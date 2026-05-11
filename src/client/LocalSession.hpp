#pragma once

#include "client/Renderer.hpp"
#include "client/Session.hpp"
#include "common/GameState.hpp"

namespace pong {

class LocalSession : public Session{
public:
	explicit LocalSession(Renderer& input);

	void update(double wallDt) override;
	const GameState& state() const override { return mState; }
	std::optional<int> localPaddle() const override { return std::nullopt; }
	bool alive()    const override { return true; }
	bool gameOver() const override { return mGameOver; }
	int  winner()   const override { return mWinner; }

private:
	Renderer*  mInput;          
	GameState  mState;
	double     mAccumulator = 0.0;   
	bool       mGameOver = false;
	int        mWinner = -1;
};

} // namespace pong