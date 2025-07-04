find_package(SQLite3 REQUIRED)

message("Enabling SQLite3 backend")

set(TYPOR_BACKEND_SQLITE_CONFIG_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(TYPOR_BACKEND_SQLITE_CONFIG_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE TYPOR_BACKEND_SQLITE_SOURCE_FILES ${TYPOR_BACKEND_SQLITE_CONFIG_SOURCE_DIR}/*.cpp)

add_library(typor_backend_sqlite STATIC ${TYPOR_BACKEND_SQLITE_SOURCE_FILES})
target_include_directories(typor_backend_sqlite PUBLIC ${TYPOR_BACKEND_SQLITE_CONFIG_INCLUDE_DIR})
target_link_libraries(typor_backend_sqlite PUBLIC Typor::backend SQLite::SQLite3)

add_library(Typor::sqlite_backend ALIAS typor_backend_sqlite)
