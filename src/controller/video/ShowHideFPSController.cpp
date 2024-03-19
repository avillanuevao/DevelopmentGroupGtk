#include "ShowHideFPSController.hpp"

namespace controller
{
namespace video 
{
ShowHideFPSVideoController::ShowHideFPSVideoController(std::shared_ptr<model::video::Video> model) :
    mModel(model)
{
}

void ShowHideFPSVideoController::showHideFPSVideo()
{
    mModel->setIsShowingFPS(!mModel->getIsShowingFPS());
}

} // namespace video
} // namespace controller