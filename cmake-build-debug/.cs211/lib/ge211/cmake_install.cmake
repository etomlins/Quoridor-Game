# Install script for directory: /Users/ellen.tomlins/Desktop/Classes_archive/CS211/quoridor_final_project/.cs211/lib/ge211

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Library/Developer/CommandLineTools/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/ellen.tomlins/Desktop/Classes_archive/CS211/quoridor_final_project/cmake-build-debug/.cs211/lib/ge211/src/libge211.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libge211.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libge211.a")
    execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libge211.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES
    "/Users/ellen.tomlins/Desktop/Classes_archive/CS211/quoridor_final_project/.cs211/lib/ge211/include/"
    "/Users/ellen.tomlins/Desktop/Classes_archive/CS211/quoridor_final_project/cmake-build-debug/.cs211/lib/ge211/include/"
    FILES_MATCHING REGEX "/[^/]*\\.hxx$")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ge211" TYPE DIRECTORY FILES "/Users/ellen.tomlins/Desktop/Classes_archive/CS211/quoridor_final_project/.cs211/lib/ge211/Resources/")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/cmake/Ge211/Ge211Config.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/cmake/Ge211/Ge211Config.cmake"
         "/Users/ellen.tomlins/Desktop/Classes_archive/CS211/quoridor_final_project/cmake-build-debug/.cs211/lib/ge211/CMakeFiles/Export/5431a1aa8124badee94588c5300a5a41/Ge211Config.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/cmake/Ge211/Ge211Config-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/cmake/Ge211/Ge211Config.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/cmake/Ge211" TYPE FILE FILES "/Users/ellen.tomlins/Desktop/Classes_archive/CS211/quoridor_final_project/cmake-build-debug/.cs211/lib/ge211/CMakeFiles/Export/5431a1aa8124badee94588c5300a5a41/Ge211Config.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/cmake/Ge211" TYPE FILE FILES "/Users/ellen.tomlins/Desktop/Classes_archive/CS211/quoridor_final_project/cmake-build-debug/.cs211/lib/ge211/CMakeFiles/Export/5431a1aa8124badee94588c5300a5a41/Ge211Config-debug.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/cmake/Ge211" TYPE FILE FILES "/Users/ellen.tomlins/Desktop/Classes_archive/CS211/quoridor_final_project/cmake-build-debug/.cs211/lib/ge211/Ge211/Ge211ConfigVersion.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/ellen.tomlins/Desktop/Classes_archive/CS211/quoridor_final_project/cmake-build-debug/.cs211/lib/ge211/src/cmake_install.cmake")
  include("/Users/ellen.tomlins/Desktop/Classes_archive/CS211/quoridor_final_project/cmake-build-debug/.cs211/lib/ge211/example/cmake_install.cmake")

endif()

