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

  Glib::signal_timeout().connect(sigc::mem_fun(*this, &PaintArea::on_timeout), mRtpVideo->frameRateToMillisec()); //25 millisec -> 40 FPS
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
  mRtpVideo->surface = cairo_image_surface_create(CAIRO_FORMAT_RGB24, mRtpVideo->width, mRtpVideo->height);

  // auto a = static_cast<Gtk::Widget*>(this);
  gtk_widget_set_size_request(mDrawingArea, mRtpVideo->width, mRtpVideo->height);
  // this->set_size_request(mRtpVideo->width, mRtpVideo->height);
  g_object_set_data(G_OBJECT(mDrawingArea), "surface", mRtpVideo->surface);
  // this->set_data("surface", mRtpVideo->surface);

  // Start the update timer
  mRtpVideo->timeout_id_ =
      g_timeout_add(1000 / mRtpVideo->framerate, mRtpVideo->UpdateCallback, mDrawingArea);  // framerate is in milliseconds

  mRtpVideo->startCapture();

}

void PaintArea::on_draw(const Cairo::RefPtr<Cairo::Context> &cr, int width, int height)
{
  // paintSquare(cr, width, height);
  paintVideo(cr, width, height);
}

void PaintArea::paintVideo(const Cairo::RefPtr<Cairo::Context> &cr, int width, int height)
{
  // Time the start of the draw
      auto start = std::chrono::high_resolution_clock::now();

      uint8_t *cpu_buffer;
      mediax::video::ColourSpaceCpu convert;

      // Fill the surface with video data if available
      if (mRtpVideo->receiveRtp(&cpu_buffer, mRtpVideo->timeout_)) 
      {
        unsigned char *surface_data = cairo_image_surface_get_data(mRtpVideo->surface);

        // Get the width and height of the surface
        int width = cairo_image_surface_get_width(mRtpVideo->surface);
        int height = cairo_image_surface_get_height(mRtpVideo->surface);

        // Check the colourspace
        if (auto format = cairo_image_surface_get_format(mRtpVideo->surface); format != CAIRO_FORMAT_RGB24) 
        {
          LOG(ERROR) << "Unsupported format=" << format << "\n";
          return ;
        }

        switch (mRtpVideo->mode) 
        {
          case 0:
            convert.RgbToBgra(height, width, cpu_buffer, surface_data);
            break;
          case 1:
            convert.YuvToBgra(height, width, cpu_buffer, surface_data);
            break;
          case 2:
            convert.Mono16ToBgra(height, width, cpu_buffer, surface_data);
            break;
          case 3:
            convert.Mono8ToBgra(height, width, cpu_buffer, surface_data);
            break;
          case 4:
            convert.Nv12ToBgra(height, width, cpu_buffer, surface_data);
            break;
          default:
            LOG(ERROR) << "Unsupported mode=" << mRtpVideo->mode << "\n";
            break;
        }

        // Mark the surface as dirty to ensure the data is properly updated
        // cairo_surface_mark_dirty(data->surface);

        auto surface = new Cairo::Surface(mRtpVideo->surface);
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
        mRtpVideo->dropped_++;
      }

      if ((mRtpVideo->num_frames > 0) && (mRtpVideo->count_ >= mRtpVideo->num_frames)) 
      {
        if (mRtpVideo->timeout_id_ != 0) g_source_remove(mRtpVideo->timeout_id_);

        ///%gtk_main_quit();
        ///%g_main_loop_quit();
      }

      // Overwrite line below to test the frame rate
      if (mRtpVideo->verbose) std::cout << "Frame=" << mRtpVideo->count_ << "\r";
      std::flush(std::cout);

      if (mRtpVideo->num_frames > 0) {
        mRtpVideo->count_++;
      }

      if (mRtpVideo->timeout_id_ != 0) g_source_remove(mRtpVideo->timeout_id_);
  // If CALLBACK is not 1
  #if !CALLBACK

      // Calculate the elapsed time in ms
      auto elapsed =
          std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
      guint sleep_time = (1000 / mRtpVideo->framerate) - elapsed.count();
      if (elapsed.count() >= (1000 / mRtpVideo->framerate)) sleep_time = 1;

      // Update the g_timeout_add
      mRtpVideo->timeout_id_ = g_timeout_add(sleep_time, view::communication::video::RtpVideo::UpdateCallback,
                                  mDrawingArea);  // framerate is in milliseconds
  #else
      // data->cr = cr;
      // timeout_id_ = g_timeout_add(200, Receive::UpdateCallback,
      //                             drawing_area);  // framerate is in milliseconds

  #endif
      //return TRUE;
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