add_executable(git-time main.cpp)
target_include_directories(git-time PUBLIC "${git-time_SOURCE_DIR}/include")
target_link_libraries(git-time git2)
install(TARGETS git-time DESTINATION bin)
