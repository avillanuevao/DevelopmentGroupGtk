# include "PlayPauseVideoSignal.hpp"

namespace model
{
namespace video 
{
namespace signal
{
PlayPauseVideoSignal::PlayPauseVideoSignal(bool isPlayingVideo) :
    mIsPlayingVideo(isPlayingVideo)
{
}

bool PlayPauseVideoSignal::getIsPlayingVideo()
{
    return mIsPlayingVideo;
}

} // namespace signal
} // namespace video
} // namespace model