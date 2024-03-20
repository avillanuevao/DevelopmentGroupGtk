#ifndef MODEL_VIDEO_SIGNAL_PLAYPAUSEVIDEOSIGNAL_HPP
#define MODEL_VIDEO_SIGNAL_PLAYPAUSEVIDEOSIGNAL_HPP

#include <iostream>

namespace model
{
namespace video 
{
namespace signal
{

class PlayPauseVideoSignal
{
  public:
    PlayPauseVideoSignal(bool isPlayingVideo);

    bool getIsPlayingVideo();

  private:
    bool mIsPlayingVideo;
};

} // namespace signal
} // namespace video
} // namespace model

#endif //MODEL_VIDEO_SIGNAL_PLAYPAUSEVIDEOSIGNAL_HPP