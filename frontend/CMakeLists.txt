include(${PROJECT_SOURCE_DIR}/cmake/config.cmake)


set(TYPOR_FRONTEND_CONFIG_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(TYPOR_FRONTEND_CONFIG_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE TYPOR_FRONTEND_SOURCE_FILES ${TYPOR_FRONTEND_CONFIG_SOURCE_DIR}/*.cpp)


add_library(typor_frontend STATIC ${TYPOR_FRONTEND_SOURCE_FILES})
target_include_directories(typor_frontend PUBLIC ${TYPOR_FRONTEND_CONFIG_INCLUDE_DIR})
target_link_libraries(typor_frontend PUBLIC Typor::backend)

add_library(Typor::frontend ALIAS typor_frontend)
