#pragma once

namespace pong {

class Ball {
public:
	Ball();

	void reset(int lastLoser);

	void move(double dt);

	double x()  const { return mX; }
	double y()  const { return mY; }
	double vx() const { return mVX; }
	double vy() const { return mVY; }

	void setPos(double x, double y) { mX = x;  mY = y; }
	void setVel(double vx, double vy) { mVX = vx; mVY = vy; }

private:
	double mX = 0, mY = 0;
	double mVX = 0, mVY = 0;
};

} // namespace pong
