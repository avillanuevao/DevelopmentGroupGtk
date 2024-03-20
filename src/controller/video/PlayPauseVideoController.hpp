#ifndef CONTROLLER_VIDEO_PLAYPAUSEVIDEOCONTROLLER_HPP
#define CONTROLLER_VIDEO_PLAYPAUSEVIDEOCONTROLLER_HPP

#include <iostream>
#include <memory>

#include <model/video/Video.hpp>

namespace controller
{
namespace video 
{

class PlayPauseVideoController
{
  public:
    PlayPauseVideoController(std::shared_ptr<model::video::Video> model);

    void playPauseVideo();

  private:
    std::shared_ptr<model::video::Video> mModel;
};

} // namespace video
} // namespace controller

#endif //CONTROLLER_VIDEO_PLAYPAUSEVIDEOCONTROLLER_HPP