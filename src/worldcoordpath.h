#pragma once

#include "logger.h"
#include "position.h"

#include <cmath>
#include <optional>
#include <vector>

namespace iow
{

struct WorldCoordPath {
	std::vector<iow::Position> path;
	float popRadius;

    public:
	WorldCoordPath(float r);

	// updates the path to get the next one if necassarray. if not
	// necassary, don't pop
	void updatePath(iow::Position const &pos);

	// peek at the next coord
	iow::Position peekNextWorldCoordInWorldCoordPath();

    public: // setters
	// peek at the next coord
	void setPath(std::vector<iow::Position> const &path);
	void setDestination(iow::Position const &pos);
};

inline WorldCoordPath::WorldCoordPath(float r)
{
	path = std::vector<iow::Position>();
	popRadius = r;
}

inline iow::Position WorldCoordPath::peekNextWorldCoordInWorldCoordPath()
{
	if (path.empty()) {
		Logger::logMessage("Error in WorldCordPath -- vector is empty");
	}

	iow::Position const tmp = path.back();

	return tmp;
}

inline void WorldCoordPath::updatePath(iow::Position const &pos)
{
	if (path.size() <= 1)
		return;

	if (absVec(pos - peekNextWorldCoordInWorldCoordPath()) < popRadius) {
		path.pop_back();
	}
}

inline void WorldCoordPath::setPath(std::vector<iow::Position> const &p)
{
	path = p;
}

inline void WorldCoordPath::setDestination(iow::Position const &pos)
{
	path[0] = pos;
}

} // namespace iow
