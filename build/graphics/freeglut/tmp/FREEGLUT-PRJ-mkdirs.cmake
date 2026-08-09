# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "D:/7-Zip/code/build/graphics/freeglut/src/FREEGLUT-PRJ")
  file(MAKE_DIRECTORY "D:/7-Zip/code/build/graphics/freeglut/src/FREEGLUT-PRJ")
endif()
file(MAKE_DIRECTORY
  "D:/7-Zip/code/build/graphics/freeglut/src/FREEGLUT-PRJ-build"
  "D:/7-Zip/code/build/graphics/freeglut"
  "D:/7-Zip/code/build/graphics/freeglut/tmp"
  "D:/7-Zip/code/build/graphics/freeglut/src/FREEGLUT-PRJ-stamp"
  "D:/7-Zip/code/build/graphics/freeglut/src"
  "D:/7-Zip/code/build/graphics/freeglut/src/FREEGLUT-PRJ-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/7-Zip/code/build/graphics/freeglut/src/FREEGLUT-PRJ-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/7-Zip/code/build/graphics/freeglut/src/FREEGLUT-PRJ-stamp${cfgdir}") # cfgdir has leading slash
endif()
