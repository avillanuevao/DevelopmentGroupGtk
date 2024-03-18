#ifndef GTKMM__PAINTAREA_H
#define GTKMM__PAINTAREA_H

#include <gtkmm/drawingarea.h>
#include <cairomm/context.h>

#include <RtpVideo.hpp>

class PaintArea : public Gtk::DrawingArea
{
public:
  PaintArea(RtpVideo* rtpVideo);
  virtual ~PaintArea();

  bool on_timeout();
  int fpsTomillisec(int fps);

protected:
  void on_draw(const Cairo::RefPtr<Cairo::Context> &context, int width, int height);

private:
  void initializeRtp();
  void paintSquare(const Cairo::RefPtr<Cairo::Context> &cr, int width, int height);
  void paintVideo(const Cairo::RefPtr<Cairo::Context> &cr, int width, int height);

  GtkWidget* mDrawingArea = nullptr;
  RtpVideo::OnDrawData mData;
  Cairo::RefPtr<Cairo::Surface> mSurface;
  RtpVideo* mRtpVideo;
  
};

#endif // GTKMM__PAINTAREA_H