#include "MainWindow.hpp"

namespace view
{
namespace ui
{

MainWindow::MainWindow(view::communication::video::RtpVideo* rtpVideo) 
: mPaintArea(rtpVideo)
{
  set_title("Video");
  set_default_size(800, 600);
  set_child(mPaintArea);
}

MainWindow::~MainWindow()
{
}

} // namespace ui
} // namespace view