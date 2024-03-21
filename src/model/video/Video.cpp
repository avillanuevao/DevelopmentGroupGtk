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

void Video::playVideo()
{
  mIsPlayingVideo = true;
  
  notifyPlayPauseVideo();
}

void Video::stopVideo()
{
  mIsPlayingVideo = false;
  
  notifyPlayPauseVideo();
}

bool Video::isPlayingVideo() const
{
    return mIsPlayingVideo;
}

void Video::notifyPlayPauseVideo()
{
  model::video::signal::PlayPauseVideoSignal signal(mIsPlayingVideo);
  utils::designPattern::SignalPublisher<model::video::signal::PlayPauseVideoSignal>::notifySubscribers(signal);
}

} // namespace video
} // namespace model