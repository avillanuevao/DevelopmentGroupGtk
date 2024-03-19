#ifndef MODEL_VIDEO_SIGNAL_SHOWHIDEFPSSIGNAL_HPP
#define MODEL_VIDEO_SIGNAL_SHOWHIDEFPSSIGNAL_HPP

#include <iostream>

namespace model
{
namespace video 
{
namespace signal
{

class ShowHideFPSSignal
{
  public:
    ShowHideFPSSignal(bool isShowingFPSVideo);

    bool getIsShowingFPSVideo();

  private:
    bool mIsShowingFPSVideo;
};

} // namespace signal
} // namespace video
} // namespace model

#endif //MODEL_VIDEO_SIGNAL_SHOWHIDEFPSSIGNAL_HPP