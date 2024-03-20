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
    mVerticalBoxButtons(Gtk::Orientation::VERTICAL),
    mVideoModel(videoModel),
    mPaintArea(std::make_shared<view::ui::video::PaintArea>(rtpVideo)),
    mButtonShowHideFPSVideoView(videoModel, showHideFPSVideoController),
    mButtonPlayPauseVideoView(videoModel, playPauseVideoController)
{
  set_title("Video");
  set_default_size(800, 600);

  mVideoModel->
    utils::designPattern::SignalPublisher<model::video::signal::PlayPauseVideoSignal>::addSubscriber(mPaintArea);

  mPaintArea->set_content_width(640);
  mPaintArea->set_content_height(480);

  mVerticalBoxButtons.set_expand(true);

  mVerticalBoxButtons.append(mButtonShowHideFPSVideoView);
  mVerticalBoxButtons.append(mButtonPlayPauseVideoView);
  
  mVerticalBoxPaintArea.append(*mPaintArea);

  mHorizontalBox.append(mVerticalBoxPaintArea);
  mHorizontalBox.append(mVerticalBoxButtons);
  set_child(mHorizontalBox);
}

MainWindow::~MainWindow()
{
}

} // namespace ui
} // namespace view