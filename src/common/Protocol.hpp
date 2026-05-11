#pragma once

#include <SFML/Network/Packet.hpp>
#include <cstdint>


namespace pong {
    // Networking schema goes here

namespace constants {
    inline constexpr unsigned short kDefaultPort = 53000;

    inline constexpr double kFieldWidth = 800.0;
    inline constexpr double kFieldHeight = 600.0;

    inline constexpr double kPaddleWidth = 12.0;
    inline constexpr double kPaddleHeight = 91.0;
    inline constexpr double kPaddleSpeed = 360.0;  
    inline constexpr double kPaddleMargin = 24.0;   

    inline constexpr double kBallSize = 12.0;
    inline constexpr double kBallSpeed = 380.0;     

    inline constexpr int    kTickRate = 240;    // esports networked pong baybee
    inline constexpr double kTickDt = 1.0 / static_cast<double>(kTickRate);

    inline constexpr int           kMaxPlayers = 2;
    inline constexpr std::uint16_t kWinScore = 9;
}

} // namespace pong
