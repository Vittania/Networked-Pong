#pragma once

#include "common/Ball.hpp"
#include "common/Paddle.hpp"
#include "common/Protocol.hpp"

#include <array>
#include <cstdint>

namespace pong {

class GameState {
public:
	GameState();
	
	bool tick(const std::array<int, constants::kMaxPlayers>& inputs, double dt);
	
	const Ball& ball()				const { return mBall; }
	const Paddle& paddle(int i)		const { return mPaddles[i]; }
	std::uint16_t score(int i)		const { return mScore[i]; }
	std::uint64_t serverTick()		const { return mServerTick; }

private:
	void resetPaddlesToStartingPositions();

	Ball mBall;
	std::array<Paddle, constants::kMaxPlayers> mPaddles;
	std::array<std::uint16_t, constants::kMaxPlayers> mScore{ 0, 0 };
	std::uint64_t mServerTick = 0;
};

} //namespace pong