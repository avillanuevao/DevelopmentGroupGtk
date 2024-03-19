#ifndef VIEW_COMMUNICATION_VIDEO_RTPVIDEO_HPP
#define VIEW_COMMUNICATION_VIDEO_RTPVIDEO_HPP

#include <gflags/gflags.h>
#include <mediax/lib/src/sap/sap_listener.h>
#include <mediax/lib/src/rtp/rtp.h>

#include <glog/logging.h>

namespace view
{
namespace communication
{
namespace video
{

class RtpVideo 
{
  public:

    const char* ipaddr = "127.0.0.1";
    const unsigned int port = 5004;
    const unsigned int height = 480;
    const unsigned int width = 640;
    const unsigned int framerate = 30; 
    const std::string session_name = "test_session_name";
    const bool verbose = false;
    const bool wait_sap = false;
    const bool uncompressed = true;
    const unsigned int mode = 1;
    const unsigned int num_frames = 0;

    RtpVideo();
    ~RtpVideo();

    void setupStream(mediax::rtp::ColourspaceType video_mode);
    unsigned int frameRateToMillisec();

    void startCapture();
    void stopCapture();
    bool receiveRtp();
    void convertBufferToSurface(int width, int heigh, unsigned char* surface_data);

  private:
    std::shared_ptr<mediax::sap::SapListener> mSapListener;
    std::shared_ptr<mediax::rtp::RtpDepayloader> mRtp;

    int32_t mTimeout;
    uint8_t* mCpuBuffer;

};

} // namespace video
} // namespace communication
} // namespace view


#endif // VIEW_COMMUNICATION_VIDEO_RTPVIDEO_HPP