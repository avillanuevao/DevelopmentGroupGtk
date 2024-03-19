#ifndef VIEW_UI_VIDEO_PAINTAREA_HPP
#define VIEW_UI_VIDEO_PAINTAREA_HPP

#include <gtkmm.h>
#include <gtkmm/drawingarea.h>
#include <cairomm/context.h>

#include <view/communication/video/RtpVideo.hpp>

namespace view
{
namespace ui
{
namespace video
{

class PaintArea : public Gtk::DrawingArea
{
public:
  PaintArea(view::communication::video::RtpVideo* rtpVideo);
  virtual ~PaintArea();

  bool on_timeout();

protected:
  void on_draw(const Cairo::RefPtr<Cairo::Context> &context, int width, int height);

private:
  void initializeRtp();
  void paintSquare(const Cairo::RefPtr<Cairo::Context> &cr, int width, int height);
  void paintVideo(const Cairo::RefPtr<Cairo::Context> &cr, int width, int height);

  GtkWidget* mDrawingArea = nullptr;
  Cairo::RefPtr<Cairo::Surface> mSurface;
  view::communication::video::RtpVideo* mRtpVideo;
  cairo_surface_t* mSurface_t;
  
};

} // namespace video
} // namespace ui
} // namespace view

#endif // VIEW_UI_VIDEO_PAINTAREA_HPP