#include "common/Ball.hpp"
#include "common/Protocol.hpp"  

namespace pong {

Ball::Ball() {
	reset(0);
}

void Ball::reset(int lastLoser) {
	mX = constants::kFieldWidth * 0.5;
	mY = constants::kFieldHeight * 0.5;

	mVX = (lastLoser == 0) ? -constants::kBallSpeed : constants::kBallSpeed;
	mVY = 0;
}

void Ball::move(double dt) {
	mX += mVX * dt;  
	mY += mVY * dt;

	// vertical bounce check
	if (mY <= 0 && mVY < 0 ||
		mY + constants::kBallSize >= constants::kFieldHeight && mVY > 0) {
		mY = mY <= 0 ? 0 : constants::kFieldHeight - constants::kBallSize;
		mVY *= -1;
	};
}

} // namespace pong

