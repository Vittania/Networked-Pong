#include "common/Paddle.hpp"
#include "common/Protocol.hpp"

namespace pong {

Paddle::Paddle() {}

void Paddle::move(int moveDir, double dt) {
	mY += moveDir * constants::kPaddleSpeed * dt;
	// clamps
	mY = mY <= 0.0 ? 0.0 : mY;
	double ceiling = constants::kFieldHeight - constants::kPaddleHeight;
	mY = mY >= ceiling ? ceiling: mY;
}

} // namespace pong
