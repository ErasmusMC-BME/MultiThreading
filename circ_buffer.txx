#ifndef circ_buffer_H_DEF
#define circ_buffer_H_DEF


#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/circular_buffer.hpp>
#include <vnl/vnl_vector.h>
#include <vnl/vnl_matrix.h>
// Thread safe circular buffer 
template <typename T>
class circ_buffer : private boost::noncopyable
{
public:
  typedef boost::mutex::scoped_lock lock;
  circ_buffer() {}
  circ_buffer(int n) {cb.set_capacity(n);}
  void send (T imdata) {
    lock lk(monitor);
    cb.push_back(imdata);
    buffer_not_empty.notify_one();
  }
  T receive() {
    lock lk(monitor);
    while (cb.empty())
      buffer_not_empty.wait(lk);
    T imdata = cb.front();
    cb.pop_front();
    return imdata;
  }
	  T back() {
    lock lk(monitor);
    while (cb.empty())
      buffer_not_empty.wait(lk);
    T imdata = cb.back();
    return imdata;
  }
  void clear() {
    lock lk(monitor);
    cb.clear();
  }
  int size() {
    lock lk(monitor);
    return cb.size();
  }
  void set_capacity(int capacity) {
    lock lk(monitor);
    cb.set_capacity(capacity);
  }
private:
  boost::condition buffer_not_empty;
  boost::mutex monitor;
  boost::circular_buffer<T> cb;
};
#endif
