#ifndef VIEW_UI_VIDEO_PLAYPAUSEVIDEOVIEW_HPP
#define VIEW_UI_VIDEO_PLAYPAUSEVIDEOVIEW_HPP

#include <iostream>
#include <memory>

#include <gtkmm.h>

#include <model/video/Video.hpp>
#include <controller/video/PlayPauseVideoController.hpp>

namespace view
{
namespace ui
{
namespace video 
{

class PlayPauseVideoView :
  public Gtk::Button
{
  public:
    PlayPauseVideoView(std::shared_ptr<model::video::Video> model,
                      std::shared_ptr<controller::video::PlayPauseVideoController> controller);

  protected:
    void onClicked();
    
  private:
    void updateLabel();
    
    std::shared_ptr<model::video::Video> mModel;
    std::shared_ptr<controller::video::PlayPauseVideoController> mController;
    Glib::ustring mLabelPlay = "Play Video";
    Glib::ustring mLabelPause = "Pause Video";
};

} // namespace video
} // namespace ui
} // namespace view

#endif //VIEW_UI_VIDEO_PLAYPAUSEVIDEOVIEW_HPP