#include "common/GameState.hpp"

namespace pong {

GameState::GameState() {
	resetPaddlesToStartingPositions();
}

void GameState::resetPaddlesToStartingPositions() {
	double centerY = (constants::kFieldHeight - constants::kPaddleHeight) * 0.5;

	double leftx = constants::kPaddleMargin;
	mPaddles[0].setX(leftx);
	mPaddles[0].setY(centerY);

	double rightx = constants::kFieldWidth - constants::kPaddleMargin - constants::kPaddleWidth;
	mPaddles[1].setX(rightx);
	mPaddles[1].setY(centerY);
}

// Runs a loop: move paddles, move ball, check collisions, check scoring
bool GameState::tick(const std::array<int, constants::kMaxPlayers>& inputs, double dt) {
	mServerTick++;

	// move paddles
	for (int i = 0; i < constants::kMaxPlayers; ++i) {
		mPaddles[i].move(inputs[i], dt);
	}

	// move ball
	mBall.move(dt);

	// check paddle/ball collision 
	// TODO: change deflection to be proportionate to kBallSpeed 
	for (int i = 0; i < constants::kMaxPlayers; ++i) {
		double px0 = mPaddles[i].x();
		double py0 = mPaddles[i].y();
		double px1 = px0 + constants::kPaddleWidth;
		double py1 = py0 + constants::kPaddleHeight;

		double bx0 = mBall.x();
		double by0 = mBall.y();
		double bx1 = bx0 + constants::kBallSize;
		double by1 = by0 + constants::kBallSize;

		const bool incoming = (i == 0 && mBall.vx() < 0) || (i == 1 && mBall.vx() > 0);
		if (!incoming) continue;

		const bool overlapping = bx0 < px1 && bx1 > px0 && by0 < py1 && by1 > py0;
		const double hitOffset = mBall.y() - (mPaddles[i].y() + (constants::kPaddleHeight * 0.5));
		const double snapX = (i == 0) ? px1 : px0 - constants::kBallSize;

		if (overlapping) {
			mBall.setPos(snapX, mBall.y());
			mBall.setVel(-mBall.vx(), mBall.vy() + hitOffset);
		}
	}

	// check and update scores
	if (mBall.x() + constants::kBallSize <= 0.0) {
		mScore[1]++; mBall.reset(0);
		resetPaddlesToStartingPositions();
		return true;
	}
	else if (mBall.x() >= constants::kFieldWidth) {
		mScore[0]++; mBall.reset(1);
		resetPaddlesToStartingPositions();
		return true;
	}

	return false;
}

} // namespace pong