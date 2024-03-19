
#include <mediax/common/example_helpers.h>

#include "RtpVideo.hpp"

namespace view
{
namespace communication
{
namespace video
{

    RtpVideo::RtpVideo()
    {
      std::cout << "Example RTP (Rx) streaming (" << width << "x" << height << " " << ModeToString(mode)
                << ") to " << ipaddr << ":" << port << "@" << framerate << "Htz\n";

      mediax::rtp::ColourspaceType video_mode = GetMode(mode);

      timeout_ = frameRateToMillisec() * 2;

  // switch (video_mode) {
  //   default:  // Assume uncompressed
  //     RtpVideo::rtp_ = std::make_shared<mediax::rtp::uncompressed::RtpUncompressedDepayloader>();
  //     break;
  //   case mediax::rtp::ColourspaceType::kColourspaceH264Part10:
  //   case mediax::rtp::ColourspaceType::kColourspaceH264Part4:
  //     RtpVideo::rtp_ = std::make_shared<mediax::rtp::h264::gst::vaapi::RtpH264GstVaapiDepayloader>();
  //     break;
  //   case mediax::rtp::ColourspaceType::kColourspaceH265:
  //     RtpVideo::rtp_ = std::make_shared<mediax::rtp::h265::gst::vaapi::RtpH265GstVaapiDepayloader>();
  //     break;
  // }
      rtp_ = std::make_shared<mediax::rtp::uncompressed::RtpUncompressedDepayloader>();

      SetupStream(video_mode);

    }

    RtpVideo::~RtpVideo()
    {

    }

    unsigned int RtpVideo::frameRateToMillisec()
    {
      float seconds = 1.0 / framerate;
      unsigned int milliseconds = seconds * 1000;
      return milliseconds;
    }

    void RtpVideo::startCapture()
    {
      // We have all the information so we can request the ports open now. No need to wait for SAP/SDP
      if (!rtp_->Open()) 
      {
        LOG(ERROR) << "Could not open stream, quitting";
        exit(1);
      }
      
      rtp_->Start();
    }

    void RtpVideo::stopCapture()
    {
        rtp_->Stop();
        rtp_->Close();

        mediax::RtpCleanup();

        std::cout << "Recieved " << count_ << ", dropped " << dropped_ << "\n";
        std::cout << "RTP (Rx) Example terminated...\n";
    }

    bool RtpVideo::receiveRtp(uint8_t **cpu, int32_t timeout)
    {
        return rtp_->Receive(cpu, timeout);
    }

    void RtpVideo::SetupStream(mediax::rtp::ColourspaceType video_mode) 
    {
      // Setup stream
      mediax::rtp::StreamInformation stream_information = {session_name, ipaddr, (uint16_t)port,
                                                          height,       width,  framerate,
                                                          video_mode,         false};
      if (wait_sap) // FOR MULTICAST
      {
        // Just give the stream name and wait for SAP/SDP announcement
        LOG(INFO) << "Example RTP streaming to " << session_name;
        sap_listener_ = std::make_shared<mediax::sap::SapListener>();
        sap_listener_->Start();

        // Sleep for one second to allow the SAP listener to start
        std::this_thread::sleep_for(std::chrono::seconds(1));

        if (sap_listener_->GetStreamInformation(session_name, &stream_information) == false) 
        {
          LOG(ERROR) << "Could not get stream information, quitting";
          exit(1);
        }
        // Add SAP callback here
        rtp_->SetStreamInfo(stream_information);

      } 
      else 
      {
        LOG(INFO) << "Example RTP streaming to " << ipaddr << ":" << port;
        rtp_->SetStreamInfo(stream_information);
      }
    }

} // namespace video
} // namespace communication
} // namespace view
