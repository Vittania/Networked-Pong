#pragma once

namespace pong {

class Paddle {
public:
    Paddle();

    void move(int moveDir, double dt);

    double x() const { return mX; }
    double y() const { return mY; }
    void  setX(double x) { mX = x; }
    void  setY(double y) { mY = y; }

private:
    double mX = 0;
    double mY = 0;
};

} // namespace pong
