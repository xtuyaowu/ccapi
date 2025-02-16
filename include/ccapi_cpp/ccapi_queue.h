#ifndef INCLUDE_CCAPI_CPP_CCAPI_QUEUE_H_
#define INCLUDE_CCAPI_CPP_CCAPI_QUEUE_H_
#include <mutex>
#include <queue>
#include <vector>

#include "ccapi_cpp/ccapi_logger.h"
namespace ccapi {
template <class T>
/**
 * This class represents a generic FIFO queue.
 */
class Queue {
 public:
  std::string EXCEPTION_QUEUE_FULL = "queue is full";
  std::string EXCEPTION_QUEUE_EMPTY = "queue is empty";
  explicit Queue(const size_t maxSize = 0) : maxSize(maxSize) {}
  void pushBack(T&& t) {
    std::lock_guard<std::mutex> lock(this->m);
    if (this->maxSize <= 0 || this->queue.size() < this->maxSize) {
      CCAPI_LOGGER_TRACE("this->queue.size() = " + size_tToString(this->queue.size()));
      this->queue.push_back(t);
    } else {
      throw std::runtime_error(EXCEPTION_QUEUE_FULL);
    }
  }
  T popBack() {
    std::lock_guard<std::mutex> lock(this->m);
    if (this->queue.empty()) {
      throw std::runtime_error(EXCEPTION_QUEUE_EMPTY);
    } else {
      T t = std::move(this->queue.back());
      this->queue.pop_back();
      return t;
    }
  }
  std::vector<T> purge() {
    std::lock_guard<std::mutex> lock(this->m);
    std::vector<T> p;
    std::swap(p, this->queue);
    return p;
  }
  void removeAll(std::vector<T>& c) {
    std::lock_guard<std::mutex> lock(this->m);
    if (c.empty()) {
      c = std::move(this->queue);
    } else {
      c.reserve(c.size() + this->queue.size());
      std::move(std::begin(this->queue), std::end(this->queue), std::back_inserter(c));
    }
    this->queue.clear();
  }
  size_t size() const {
    std::lock_guard<std::mutex> lock(this->m);
    return this->queue.size();
  }
  bool empty() const {
    std::lock_guard<std::mutex> lock(this->m);
    return this->queue.empty();
  }
#ifndef CCAPI_EXPOSE_INTERNAL

 private:
#endif
  std::vector<T> queue;
  mutable std::mutex m;
  size_t maxSize{};
};
} /* namespace ccapi */
#endif  // INCLUDE_CCAPI_CPP_CCAPI_QUEUE_H_
