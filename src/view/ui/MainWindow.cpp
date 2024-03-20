#include "MainWindow.hpp"

namespace view
{
namespace ui
{

MainWindow::MainWindow(view::communication::video::RtpVideo* rtpVideo, 
  std::shared_ptr<model::video::Video> videoModel,
  std::shared_ptr<controller::video::ShowHideFPSVideoController> showHideFPSVideoController,
  std::shared_ptr<controller::video::PlayPauseVideoController> playPauseVideoController) : 
    mHorizontalBox(Gtk::Orientation::HORIZONTAL),
    mVerticalBox(Gtk::Orientation::VERTICAL),
    mPaintArea(rtpVideo),
    mButtonShowHideFPSVideoView(videoModel, showHideFPSVideoController),
    mButtonPlayPauseVideoView(videoModel, playPauseVideoController)
{
  set_title("Video");
  set_default_size(800, 600);

  mPaintArea.set_content_width(640);
  mPaintArea.set_content_height(480);

  mVerticalBox.append(mButtonShowHideFPSVideoView);
  mVerticalBox.append(mButtonPlayPauseVideoView);

  mHorizontalBox.set_spacing(10);
  mHorizontalBox.append(mPaintArea);
  mHorizontalBox.append(mVerticalBox);

  set_child(mHorizontalBox);
}

MainWindow::~MainWindow()
{
}

} // namespace ui
} // namespace view