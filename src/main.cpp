

#include <mediax/version.h>

#include <view/ui/MainWindow.hpp>
#include <view/communication/video/RtpVideo.hpp>

GtkWidget *drawing_area = nullptr;
view::communication::video::RtpVideo* mRtpVideo = nullptr;

void signalHandler(int signum [[maybe_unused]]) 
{
  // GTK close
  ///%gtk_main_quit();
  mRtpVideo->rtp_->Stop();
  mRtpVideo->rtp_->Close();
  mediax::RtpCleanup();
  std::cout << "receive-example Interrupt signal (" << signum << ") received.\n";

  exit(1);
}


int main(int argc, char *argv[]) 
{
  gflags::SetVersionString(mediax::kVersion);
  gflags::SetUsageMessage(
      "Example RTP receiver\n"
      "Usage:\n"
      "  rtp-receive [OPTION]...\n"
      "Example:\n"
      "  rtp-receive -ipaddr=127.0.0.1 --port=5004 --height=480 --width=640\n");
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  auto app = Gtk::Application::create("org.gtkmm.examples.base");

  google::InitGoogleLogging(argv[0]);
  google::InstallFailureSignalHandler();
  mediax::InitRtp(argc, argv);

  mRtpVideo = new view::communication::video::RtpVideo();

  signal(SIGINT, signalHandler);
  signal(SIGTERM, signalHandler);

  int exit = app->make_window_and_run<view::ui::MainWindow>(argc, argv, mRtpVideo);

  mRtpVideo->rtp_->Stop();
  mRtpVideo->rtp_->Close();

  mediax::RtpCleanup();

  std::cout << "Exit..." << std::endl;

  return exit;
}
