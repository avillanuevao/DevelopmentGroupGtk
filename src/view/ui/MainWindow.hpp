#ifndef VIEW_UI_MAINWINDOW_HPP
#define VIEW_UI_MAINWINDOW_HPP

#include <gtkmm/window.h>

#include <view/ui/video/PaintArea.hpp>
#include <view/ui/video/ShowHideFPSVideoView.hpp>
#include <controller/video/ShowHideFPSController.hpp>
#include <model/video/Video.hpp>

namespace view
{
namespace ui
{

class MainWindow : public Gtk::Window
{
public:
  MainWindow(view::communication::video::RtpVideo* rtpVideo, 
    std::shared_ptr<model::video::Video> videoModel,
    std::shared_ptr<controller::video::ShowHideFPSVideoController> showHideFPSVideoController);
  virtual ~MainWindow();

private:
  Gtk::Box mHorizontalBox;
  Gtk::Box mVerticalBox;
  std::shared_ptr<model::video::Video> mVideoModel;
  std::shared_ptr<view::ui::video::PaintArea> mPaintArea;
  std::shared_ptr<view::ui::video::ShowHideFPSVideoView> mButtonShowHideFPSVideoView;
};

} // namespace ui
} // namespace view

#endif // VIEW_UI_MAINWINDOW_HPP