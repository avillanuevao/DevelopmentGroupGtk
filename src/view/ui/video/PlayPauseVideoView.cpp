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
        set_label(mLabelPause);
        set_active(true);
    }
    else 
    {
        set_label(mLabelPlay);
        set_active(false);
    }
}

}// namespace video
} // namespace ui
} // namespace view