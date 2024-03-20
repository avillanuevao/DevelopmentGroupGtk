#include "MainWindow.hpp"

namespace view
{
namespace ui
{

MainWindow::MainWindow(view::communication::video::RtpVideo* rtpVideo, 
  std::shared_ptr<model::video::Video> videoModel,
  std::shared_ptr<controller::video::ShowHideFPSVideoController> showHideFPSVideoController) : 
    mHorizontalBox(Gtk::Orientation::HORIZONTAL),
    mVerticalBox(Gtk::Orientation::VERTICAL),
    mVideoModel(videoModel),
    mPaintArea(std::make_shared<view::ui::video::PaintArea>(rtpVideo)),
    mButtonShowHideFPSVideoView(std::make_shared<view::ui::video::ShowHideFPSVideoView>(videoModel, showHideFPSVideoController))
{
  set_title("Video");
  set_default_size(800, 600);

  mVideoModel->addSubscriber(mPaintArea);

  mPaintArea->set_content_width(640);
  mPaintArea->set_content_height(480);

  mVerticalBox.append(*mButtonShowHideFPSVideoView);

  mHorizontalBox.set_spacing(10);
  mHorizontalBox.append(*mPaintArea);
  mHorizontalBox.append(mVerticalBox);

  set_child(mHorizontalBox);
}

MainWindow::~MainWindow()
{
}

} // namespace ui
} // namespace view