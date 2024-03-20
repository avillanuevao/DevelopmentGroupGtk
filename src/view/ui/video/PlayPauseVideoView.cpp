#include "PlayPauseVideoView.hpp"

namespace view
{
namespace ui
{
namespace video 
{
PlayPauseVideoView::PlayPauseVideoView(std::shared_ptr<model::video::Video> model, 
                                    std::shared_ptr<controller::video::PlayPauseVideoController> controller) :
    mModel(model), mController(controller)
{ 
  set_halign(Gtk::Align::CENTER);
  set_size_request(100, 50);
  set_margin_top(10);

  addImages();

  updateLabel();
    
  signal_clicked().connect(sigc::mem_fun(*this, &PlayPauseVideoView::onClicked));

}

void PlayPauseVideoView::onClicked()
{
  mController->playPauseVideo();
  updateLabel();
}

void PlayPauseVideoView::updateLabel()
{
  if(mModel->getIsPlayingVideo())
  {
    set_active(true);
    set_child(mPauseImage);
  }
  else 
  {
    set_active(false);
    set_child(mPlayImage);
  }
}

void PlayPauseVideoView::addImages()
{
  mPlayImage.set("../../../image/play.png");
  mPauseImage.set("../../../image/pause.png");
}

}// namespace video
} // namespace ui
} // namespace view