#ifndef VIEW_UI_VIDEO_PAINTAREA_HPP
#define VIEW_UI_VIDEO_PAINTAREA_HPP

#include <vector>
#include <chrono>
#include <numeric>

#include <gtkmm.h>
#include <gtkmm/drawingarea.h>
#include <cairomm/context.h>

#include <view/communication/video/RtpVideo.hpp>
#include <utils/designPattern/SignalSubscriber.hpp>
#include <model/video/signal/ShowHideFPSSignal.hpp>
#include <model/video/signal/PlayPauseVideoSignal.hpp>
#include <utils/designPattern/SignalSubscriber.hpp>

namespace view
{
namespace ui
{
namespace video
{

class PaintArea : 
  public Gtk::DrawingArea,
  public utils::designPattern::SignalSubscriber<model::video::signal::ShowHideFPSSignal>
  public utils::designPattern::SignalSubscriber<model::video::signal::PlayPauseVideoSignal>
{
public:
  PaintArea(view::communication::video::RtpVideo* rtpVideo);
  virtual ~PaintArea();

  bool on_timeout();
  void recievedSignal(model::video::signal::ShowHideFPSSignal signal) override;
  void recievedSignal(model::video::signal::PlayPauseVideoSignal signal) override;
protected:
  void on_draw(const Cairo::RefPtr<Cairo::Context> &context, int width, int height);

private:
  void initializeRtp();
  void paintSquare(const Cairo::RefPtr<Cairo::Context> &cr, int width, int height);
  void paintVideo(const Cairo::RefPtr<Cairo::Context> &cr, int width, int height);
  void drawFPS(const Cairo::RefPtr<Cairo::Context> &context, int x, int y);
  void drawText(const Cairo::RefPtr<Cairo::Context> &context, Glib::ustring text, int xPosition, 
                int yPosition);
  void connectTimeout();

  int kFrameCount = 60;
  view::communication::video::RtpVideo* mRtpVideo;
  cairo_surface_t* mSurface_t;
  std::vector<std::chrono::duration<double>> mTimestampFPS;
  int mFPS;
  std::chrono::system_clock::time_point mStart;
  std::chrono::system_clock::time_point mEnd;
  bool isShowingFPS;
  sigc::connection mTimeoutConnection;
};

} // namespace video
} // namespace ui
} // namespace view

#endif // VIEW_UI_VIDEO_PAINTAREA_HPP