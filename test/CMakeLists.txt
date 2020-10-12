add_executable(testing main.cpp test_format.cpp test_trim.cpp)
target_include_directories(testing PUBLIC "${git-time_SOURCE_DIR}/include")
target_link_libraries(testing git2)
add_test(NAME git-time COMMAND testing -o report.xml)
