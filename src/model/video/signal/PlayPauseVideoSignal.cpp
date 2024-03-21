# include "PlayPauseVideoSignal.hpp"

namespace model
{
namespace video 
{
namespace signal
{
PlayPauseVideoSignal::PlayPauseVideoSignal(bool mustPlayVideo) :
    mMustPlayVideo(mustPlayVideo)
{
}

bool PlayPauseVideoSignal::mustPlayVideo() const
{
    return mMustPlayVideo;
}

} // namespace signal
} // namespace video
} // namespace model