#ifndef VIEW_UI_MAINWINDOW_HPP
#define VIEW_UI_MAINWINDOW_HPP

#include <gtkmm/window.h>

#include <view/ui/video/PaintArea.hpp>

namespace view
{
namespace ui
{

class MainWindow : public Gtk::Window
{
public:
  MainWindow(view::communication::video::RtpVideo* rtpVideo);
  virtual ~MainWindow();

private:
  view::ui::video::PaintArea mPaintArea;
};

} // namespace ui
} // namespace view

#endif // VIEW_UI_MAINWINDOW_HPP