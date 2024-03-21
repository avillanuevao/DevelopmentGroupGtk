#ifndef VIEW_UI_VIDEO_PLAYPAUSEVIDEOVIEW_HPP
#define VIEW_UI_VIDEO_PLAYPAUSEVIDEOVIEW_HPP

#include <iostream>
#include <memory>
#include <fstream>

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
  public Gtk::ToggleButton
{
  public:
    PlayPauseVideoView(const std::shared_ptr<model::video::Video> videoModel,
                      std::shared_ptr<controller::video::PlayPauseVideoController> playPauseVideoController);

  protected:
    void onClicked();
    
  private:
    void setButtonProperties();
    void loadImages();
    void updateLabel();
    void addImage(std::string imagePath);
    void checkImageExistence(std::string imagePath);
    
    const std::shared_ptr<model::video::Video> mVideoModel;
    std::shared_ptr<controller::video::PlayPauseVideoController> mPlayPauseVideoController;

    const std::string mPlayImagePath = "../../../../res/ui/play.png";
    const std::string mPauseImagePath = "../../../../res/ui/pause.png";

    Gtk::Image mPlayImage;
    Gtk::Image mPauseImage;
};

} // namespace video
} // namespace ui
} // namespace view

#endif //VIEW_UI_VIDEO_PLAYPAUSEVIDEOVIEW_HPP