#include "MainWindow.hpp"

MainWindow::MainWindow(RtpVideo* rtpVideo) 
: mPaintArea(rtpVideo)
{
  set_title("Video");
  set_default_size(800, 600);
  set_child(mPaintArea);
}

MainWindow::~MainWindow()
{
}

