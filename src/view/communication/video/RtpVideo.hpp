#ifndef VIEW_COMMUNICATION_VIDEO_RTPVIDEO_HPP
#define VIEW_COMMUNICATION_VIDEO_RTPVIDEO_HPP

#include <gtkmm.h>
#include <gflags/gflags.h>
// #include <mediax/common/example.h>
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

    // struct FLAGS
    // {
        const char* ipaddr = "127.0.0.1";
        const unsigned int port = 5004;
        const unsigned int height = 480;
        const unsigned int width = 640;
        const unsigned int framerate = 25; 
        const std::string session_name = "test_session_name";
        const bool verbose = false;
        const bool wait_sap = false;
        const bool uncompressed = true;
        const unsigned int mode = 1;
        const unsigned int num_frames = 0;
    // };

    struct OnDrawData 
    {
        cairo_t *cr;
        std::string name;
        cairo_surface_t *surface;
        int32_t height;
        int32_t width;
        std::string ipaddr;
        uint16_t port;
    };

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
    void SetupStream(mediax::rtp::ColourspaceType video_mode) {
      // Setup stream
      mediax::rtp::StreamInformation stream_information = {session_name, ipaddr, (uint16_t)port,
                                                          height,       width,  framerate,
                                                          video_mode,         false};
      if (wait_sap) {
        // Just give the stream name and wait for SAP/SDP announcement
        LOG(INFO) << "Example RTP streaming to " << session_name;
        sap_listener_ = std::make_shared<mediax::sap::SapListener>();
        sap_listener_->Start();
        // Sleep for one second to allow the SAP listener to start
        std::this_thread::sleep_for(std::chrono::seconds(1));

        if (sap_listener_->GetStreamInformation(session_name, &stream_information) == false) {
          LOG(ERROR) << "Could not get stream information, quitting";
          exit(1);
        }
        // Add SAP callback here
        rtp_->SetStreamInfo(stream_information);
      } else {
        LOG(INFO) << "Example RTP streaming to " << ipaddr << ":" << port;
        rtp_->SetStreamInfo(stream_information);
      }
    }

    std::shared_ptr<mediax::rtp::RtpDepayloader> rtp_;
    int32_t timeout_;
    uint32_t count_;
    uint32_t dropped_;
    guint timeout_id_;
    cairo_surface_t *surface;
    GtkWidget *window;

  private:
    std::shared_ptr<mediax::sap::SapListener> sap_listener_;

    uint32_t frame_counter_;
};

} // namespace video
} // namespace communication
} // namespace view


#endif // VIEW_COMMUNICATION_VIDEO_RTPVIDEO_HPP