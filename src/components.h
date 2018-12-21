#pragma once

#include "../extern/mmacros.h"
#include "collision.h"
#include "directions.h"
#include "graphics.h"
#include "packedvector.h"
#include "position.h"

/** Components.h
 * Class for the vectors of componenets
 */


namespace iow
{

#define IOW_COMPONENT_LIST                                                     \
	/*X_CPT(name, type) */                                                 \
                                                                               \
	/* tile map components*/                                               \
	X_CPT(TilePosition, sf ::Vector2f)                                     \
	X_CPT(TileAppearance, sf ::Sprite)                                     \
	X_CPT(TileCollisionLayer, CollisionBox)                                \
                                                                               \
	/* Player Components */                                                \
	X_CPT(IsPlayer, size_t)                                                \
	X_CPT(PlayerCollisionLayer, iow::CollisionBox)                         \
                                                                               \
	/* bullet components */                                                \
	X_CPT(IsBullet, bool)                                                  \
                                                                               \
	/* game components */                                                  \
	X_CPT(Direction, iow::Directions)                                      \
	X_CPT(Appearance, sf ::Sprite)                                         \
	X_CPT(Position, iow::Position)                                         \
	X_CPT(Speed, sf::Vector2f)                                             \
	X_CPT(HP, float)                                                       \
	X_CPT(HasHP, bool)

#define MK_COMPONENT_MEMBER_VAR_NAME(name) c_##name

// deprecated
enum class ComponentTypes : uint64_t {};

// Aliasing the types
#define X_CPT(name, type) using name = type;
IOW_COMPONENT_LIST
#undef X_CPT

class Components
{
    public:
	Components(size_t capacity);

	// generating the component lists
#define X_CPT(name, type)                                                      \
	iow::PackedVector<name> MK_COMPONENT_MEMBER_VAR_NAME(name);
	IOW_COMPONENT_LIST
#undef X_CPT
};

} // namespace iow
