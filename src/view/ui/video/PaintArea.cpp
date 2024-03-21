#include <iostream>

#include "PaintArea.hpp"

namespace view
{
namespace ui
{
namespace video
{

PaintArea::PaintArea(view::communication::video::RtpVideo* rtpVideo)
  : mRtpVideo(rtpVideo),
    mSurface_t(nullptr),
    mFPS(0),
    isShowingFPS(false)
{
  initializeRtp();

  connectTimeout();
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

void PaintArea::recievedSignal(model::video::signal::ShowHideFPSSignal signal)
{
  isShowingFPS = signal.getIsShowingFPSVideo();
}

void PaintArea::recievedSignal(model::video::signal::PlayPauseVideoSignal signal)
{  
  if(signal.getIsPlayingVideo())
  {
    connectTimeout();
  }
  else
  {
    mTimeoutConnection.disconnect();
  }
}

void PaintArea::initializeRtp()
{
  mSurface_t = cairo_image_surface_create(CAIRO_FORMAT_RGB24, mRtpVideo->width, mRtpVideo->height);

  // this->set_size_request(mRtpVideo->width, mRtpVideo->height);
  this->set_content_width(mRtpVideo->width);
  this->set_content_height(mRtpVideo->height);
  this->set_data("surface", mSurface_t);

  mRtpVideo->startCapture();
}

void PaintArea::on_draw(const Cairo::RefPtr<Cairo::Context> &cr, int width, int height)
{
  mEnd = std::chrono::high_resolution_clock::now();
  
  paintVideo(cr, width, height);
  // paintSquare(cr, 80, 80);
  drawFPS(cr, 10, 10);

  auto end = std::chrono::high_resolution_clock::now();
  if(mTimestampFPS.size() <= kFrameCount)
  {
    mTimestampFPS.push_back(std::chrono::duration<double>((end - mEnd) + (mEnd - mStart)));    
  }
  else
  {
    mFPS = kFrameCount / std::reduce(mTimestampFPS.begin(), mTimestampFPS.end()).count();
    
    mTimestampFPS.clear();
  }

  mStart = std::chrono::high_resolution_clock::now();
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

    auto surface = Cairo::RefPtr<Cairo::Surface>(new Cairo::Surface(mSurface_t));
    cr->set_source(surface, 0, 0);
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

void PaintArea::connectTimeout()
{
  mTimeoutConnection = Glib::signal_timeout().connect(sigc::mem_fun(*this, &PaintArea::on_timeout), mRtpVideo->frameRateToMillisec()); 
}

void PaintArea::drawFPS(const Cairo::RefPtr<Cairo::Context> &context, int x, int y)
{
  if(isShowingFPS)
  {
    drawText(context, "FPS: " + Glib::ustring::format(mFPS), x, y);
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

void PaintArea::drawText(const Cairo::RefPtr<Cairo::Context> &context, Glib::ustring text, int xPosition,
                      int yPosition)
{
  // Pango::FontDescription sirve para establecer el tipo de fuente y diferentes características del texto 
  // como si es en negrita, cursiva, tamaño...
  Pango::FontDescription font;
  font.set_family("Monospace");
  font.set_weight(Pango::Weight::BOLD);
  font.set_absolute_size(20 * PANGO_SCALE);

  // Creamos el Layout donde se pintara el texto. El tamaño del layout se calcurá en función del texto que 
  // tenga dentro
  Glib::RefPtr<Pango::Layout> layout = create_pango_layout(text);
  layout->set_font_description(font);

  // Nos posicionamos donde queremos pintar y pintamos
  context->set_source_rgb(0, 0, 0);
  context->move_to(xPosition, yPosition);
  layout->show_in_cairo_context(context);
  context->stroke();
}

} // namespace video
} // namespace ui
} // namespace view