#include "RtpVideo.hpp"

#include <mediax/common/example_helpers.h>


namespace view
{
namespace communication
{
namespace video
{

    RtpVideo::RtpVideo()
    : mSapListener(nullptr)
    , mRtp(nullptr)
    , mTimeout(0)
    , mCpuBuffer(nullptr)
    {
      std::cout << "Example RTP (Rx) streaming (" << width << "x" << height << " " << ModeToString(mode)
                << ") to " << ipaddr << ":" << port << "@" << framerate << "Htz\n";

      mediax::rtp::ColourspaceType video_mode = GetMode(mode);

      mTimeout = frameRateToMillisec() * 2;

  // switch (video_mode) {
  //   default:  // Assume uncompressed
  //     RtpVideo::mRtp = std::make_shared<mediax::rtp::uncompressed::RtpUncompressedDepayloader>();
  //     break;
  //   case mediax::rtp::ColourspaceType::kColourspaceH264Part10:
  //   case mediax::rtp::ColourspaceType::kColourspaceH264Part4:
  //     RtpVideo::mRtp = std::make_shared<mediax::rtp::h264::gst::vaapi::RtpH264GstVaapiDepayloader>();
  //     break;
  //   case mediax::rtp::ColourspaceType::kColourspaceH265:
  //     RtpVideo::mRtp = std::make_shared<mediax::rtp::h265::gst::vaapi::RtpH265GstVaapiDepayloader>();
  //     break;
  // }
      mRtp = std::make_shared<mediax::rtp::uncompressed::RtpUncompressedDepayloader>();

      setupStream(video_mode);

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
      if (!mRtp->Open()) 
      {
        LOG(ERROR) << "Could not open stream, quitting";
        exit(1);
      }
      
      mRtp->Start();
    }

    void RtpVideo::stopCapture()
    {
        mRtp->Stop();
        mRtp->Close();

        mediax::RtpCleanup();
        std::cout << "RTP (Rx) Example terminated...\n";
    }

    bool RtpVideo::receiveRtp()
    {
        return mRtp->Receive(&mCpuBuffer, mTimeout);
    }

    void RtpVideo::convertBufferToSurface(int width, int heigh, unsigned char* surface_data)
    {
      mediax::video::ColourSpaceCpu convert;

      switch (mode) 
      {
        case 0:
          convert.RgbToBgra(height, width, mCpuBuffer, surface_data);
          break;
        case 1:
          convert.YuvToBgra(height, width, mCpuBuffer, surface_data);
          break;
        case 2:
          convert.Mono16ToBgra(height, width, mCpuBuffer, surface_data);
          break;
        case 3:
          convert.Mono8ToBgra(height, width, mCpuBuffer, surface_data);
          break;
        case 4:
          convert.Nv12ToBgra(height, width, mCpuBuffer, surface_data);
          break;
        default:
          LOG(ERROR) << "Unsupported mode=" << mode << "\n";
          break;
      }
    }

    void RtpVideo::setupStream(mediax::rtp::ColourspaceType video_mode) 
    {
      // Setup stream
      mediax::rtp::StreamInformation stream_information = {session_name, ipaddr, (uint16_t)port,
                                                          height,       width,  framerate,
                                                          video_mode,         false};
      if (wait_sap) // FOR MULTICAST
      {
        // Just give the stream name and wait for SAP/SDP announcement
        LOG(INFO) << "Example RTP streaming to " << session_name;
        mSapListener = std::make_shared<mediax::sap::SapListener>();
        mSapListener->Start();

        // Sleep for one second to allow the SAP listener to start
        std::this_thread::sleep_for(std::chrono::seconds(1));

        if (mSapListener->GetStreamInformation(session_name, &stream_information) == false) 
        {
          LOG(ERROR) << "Could not get stream information, quitting";
          exit(1);
        }
        // Add SAP callback here
        mRtp->SetStreamInfo(stream_information);

      } 
      else 
      {
        LOG(INFO) << "Example RTP streaming to " << ipaddr << ":" << port;
        mRtp->SetStreamInfo(stream_information);
      }
    }

} // namespace video
} // namespace communication
} // namespace view
