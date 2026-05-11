cmake_minimum_required(VERSION 3.28)
project(Pong LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    # keeps SFML's targets out of the build
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# common code that both the client and server need
# anything that links pong_common also gets sf::Packet/sf::TcpSocket included
add_library(pong_common STATIC
    src/common/Ball.cpp
    src/common/Paddle.cpp
    src/common/GameState.cpp
)
target_include_directories(pong_common PUBLIC src)
target_compile_features(pong_common PUBLIC cxx_std_17)
target_link_libraries(pong_common PUBLIC SFML::Network)

# pong_client: SFML window for input + rendering, plus networking.
add_executable(pong_client
    src/client/main.cpp
    src/client/Renderer.cpp
    src/client/LocalSession.cpp
)
target_link_libraries(pong_client PRIVATE pong_common SFML::Graphics)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    PROPERTY VS_STARTUP_PROJECT pong_client)
