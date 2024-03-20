#include "PlayPauseVideoController.hpp"

namespace controller
{
namespace video 
{
PlayPauseVideoController::PlayPauseVideoController(std::shared_ptr<model::video::Video> model) :
    mModel(model)
{
}

void PlayPauseVideoController::playPauseVideo()
{
    mModel->setIsPlayingVideo(!mModel->getIsPlayingVideo());
}

} // namespace video
} // namespace controller