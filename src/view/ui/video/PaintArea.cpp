#include <iostream>

#include "PaintArea.hpp"

namespace view
{
namespace ui
{
namespace video
{

PaintArea::PaintArea(view::communication::video::RtpVideo* rtpVideo)
  : mDrawingArea(nullptr),
    mSurface(),
    mRtpVideo(rtpVideo)
{
  initializeRtp();

  Glib::signal_timeout().connect(sigc::mem_fun(*this, &PaintArea::on_timeout), mRtpVideo->frameRateToMillisec()); 
  set_draw_func(sigc::mem_fun(*this, &PaintArea::on_draw));
}

PaintArea::~PaintArea()
{
  mRtpVideo->stopCapture();
}

bool PaintArea::on_timeout()
{
  // force our program to redraw the entire clock.
  queue_draw();
  return true;
}

void PaintArea::initializeRtp()
{
  mDrawingArea = gtk_drawing_area_new();
  mSurface_t = cairo_image_surface_create(CAIRO_FORMAT_RGB24, mRtpVideo->width, mRtpVideo->height);

  // auto a = static_cast<Gtk::Widget*>(this);
  gtk_widget_set_size_request(mDrawingArea, mRtpVideo->width, mRtpVideo->height);
  // this->set_size_request(mRtpVideo->width, mRtpVideo->height);
  g_object_set_data(G_OBJECT(mDrawingArea), "surface", mSurface_t);
  // this->set_data("surface", mSurface_t);

  mRtpVideo->startCapture();

}

void PaintArea::on_draw(const Cairo::RefPtr<Cairo::Context> &cr, int width, int height)
{
  // paintSquare(cr, width, height);
  paintVideo(cr, width, height);
}

void PaintArea::paintVideo(const Cairo::RefPtr<Cairo::Context> &cr, int width, int height)
{
  // Fill the surface with video data if available
  if (mRtpVideo->receiveRtp()) 
  {
    unsigned char *surface_data = cairo_image_surface_get_data(mSurface_t);

    // Get the width and height of the surface
    int width = cairo_image_surface_get_width(mSurface_t);
    int height = cairo_image_surface_get_height(mSurface_t);

    // Check the colourspace
    auto format = cairo_image_surface_get_format(mSurface_t);
    if (format != CAIRO_FORMAT_RGB24) 
    {
      LOG(ERROR) << "Unsupported format=" << format << "\n";
      return ;
    }

    mRtpVideo->convertBufferToSurface(width, height, surface_data);

    // Mark the surface as dirty to ensure the data is properly updated
    // cairo_surface_mark_dirty(data->surface);

    auto surface = new Cairo::Surface(mSurface_t);
    mSurface = Cairo::RefPtr<Cairo::Surface>(surface);
    cr->set_source(mSurface, 0, 0);
    cr->paint();
        
  } 
  else 
  {
    // Timedout
    cr->select_font_face("Courier", Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
    cr->set_font_size(24);
    cr->move_to(20, 50);
    
    std::string no_stream = "No Stream " + mRtpVideo->session_name + ":" + mRtpVideo->ipaddr + ":" + std::to_string(mRtpVideo->port) + "\n";
    cr->show_text(no_stream.c_str());
  }

}

void PaintArea::paintSquare(const Cairo::RefPtr<Cairo::Context> &cr, int width, int height)
{
  /* a custom shape that could be wrapped in a function */
  double x         = 0,        /* parameters like cairo_rectangle */
        y         = 0,
        aspect        = 1.0,     /* aspect ratio */
        corner_radius = height / 10.0;   /* and corner curvature radius */



  double radius = corner_radius / aspect;
  double degrees = M_PI / 180.0;

  cr->arc(x + width - radius, y + radius, radius, -90 * degrees, 0 * degrees);
  cr->arc(x + width - radius, y + radius, radius, -90 * degrees, 0 * degrees);
  cr->arc(x + width - radius, y + height - radius, radius, 0 * degrees, 90 * degrees);
  cr->arc(x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees);
  cr->arc(x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
  cr->close_path();

  cr->set_source_rgb(0.5, 0.5, 1);
  cr->fill_preserve();
  cr->set_source_rgba(0.5, 0, 0, 0.5);
  cr->set_line_width(10.0);
  cr->stroke();
}

} // namespace video
} // namespace ui
} // namespace view