#ifndef GTKMM_MAINWINDOW_H
#define GTKMM_MAINWINDOW_H

#include <gtkmm/window.h>

#include <PaintArea.hpp>

class MainWindow : public Gtk::Window
{
public:
  MainWindow(RtpVideo* rtpVideo);
  virtual ~MainWindow();

private:
  PaintArea mPaintArea;
};

#endif //GTKMM_MAINWINDOW_H