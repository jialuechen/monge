project(monge)

cmake_minimum_required(VERSION 3.2.0)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set (CMAKE_CXX_STANDARD 11)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(USE_CIMAGE true)

if(USE_CIMAGE)
    add_definitions(-D_cimg_)
    add_definitions(-Dcimg_display=0)

    find_package(PNG)
    if(PNG_FOUND)
        add_definitions(-Dcimg_use_png)
        set(ALLLIBS ${ALLLIBS} PNG::PNG)
    endif()

    find_package(JPEG)
    if(JPEG_FOUND)
        add_definitions(-Dcimg_use_jpeg)
        set(ALLLIBS ${ALLLIBS} JPEG::JPEG)
    endif()

   if(WIN32)
      add_definitions(-Dcimg_OS=2)
   else()
      add_definitions(-Dcimg_OS=0)
   endif()
endif()

include_directories(extern/)
include_directories(monge/)

find_package(Cholmod)
if(CHOLMOD_FOUND)
  message(STATUS "Enable Cholmod support")
  add_definitions("-DHAS_CHOLMOD")
  include_directories(${CHOLMOD_INCLUDES})
  set(ALLLIBS ${ALLLIBS} ${CHOLMOD_LIBRARIES})
else()
  message(STATUS "Disable Cholmod support (not found)")
  message(WARNING "Chomod not found, solving will be significantly slower than expected.")
endif()

## FILES ##########################################################################
set(SURFACE_MESH_SRC_FILES
    monge/surface_mesh/IO.cpp
    monge/surface_mesh/IO_off.cpp
    monge/surface_mesh/IO_obj.cpp
    monge/surface_mesh/Surface_mesh.cpp
)

set(SURFACE_MESH_HEADER_FILES
    monge/surface_mesh/IO.h
    monge/surface_mesh/properties.h
    monge/surface_mesh/Surface_mesh.h
    monge/surface_mesh/types.h
    monge/surface_mesh/Vector.h
)

set(OTSOLVER_SRC_FILES
    monge/transport_map.cpp
    monge/otsolver_2dgrid.cpp
    monge/details/line_search.cpp
    monge/details/nested_dissection.cpp
    monge/utils/bvh2d.cpp
    monge/utils/rasterizer.cpp
    monge/utils/stochastic_rasterizer.cpp
    monge/utils/mesh_utils.cpp
)

set(OTSOLVER_HEADER_FILES
    monge/transport_map.h
    monge/otsolver_2dgrid.h
    monge/details/line_search.h
    monge/details/nested_dissection.h
    monge/utils/bvh2d.h
    monge/utils/rasterizer.h
    monge/utils/stochastic_rasterizer.h
    monge/utils/mesh_utils.h
)

###################################################################################

add_definitions(-DDATA_DIR="${PROJECT_SOURCE_DIR}/data")

if(NOT WIN32)
   add_definitions(-DENABLE_SSE_MODE)
else()
    add_definitions(-D_USE_MATH_DEFINES)
endif()

add_library(monge ${SURFACE_MESH_SRC_FILES} ${OTSOLVER_SRC_FILES})



set(OTAPPUTILS_SRC_FILES
    apps/common/image_utils.cpp
    apps/common/inputparser.cpp
    apps/common/analytical_functions.cpp
    apps/common/generic_tasks.cpp
)

set(OTAPPUTILS_HEADER_FILES
    apps/common/image_utils.h
    apps/common/inputparser.h
    apps/common/analytical_functions.h
    apps/common/generic_tasks.h
    apps/common/otsolver_options.h
)

add_library(otapputils ${OTAPPUTILS_SRC_FILES})

add_executable(monge apps/monge)
target_link_libraries(monge otapputils monge ${ALLLIBS})

add_executable(stippling apps/stippling.cpp)
target_link_libraries(stippling otapputils monge ${ALLLIBS})

add_executable(barycenters apps/barycenters.cpp)
target_link_libraries(barycenters otapputils monge ${ALLLIBS})
