#include "ShowHideFPSVideoView.hpp"

namespace view
{
namespace ui
{
namespace video 
{
ShowHideFPSVideoView::ShowHideFPSVideoView(std::shared_ptr<model::video::Video> model, 
  std::shared_ptr<controller::video::ShowHideFPSVideoController> controller) :
    mModel(model),
    mController(controller)
{
  updateLabel();
  signal_clicked().connect(sigc::mem_fun(*this, &ShowHideFPSVideoView::onClicked));
}

ShowHideFPSVideoView::~ShowHideFPSVideoView()
{
}

void ShowHideFPSVideoView::onClicked()
{
  mController->showHideFPSVideo();
  updateLabel();
}

void ShowHideFPSVideoView::updateLabel()
{
  if(mModel->getIsShowingFPS())
  {
    set_label(mLabelHide);
  }
  else
  {
    set_label(mLabelShow);
  }
}

} // namespace video
} // namespace ui
} // namespace view