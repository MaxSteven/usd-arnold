set(PLUGIN_NAME arnoldForUsdMaya)

include_directories(${USD_ROOT}/third_party/maya/include)
link_directories(${USD_ROOT}/third_party/maya/lib)

find_package(Maya)
include_directories(${MAYA_INCLUDE_DIRS})
link_directories(${MAYA_LIBRARY_DIR})

find_package(MtoA REQUIRED)
include_directories(${MTOA_INCLUDE_DIR})

find_package(USDArnold REQUIRED)
include_directories(${USD_ARNOLD_INCLUDE_DIR})

set(MAYA_LIBS OpenMaya Foundation OpenMayaAnim OpenMayaFX OpenMayaUI OpenMayaRender)

add_compile_options(-D_LINUX)

file(GLOB SRC *.cpp)

find_package(Boost COMPONENTS python REQUIRED)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

add_library(${PLUGIN_NAME} SHARED ${SRC})
set_target_properties(${PLUGIN_NAME} PROPERTIES PREFIX "")
target_link_libraries(${PLUGIN_NAME}
                      ${Boost_LIBRARIES}
                      ${PYTHON_LIBRARIES} ${MAYA_LIBS}
                      ${MTOA_mtoa_api_LIBRARY} tf gf sdf usd usdGeom ${USD_ARNOLD_LIBRARY} usdMaya)
set_target_properties(${PLUGIN_NAME} PROPERTIES INSTALL_RPATH_USE_LINK_PATH ON)

if ("${MTOA_ARCH_VERSION_NUM}" MATCHES "1")
    if ("${MTOA_MAJOR_VERSION_NUM}" MATCHES "2")
        target_compile_options(${PLUGIN_NAME} PRIVATE -DMTOA12)
    elseif ("${MTOA_MAJOR_VERSION_NUM}" MATCHES "4")
        target_compile_options(${PLUGIN_NAME} PRIVATE -DMTOA14)
    else ()
        message(FATAL_ERROR "Unsupported MtoA 1.x version: ${MTOA_VERSION)")
    endif ()
endif ()

install(TARGETS ${PLUGIN_NAME}
        DESTINATION plug-ins)

set(PLUGINFO_OUT ${CMAKE_CURRENT_BINARY_DIR}/plugInfo.json)
configure_file(plugInfo.json.in ${PLUGINFO_OUT})

install(FILES ${PLUGINFO_OUT}
        DESTINATION .)
