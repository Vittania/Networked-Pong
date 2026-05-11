#include "client/LocalSession.hpp"
#include "client/Renderer.hpp"
#include "common/Protocol.hpp"

#include <array>

namespace pong {

LocalSession::LocalSession(Renderer& input) : mInput(&input) {}

void LocalSession::update(double wallDt) {
	mAccumulator += wallDt;
	if (mAccumulator > 0.25) mAccumulator = 0.25;

	std::array<int, constants::kMaxPlayers> inputs{};
	inputs[0] = mInput->readPaddleInput(0);
	inputs[1] = mInput->readPaddleInput(1);

	while (mAccumulator >= constants::kTickDt) {
		mAccumulator -= constants::kTickDt;

		const bool scored = mState.tick(inputs, constants::kTickDt);
		if (!scored) continue;

		for (int i = 0; i < constants::kMaxPlayers; ++i) {
			if (mState.score(i) >= constants::kWinScore) {
				mWinner = i;
				mGameOver = true;
				break;
			}
		}
		
		if (mGameOver) break;
	}	
}

} // namespace pong