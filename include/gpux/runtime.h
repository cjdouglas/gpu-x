#pragma once

#include <cstddef>
#include <string_view>

#include "gpux/internal/definitions.h"

namespace gpux {
namespace runtime {
enum class XError { success, unknown };

enum class XMemcpyKind {
  host_to_host,
  host_to_device,
  device_to_host,
  device_to_device,
  default_copy,
};

// Device management

GPUX_API XError get_device(int* id);
GPUX_API XError set_device(int id);
GPUX_API XError get_device_count(int* count);
GPUX_API XError device_synchronize();
GPUX_API XError device_reset();

// Error handling

GPUX_API XError get_last_error();
GPUX_API XError peek_last_error();
GPUX_API std::string_view get_error_name(XError error);
GPUX_API std::string_view get_error_string(XError error);

// Stream Management

// TODO: stream class & functions

// Memory management

GPUX_API XError malloc(void** ptr, std::size_t size);
GPUX_API XError malloc_host(void** ptr, std::size_t size);
GPUX_API XError memcpy(void* dst, const void* src, std::size_t size,
                       XMemcpyKind copy_kind);

// TODO: implement streams
// GPUX_API XError gpu_memcpy_async(void* dst, const void* src, std::size_t
// size, XMemcpyKind copy_kind, const XStream& stream);

GPUX_API XError free(void* ptr);
GPUX_API XError free_host(void* ptr);

}  // namespace runtime
}  // namespace gpux
