#pragma once

#include "packedvector.h"
#include "graphics.h"

/** Components.h
 * Class for the vectors of componenets
 */

namespace iow
{

// deprecated
enum class ComponentTypes : uint64_t {};

using HP = float;
using HasHP = bool;
using Position = sf::Vector2f;
using Speed = sf::Vector2f;

class Components
{
    public:
	Components(size_t capacity);

	iow::PackedVector<HP> c_HP;
	iow::PackedVector<HasHP> c_HasHP;
	iow::PackedVector<Position> c_Position;
	iow::PackedVector<Speed> c_Speed;


	iow::PackedVector<sf::RectangleShape> c_RectAppearance;
	iow::PackedVector<sf::CircleShape> c_CircleAppearance;
};

} // namespace iow
