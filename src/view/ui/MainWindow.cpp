#include "MainWindow.hpp"

namespace view
{
namespace ui
{

MainWindow::MainWindow(view::communication::video::RtpVideo* rtpVideo, 
  std::shared_ptr<model::video::Video> videoModel,
  std::shared_ptr<controller::video::ShowHideFPSVideoController> showHideFPSVideoController,
  std::shared_ptr<controller::video::PlayPauseVideoController> playPauseVideoController) : 
    mHorizontalBox(Gtk::Orientation::HORIZONTAL), mVerticalBoxButtons(Gtk::Orientation::VERTICAL),
    mVideoModel(videoModel), mPaintArea(std::make_shared<view::ui::video::PaintArea>(rtpVideo)),
    mButtonPlayPauseVideoView(std::make_shared<ui::video::PlayPauseVideoView>(
      videoModel, playPauseVideoController)),
    mButtonShowHideFPSVideoView(std::make_shared<view::ui::video::ShowHideFPSVideoView>(
      videoModel, showHideFPSVideoController))
{
  windowConfiguration();
  
  addSubscribersToVideoModel();
  
  initializeUIComponents();
}

MainWindow::~MainWindow()
{
}

void MainWindow::windowConfiguration()
{
  set_title("Video");
  // set_decorated(false);
  set_default_size(kWidthWindow, kHeigthWindow);
}

void MainWindow::initializeUIComponents()
{
  mPaintArea->set_content_width(kWidhtVideo);
  mPaintArea->set_content_height(kHeigthVideo);

  mVerticalBoxButtons.set_expand(true);

  mVerticalBoxButtons.append(*mButtonShowHideFPSVideoView);
  mVerticalBoxButtons.append(*mButtonPlayPauseVideoView);
  
  mVerticalBoxPaintArea.append(*mPaintArea);

  mHorizontalBox.append(mVerticalBoxPaintArea);
  mHorizontalBox.append(mVerticalBoxButtons);
  set_child(mHorizontalBox);
}

void MainWindow::addSubscribersToVideoModel()
{
  mVideoModel->utils::designPattern::SignalPublisher<model::video::signal::PlayPauseVideoSignal>::
      addSubscriber(mPaintArea);
  mVideoModel->utils::designPattern::SignalPublisher<model::video::signal::ShowHideFPSSignal>::
      addSubscriber(mPaintArea);

}

} // namespace ui
} // namespace view