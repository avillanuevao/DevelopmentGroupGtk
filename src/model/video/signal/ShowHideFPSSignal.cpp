#include "ShowHideFPSSignal.hpp"

namespace model
{
namespace video 
{
namespace signal
{
ShowHideFPSSignal::ShowHideFPSSignal(bool isShowingFPSVideo) :
    mIsShowingFPSVideo(isShowingFPSVideo)
{
}

bool ShowHideFPSSignal::getIsShowingFPSVideo()
{
    return mIsShowingFPSVideo;
}

} // namespace signal
} // namespace video
} // namespace model