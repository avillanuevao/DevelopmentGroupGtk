#ifndef CONTROLLER_VIDEO_SHOWHIDEFPSCONTROLLER_HPP
#define CONTROLLER_VIDEO_SHOWHIDEFPSCONTROLLER_HPP

#include <iostream>
#include <memory>

#include <model/video/Video.hpp>

namespace controller
{
namespace video 
{

class ShowHideFPSVideoController
{
  public:
    ShowHideFPSVideoController(std::shared_ptr<model::video::Video> videoModel);

    void showHideFPSVideo();

  private:
    std::shared_ptr<model::video::Video> mVideoModel;
};

} // namespace video
} // namespace controller

#endif //CONTROLLER_VIDEO_SHOWHIDEFPSCONTROLLER_HPP