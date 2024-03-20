#ifndef VIEW_UI_MAINWINDOW_HPP
#define VIEW_UI_MAINWINDOW_HPP

#include <gtkmm/window.h>

#include <view/ui/video/PaintArea.hpp>
#include <view/ui/video/ShowHideFPSVideoView.hpp>
#include <view/ui/video/PlayPauseVideoView.hpp>
#include <controller/video/ShowHideFPSController.hpp>
#include <controller/video/PlayPauseVideoController.hpp>
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
    std::shared_ptr<controller::video::ShowHideFPSVideoController> showHideFPSVideoController,
    std::shared_ptr<controller::video::PlayPauseVideoController> playPauseVideoController);
  virtual ~MainWindow();

private:
  Gtk::Box mHorizontalBox;
  Gtk::Box mVerticalBox;
  view::ui::video::PaintArea mPaintArea;
  view::ui::video::ShowHideFPSVideoView mButtonShowHideFPSVideoView;
  view::ui::video::PlayPauseVideoView mButtonPlayPauseVideoView;
};

} // namespace ui
} // namespace view

#endif // VIEW_UI_MAINWINDOW_HPP