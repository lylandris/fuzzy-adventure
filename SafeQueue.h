#ifndef __SafeQueue_h
#define __SafeQueue_h

#include <queue>
#include <mutex>
#include <condition_variable>

namespace ctc
{
  template <typename T> class SafeQueue
  {
    public:
      SafeQueue(size_t depth);
      virtual ~SafeQueue();

      void EnQueue(T t);
      T DeQueue(void);

    private:
      std::queue<T> _q;
      mutable std::mutex _m;
      std::condition_variable _notEmpty;
      std::condition_variable _notFull;
      size_t _depth;
  };

  template <typename T> SafeQueue<T>::SafeQueue(size_t depth)
  {
    _depth = depth;
  }

  template <typename T> SafeQueue<T>::~SafeQueue(void)
  {
  }

  template <typename T> void SafeQueue<T>::EnQueue(T t)
  {
    std::unique_lock<std::mutex> lock(_m);
    _notFull.wait(lock, [&]{return (_q.size() != _depth);});
    _q.push(t);
    _notEmpty.notify_all();
  }

  template <typename T> T SafeQueue<T>::DeQueue(void)
  {
    std::unique_lock<std::mutex> lock(_m);
    _notEmpty.wait(lock, [&]{return !_q.empty();});
    T val = _q.front();
    _q.pop();
    _notFull.notify_all();

    return val;
  }
}

#endif //__SafeQueue_h
