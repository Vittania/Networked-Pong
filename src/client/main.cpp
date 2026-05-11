#include "client/Renderer.hpp"
#include "client/Session.hpp"
#include "client/LocalSession.hpp"
#include "common/Protocol.hpp"

#include <SFML/System/Clock.hpp>

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

int main(int argc, char** argv) {
    bool           modeLocal = false;
    std::string    host = "127.0.0.1";
    unsigned short port = pong::constants::kDefaultPort;

    // Parse launch args: 
    // <host> [port]            connects to remote server
    //                          default connect to 127.0.0.1 : kDefaultPort
    // --local                  standalone hotseat
    // TODO: --listen [port]    host as player
    // Stretch: get rid of this and have a lobby
    bool hostSet = false;
    for (int i = 1; i < argc; ++i) {
        std::string a = argv[i];
        if (a == "--local") { modeLocal = true; continue; }
        if (a.rfind("--", 0) == 0) {
            std::cerr << "Unknown flag: " << a << "\n";
            return 1;
        }
        if (!hostSet) { host = a; hostSet = true; }
        else { port = static_cast<unsigned short>(std::atoi(a.c_str())); }
    }

    // Create a session based on launch args
    pong::Renderer renderer;
    std::unique_ptr<pong::Session> session;

    if (modeLocal) {
        std::cout << "Local hotseat. P0 = W/S, P1 = Up/Down.\n";
        session = std::make_unique<pong::LocalSession>(renderer);
    }
    else {
        // TODO: network mode
    }

    // Main loop
    sf::Clock clock;
    while (renderer.isOpen() && session->alive()) {
        const double wallDt = clock.restart().asSeconds();

        renderer.pumpEvents();
        session->update(wallDt);
        renderer.draw(session->state(), session->localPaddle());

        if (session->gameOver()) {
            std::cout << "Game over -- player " << session->winner() << " wins.\n";
            // TODO: "press R to play again / Esc to quit" overlay 
            break;
        }
    }
    return 0;
}
