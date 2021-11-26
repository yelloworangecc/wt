add_executable(wtcli wtcli.cpp ../shared/SimpleUdp.cpp)
target_link_libraries(wtcli ws2_32)
