#include "ShowHideFPSController.hpp"

namespace controller
{
namespace video 
{
ShowHideFPSVideoController::ShowHideFPSVideoController(std::shared_ptr<model::video::Video> videoModel) :
    mVideoModel(videoModel)
{
}

void ShowHideFPSVideoController::showHideFPSVideo()
{
    mVideoModel->setIsShowingFPS(!mVideoModel->getIsShowingFPS());
}

} // namespace video
} // namespace controller