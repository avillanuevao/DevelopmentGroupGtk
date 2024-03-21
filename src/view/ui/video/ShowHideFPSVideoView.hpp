#ifndef VIEW_UI_VIDEO_SHOWHIDEFPSVIDEOVIEW_HPP
#define VIEW_UI_VIDEO_SHOWHIDEFPSVIDEOVIEW_HPP

#include <iostream>
#include <memory>

#include <gtkmm.h>
#include <glib.h>

#include <controller/video/ShowHideFPSController.hpp>
#include <model/video/Video.hpp>

namespace view
{
namespace ui
{
namespace video 
{

class ShowHideFPSVideoView : 
  public Gtk::Button
{
  public:
    ShowHideFPSVideoView(std::shared_ptr<model::video::Video> videoModel, 
      std::shared_ptr<controller::video::ShowHideFPSVideoController> showHideFPSVideoController);
    virtual ~ShowHideFPSVideoView();

  protected:
    void onClicked();

  private:
    const Glib::ustring kLabelShow = "Show FPS";
    const Glib::ustring kLabelHide = "Hide FPS";
    const int kWidthButton = 100;
    const int kHeigthButton = 50;
    const int kMarginTop = 10;

    void buttonConfiguration();
    void updateLabel();

    const std::shared_ptr<model::video::Video> mVideoModel;
    std::shared_ptr<controller::video::ShowHideFPSVideoController> mShowHideFPSVideoController;
};

} // namespace video
} // namespace ui
} // namespace view

#endif //VIEW_UI_VIDEO_SHOWHIDEFPSVIDEOVIEW_HPP