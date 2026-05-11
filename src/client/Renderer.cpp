#include "client/Renderer.hpp"
#include "common/Protocol.hpp"

namespace pong {

Renderer::Renderer() :
	mWindow(sf::VideoMode({ static_cast<unsigned>(constants::kFieldWidth),
						  static_cast<unsigned>(constants::kFieldHeight) }),
		"Pong (client)") {
	mWindow.setVerticalSyncEnabled(true);
}

void Renderer::pumpEvents() {
	while (const std::optional event = mWindow.pollEvent()) {
		if (event->is<sf::Event::Closed>()) mWindow.close();
		//if (event->is<sf::Event::FocusLost>()) // no input
	}
}

int Renderer::readPaddleInput(int slot) const {
	using K = sf::Keyboard::Key;

	bool up = false, down = false;

	if (slot == 0) {
		up = sf::Keyboard::isKeyPressed(K::W);
		down = sf::Keyboard::isKeyPressed(K::S);
	}
	else if (slot == 1) {
		up = sf::Keyboard::isKeyPressed(K::Up);
		down = sf::Keyboard::isKeyPressed(K::Down);
	}
	if (up && !down) return -1;
	if (down && !up) return +1;
	return 0;
}

void Renderer::draw(const GameState& state, std::optional<int> highlightSlot) {
	mWindow.clear(sf::Color(20, 20, 20));

	// draw center net 
	constexpr double segW = 4.0, segH = 12.0, gap = 8.0;
	sf::RectangleShape seg;
	seg.setSize({ segW, segH });
	seg.setFillColor(sf::Color(80, 80, 80, 128));
	const float midx = (constants::kFieldWidth - segW) * 0.5;

	for (float y = 0.f; y < constants::kFieldHeight; y += segH + gap) {
		seg.setPosition({ midx, y });
		mWindow.draw(seg);
	}

	// draw paddles with highlighting
	sf::RectangleShape paddle({ constants::kPaddleWidth, constants::kPaddleHeight });
	for (int i = 0; i < constants::kMaxPlayers; ++i) {
		sf::Color color;

		if (highlightSlot) {
			color = (i == *highlightSlot) ? local : remote;
		}
		else {
			color = (i == 0) ? hot0 : hot1;
		}

		paddle.setFillColor(color);
		paddle.setPosition({ static_cast<float>(state.paddle(i).x()), static_cast<float>(state.paddle(i).y()) });

		mWindow.draw(paddle);
	}

	// draw ball
	auto ball = sf::RectangleShape({ constants::kBallSize, constants::kBallSize });
	ball.setFillColor({ sf::Color::White });
	ball.setPosition({ static_cast<float>(state.ball().x()), static_cast<float>(state.ball().y()) });
	mWindow.draw(ball);

	mWindow.display();
}

} // namespace pong