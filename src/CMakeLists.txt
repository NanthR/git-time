add_executable(git-time main.cpp check.cpp helpers.cpp commit_create.cpp)
target_include_directories(git-time PUBLIC "${git-time_SOURCE_DIR}/include"
                                           "${git-time_SOURE_DIR}/src")
target_link_libraries(git-time git2)
install(TARGETS git-time DESTINATION bin)
