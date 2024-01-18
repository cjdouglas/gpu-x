include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

set(GPUX_INSTALL_LIBDIR "${CMAKE_INSTALL_LIBDIR}/cmake/gpux")

install(
  TARGETS gpux
  EXPORT gpux_targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(
  EXPORT gpux-targets
  FILE gpux-targets.cmake
  NAMESPACE gpux::
  DESTINATION ${GPUX_INSTALL_LIBDIR})

write_basic_package_version_file(
  "gpuxConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)

# TODO: other config stuff
