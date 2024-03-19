#ifndef UTILS_DESIGNPATTERN_SIGNALPUBLISHER_HPP
#define UTILS_DESIGNPATTERN_SIGNALPUBLISHER_HPP

#include <algorithm>
#include <memory>
#include <vector>

#include <utils/designPattern/SignalSubscriber.hpp>

namespace utils
{
namespace designPattern
{

template <class TSignal>
class SignalPublisher
{
  public:
    SignalPublisher() = default;

    void addSubscriber(std::shared_ptr<SignalSubscriber<TSignal>> subscriber)
    {
      mSubscribers.push_back(subscriber);
    }

    void removeSubscriber(std::shared_ptr<SignalSubscriber<TSignal>> subscriber)
    {
      mSubscribers.erase(std::remove(mSubscribers.begin(), mSubscribers.end(), *subscriber),
                          mSubscribers.end());
    }

    void notifySubscribers(TSignal signal)
    {
      for (auto subscriber : mSubscribers)
      {
        subscriber->recievedSignal(signal);
      }
    }

  private:
    std::vector<std::shared_ptr<SignalSubscriber<TSignal>>> mSubscribers;

};

}  // namespace designPattern
}  // namespace utils

#endif  // UTILS_DESIGNPATTERN_SIGNALPUBLISHER_HPP
