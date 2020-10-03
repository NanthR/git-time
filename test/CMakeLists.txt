ADD_EXECUTABLE(testing main.cpp test_format.cpp)
TARGET_INCLUDE_DIRECTORIES(testing PUBLIC "${git-time_SOURCE_DIR}/include")
TARGET_LINK_LIBRARIES(testing git2)
ADD_TEST(NAME git-time COMMAND testing -o report.xml)
