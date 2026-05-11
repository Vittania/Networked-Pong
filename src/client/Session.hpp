#pragma once

#include "common/GameState.hpp"

#include <optional>

namespace pong {

class Session {
public:
	virtual ~Session() = default;

	virtual void update(double wallDt) = 0;

	virtual const GameState& state() const = 0;

	virtual std::optional<int> localPaddle() const = 0;

	virtual bool alive()	const = 0;
	virtual bool gameOver() const = 0;
	virtual int  winner()	const = 0;
};

} // namespace pong
