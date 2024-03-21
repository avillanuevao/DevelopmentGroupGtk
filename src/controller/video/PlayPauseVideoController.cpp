#include "PlayPauseVideoController.hpp"

namespace controller
{
namespace video 
{
PlayPauseVideoController::PlayPauseVideoController(std::shared_ptr<model::video::Video> videoModel) :
  mVideoModel(videoModel)
{
}

void PlayPauseVideoController::playPauseVideo()
{
  if (mVideoModel->isPlayingVideo())
  {
    mVideoModel->stopVideo();
  }
  else
  {
    mVideoModel->playVideo();
  }
}

} // namespace video
} // namespace controller