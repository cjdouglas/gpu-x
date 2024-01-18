#pragma once

#include <cstddef>
#include <optional>
#include <utility>

#include "gpux/runtime.h"

namespace gpux {
namespace utility {
template <typename T>
class XBuffer {
 public:
  static XBuffer<T> create() noexcept { return XBuffer(); }

  static std::optional<XBuffer<T>> create(std::size_t size_bytes) noexcept {
    if (size_bytes == 0) {
      return XBuffer<T>();
    }

    XBuffer<T> buffer(size_bytes);
    if (!buffer.initialized()) {
      std::nullopt;
    }

    return buffer;
  }

  XBuffer(const XBuffer&) = delete;
  XBuffer& operator=(const XBuffer&) = delete;
  XBuffer(XBuffer&&) = default;
  XBuffer& operator=(XBuffer&&) {
    if (this == &other) {
      return *this;
    }

    if (initialized_) {
      deallocate();
    }

    handle_ = std::exchange(other.handle_, nullptr);
    size_ = std::exchange(other.size_, 0);
    initialized_ = std::exchange(other.initialized_, false);
    return *this;
  }
  ~XBuffer() { deallocate(); }

  T* handle() { return handle_; }
  const T* handle() const { return handle_; }
  std::size_t size() const { return size_; }
  bool initialized() const { return initialized_; }

 private:
  T* handle_;
  std::size_t size_;
  bool initialized_;

  explicit XBuffer() noexcept
      : handle_(nullptr), size_(0), initialized_(false) {}

  explicit XBuffer(const std::size_t size) noexcept { allocate(size); }

  void allocate(const std::size_t size) {
    void* ptr = static_cast<void*>(handle_);
    const runtime::XError err = runtime::malloc(&ptr, size);

    if (err == runtime::XError::success) {
      handle_ = static_cast<T*>(ptr);
      size_ = size;
      initialized_ = true;
    } else {
      handle_ = nullptr;
      size_ = 0;
      initialized_ = false;
    }
  }

  void deallocate() {
    if (initialized_) {
      runtime::free(handle_);
      handle_ = nullptr;
      size_ = 0;
      initialized_ = false;
    }
  }
};
}  // namespace utility
}  // namespace gpux
