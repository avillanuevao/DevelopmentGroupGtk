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
    ShowHideFPSVideoView(std::shared_ptr<model::video::Video> model, 
      std::shared_ptr<controller::video::ShowHideFPSVideoController> controller);
    virtual ~ShowHideFPSVideoView();

  protected:
    void onClicked();

  private:
    void updateLabel();

    std::shared_ptr<model::video::Video> mModel;
    std::shared_ptr<controller::video::ShowHideFPSVideoController> mController;
    Glib::ustring mLabelShow = "Show FPS";
    Glib::ustring mLabelHide = "Hide FPS";
};

} // namespace video
} // namespace ui
} // namespace view

#endif //VIEW_UI_VIDEO_SHOWHIDEFPSVIDEOVIEW_HPP