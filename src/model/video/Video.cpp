#include "Video.hpp"

namespace model
{
namespace video 
{

Video::Video() :
    mIsShowingFPS(false), mIsPlayingVideo(true)
{
}

void Video::setIsShowingFPS(bool value)
{
  mIsShowingFPS = value;

  model::video::signal::ShowHideFPSSignal signal(mIsShowingFPS);
  utils::designPattern::SignalPublisher<model::video::signal::ShowHideFPSSignal>::notifySubscribers(signal);
}

bool Video::getIsShowingFPS() const 
{
  return mIsShowingFPS;
}

void Video::setIsPlayingVideo(bool value)
{
  mIsPlayingVideo = value;
  
  model::video::signal::PlayPauseVideoSignal signal(mIsPlayingVideo);
  utils::designPattern::SignalPublisher<model::video::signal::PlayPauseVideoSignal>::notifySubscribers(signal);
}

bool Video::getIsPlayingVideo() const
{
    return mIsPlayingVideo;
}

} // namespace video
} // namespace model