add_executable(wtcli wtcli.cpp ../shared/SimpleUdp.cpp ../shared/ConfigureReader.cpp)
target_link_libraries(wtcli ws2_32)
