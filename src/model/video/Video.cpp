#include "Video.hpp"

namespace model
{
namespace video 
{

Video::Video() :
    mIsShowingFPS(false)
{
}

void Video::setIsShowingFPS(bool value)
{
  mIsShowingFPS = value;

  model::video::signal::ShowHideFPSSignal signal(mIsShowingFPS);
  notifySubscribers(signal);
}

bool Video::getIsShowingFPS()
{
  return mIsShowingFPS;
}

} // namespace video
} // namespace model