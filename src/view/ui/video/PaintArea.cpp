#include <iostream>

#include "PaintArea.hpp"

namespace view
{
namespace ui
{
namespace video
{

PaintArea::PaintArea(view::communication::video::RtpVideo* rtpVideo) : 
  mRtpVideo(rtpVideo), mSurface_t(nullptr), mFPS(0), mIsShowingFPS(false)
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
  mIsShowingFPS = signal.getIsShowingFPSVideo();
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
  paintVideo(cr);
  paintFPS(cr, kXFPS, kYFPS);
  calculateFPS();
}

void PaintArea::paintVideo(const Cairo::RefPtr<Cairo::Context> &cr)
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

    std::string no_stream = "No Stream " + mRtpVideo->session_name + ":" + mRtpVideo->ipaddr + ":" 
                            + std::to_string(mRtpVideo->port) + "\n";
    paintText(cr, Glib::ustring(no_stream), 20, 50);
  }
}

void PaintArea::connectTimeout()
{
  mTimeoutConnection = Glib::signal_timeout().connect(sigc::mem_fun(*this, &PaintArea::on_timeout), mRtpVideo->frameRateToMillisec()); 
}

void PaintArea::calculateFPS()
{
  mTimestampFPSEnd = std::chrono::high_resolution_clock::now();

  if (mTimestampFPS.size() <= kFrameCount)
  {
    mTimestampFPS.push_back(std::chrono::duration<double>(mTimestampFPSEnd - mTimestampFPSStart));    
  }
  else
  {
    mFPS = kFrameCount / std::reduce(mTimestampFPS.begin(), mTimestampFPS.end()).count();
    
    mTimestampFPS.clear();
  }

  mTimestampFPSStart = std::chrono::high_resolution_clock::now();
}

void PaintArea::paintFPS(const Cairo::RefPtr<Cairo::Context> &context, int x, int y)
{
  if(mIsShowingFPS)
  {
    paintText(context, "FPS: " + Glib::ustring::format(mFPS), x, y);
  }
}

void PaintArea::paintText(const Cairo::RefPtr<Cairo::Context> &context, Glib::ustring text, int xPosition,
                      int yPosition)
{
  Pango::FontDescription font;
  font.set_family("Monospace");
  font.set_weight(Pango::Weight::BOLD);
  font.set_absolute_size(20 * PANGO_SCALE);

  Glib::RefPtr<Pango::Layout> layout = create_pango_layout(text);
  layout->set_font_description(font);

  context->set_source_rgb(0, 0, 0);
  context->move_to(xPosition, yPosition);
  layout->show_in_cairo_context(context);
  context->stroke();
}

} // namespace video
} // namespace ui
} // namespace view