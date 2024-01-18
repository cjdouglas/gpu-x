#include <hip/hip_runtime.h>

#include "gpux/runtime.h"

namespace gpux {
namespace runtime {
namespace {
XError hip_to_xerror(const hipError_t err) {
  switch (err) {
    case hipSuccess:
      return XError::success;
    case hipErrorUnknown:
      return XError::unknown;
    default:
      return XError::unknown;
  }
}

hipError_t xerror_to_hip(const XError err) {
  switch (err) {
    case XError::success:
      return hipSuccess;
    case XError::unknown:
      return hipErrorUnknown;
    default:
      return hipErrorUnknown;
  }
}

hipMemcpyKind map_memcpy_kind(const XMemcpyKind copy_kind) {
  switch (copy_kind) {
    case XMemcpyKind::host_to_host:
      return hipMemcpyHostToHost;
    case XMemcpyKind::host_to_device:
      return hipMemcpyHostToDevice;
    case XMemcpyKind::device_to_host:
      return hipMemcpyDeviceToHost;
    case XMemcpyKind::device_to_device:
      return hipMemcpyDeviceToDevice;
    case XMemcpyKind::default_copy:
      return hipMemcpyDefault;
    default:
      return hipMemcpyDefault;
  }
}
}  // namespace

// Memory management

XError malloc(void** ptr, const std::size_t size) {
  return hip_to_xerror(hipMalloc(ptr, size));
}

XError malloc_host(void** ptr, const std::size_t size) {
  return hip_to_xerror(hipHostMalloc(ptr, size));
}

XError memcpy(void* dst, const void* src, const std::size_t size,
              const XMemcpyKind copy_kind) {
  return hip_to_xerror(hipMemcpy(dst, src, size, map_memcpy_kind(copy_kind)));
}

XError free(void* ptr) { return hip_to_xerror(hipFree(ptr)); }

XError free_host(void* ptr) { return hip_to_xerror(hipHostFree(ptr)); }

}  // namespace runtime
}  // namespace gpux
