#ifndef MODEL_VIDEO_VIDEO_HPP
#define MODEL_VIDEO_VIDEO_HPP

#include <iostream>

#include <utils/designPattern/SignalPublisher.hpp>
#include <model/video/signal/ShowHideFPSSignal.hpp>

namespace model
{
namespace video 
{

class Video : 
  public utils::designPattern::SignalPublisher<model::video::signal::ShowHideFPSSignal>
{
  public:
    Video();

    void setIsShowingFPS(bool value);
    bool getIsShowingFPS();

  private:
    bool mIsShowingFPS;
};

} // namespace video
} // namespace model

#endif //MODEL_VIDEO_VIDEO_HPP