#ifndef UTILS_DESIGNPATTERN_SIGNALSUBSCRIBER_HPP
#define UTILS_DESIGNPATTERN_SIGNALSUBSCRIBER_HPP

namespace utils
{
namespace designPattern
{

template <class TSignal>
class SignalSubscriber
{
  public:
    SignalSubscriber() = default;
    virtual ~SignalSubscriber(){}

    virtual void recievedSignal(TSignal signal) = 0;
};

}  // namespace designPattern
}  // namespace utils

#endif  // UTILS_DESIGNPATTERN_SIGNALSUBSCRIBER_HPP
