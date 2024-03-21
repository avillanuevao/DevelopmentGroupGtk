#include "ShowHideFPSVideoView.hpp"

namespace view
{
namespace ui
{
namespace video 
{
ShowHideFPSVideoView::ShowHideFPSVideoView(std::shared_ptr<model::video::Video> videoModel, 
  std::shared_ptr<controller::video::ShowHideFPSVideoController> showHideFPSVideoController) :
    mVideoModel(videoModel),
    mShowHideFPSVideoController(showHideFPSVideoController)
{
  buttonConfiguration(); 
  updateLabel();
}

ShowHideFPSVideoView::~ShowHideFPSVideoView()
{
}

void ShowHideFPSVideoView::onClicked()
{
  mShowHideFPSVideoController->showHideFPSVideo();
  updateLabel();
}

void ShowHideFPSVideoView::buttonConfiguration()
{
  set_size_request(kWidthButton, kHeigthButton);
  set_halign(Gtk::Align::CENTER);
  set_margin_top(kMarginTop);

  signal_clicked().connect(sigc::mem_fun(*this, &ShowHideFPSVideoView::onClicked));
}

void ShowHideFPSVideoView::updateLabel()
{
  if(mVideoModel->getIsShowingFPS())
  {
    set_label(kLabelHide);
  }
  else
  {
    set_label(kLabelShow);
  }
}

} // namespace video
} // namespace ui
} // namespace view