#ifndef MODEL_VIDEO_VIDEO_HPP
#define MODEL_VIDEO_VIDEO_HPP

#include <iostream>

#include <utils/designPattern/SignalPublisher.hpp>
#include <model/video/signal/ShowHideFPSSignal.hpp>
#include <model/video/signal/PlayPauseVideoSignal.hpp>

namespace model
{
namespace video 
{

class Video : 
  public utils::designPattern::SignalPublisher<model::video::signal::ShowHideFPSSignal>,
  public utils::designPattern::SignalPublisher<model::video::signal::PlayPauseVideoSignal>
{
  public:
    Video();

    void setIsShowingFPS(bool value);
    bool getIsShowingFPS() const;
    void setIsPlayingVideo(bool value);
    bool getIsPlayingVideo() const;

  private:
    bool mIsShowingFPS;
    bool mIsPlayingVideo;
};

} // namespace video
} // namespace model

#endif //MODEL_VIDEO_VIDEO_HPP