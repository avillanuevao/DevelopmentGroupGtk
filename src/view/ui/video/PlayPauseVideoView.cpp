#include "PlayPauseVideoView.hpp"

namespace view
{
namespace ui
{
namespace video 
{
PlayPauseVideoView::PlayPauseVideoView(const std::shared_ptr<model::video::Video> videoModel, 
                                    std::shared_ptr<controller::video::PlayPauseVideoController> playPauseVideoController) :
    mVideoModel(videoModel), mPlayPauseVideoController(playPauseVideoController)
{ 
  setButtonProperties();

  loadImages();
}

void PlayPauseVideoView::onClicked()
{
  mPlayPauseVideoController->playPauseVideo();
  updateLabel();
}

void PlayPauseVideoView::setButtonProperties()
{
  set_halign(Gtk::Align::CENTER);
  set_size_request(100, 50);
  set_margin_top(10);

  signal_clicked().connect(sigc::mem_fun(*this, &PlayPauseVideoView::onClicked));

  updateLabel();
}

void PlayPauseVideoView::loadImages()
{
  checkImageExistence(mPlayImagePath);
  checkImageExistence(mPauseImagePath);

  addImage(mPlayImagePath);
  addImage(mPauseImagePath);
}

void PlayPauseVideoView::updateLabel()
{
  if (mVideoModel->getIsPlayingVideo())
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

void PlayPauseVideoView::addImage(std::string imagePath)
{
  if (imagePath == mPlayImagePath)
  {
    mPlayImage.set(mPlayImagePath);
  } 
  else if (imagePath == mPauseImagePath)
  {
    mPauseImage.set(mPauseImagePath);
  }
}

void PlayPauseVideoView::checkImageExistence(std::string imagePath)
{
  std::ifstream file(imagePath);

  if (!file.good())
  {
    std::cerr << "Error loading image: " << imagePath << std::endl;
  }
}

} // namespace video
} // namespace ui
} // namespace view