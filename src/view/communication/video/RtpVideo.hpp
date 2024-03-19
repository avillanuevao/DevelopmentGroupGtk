#ifndef VIEW_COMMUNICATION_VIDEO_RTPVIDEO_HPP
#define VIEW_COMMUNICATION_VIDEO_RTPVIDEO_HPP

#include <gtkmm.h>
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

    unsigned int frameRateToMillisec();
    void startCapture();
    void stopCapture();

    bool receiveRtp(uint8_t **cpu, int32_t timeout);

    ///
    /// \brief The GTK update callback
    ///
    /// \param user_data the user data
    /// \return gboolean true if successful
    ///
    static gboolean UpdateCallback(gpointer user_data) {
      gtk_widget_queue_draw(GTK_WIDGET(user_data));
      return TRUE;
    }

    ///
    /// \brief Rtp Callback to drive display
    ///
    /// \param depay the RTP Depayloader
    /// \param data the recieved video frame data
    ///
    void RtpCallback(const mediax::rtp::RtpDepayloader &rtp [[maybe_unused]],
                            mediax::rtp::RtpCallbackData frame [[maybe_unused]]) {
      // We dont need to render now its safe to call the Recieve function via the GTK callback
    ///%   gtk_widget_queue_draw(GTK_WIDGET(Receive::window));
      return;
    }

    ///
    /// \brief Start to process the incoming video stream
    ///
    /// \param mode the video mode
    ///
    void SetupStream(mediax::rtp::ColourspaceType video_mode);

    int32_t timeout_;
    uint32_t count_;
    uint32_t dropped_;
    guint timeout_id_;
    cairo_surface_t *surface;
    GtkWidget *window;

  private:
    std::shared_ptr<mediax::sap::SapListener> sap_listener_;
    std::shared_ptr<mediax::rtp::RtpDepayloader> rtp_;

    uint32_t frame_counter_;
};

} // namespace video
} // namespace communication
} // namespace view


#endif // VIEW_COMMUNICATION_VIDEO_RTPVIDEO_HPP