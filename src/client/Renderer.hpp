#pragma once

#include "common/GameState.hpp"

#include <SFML/Graphics.hpp>

#include <optional>

namespace pong {

class Renderer {
public:
	Renderer();

	bool isOpen() const { return mWindow.isOpen(); }

	// drain OS queue such as close, resize, focus
	void pumpEvents();

	// Process paddle input for the given slot
	// Called per paddle, per frame
	int readPaddleInput(int slot) const;

	// Draw net, ball, paddles
	void draw(const GameState& state, std::optional<int> highlightSlot);

private:
	sf::RenderWindow mWindow;
	sf::Color local = { 220, 220, 220 };
	sf::Color remote = { 110, 110, 110 };
	sf::Color hot0 = { 90, 200, 220 };
	sf::Color hot1 = { 220, 110, 90 };
};

} // namespace pong
