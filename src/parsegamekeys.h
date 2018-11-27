#pragma once

#include "ecs.h"
#include "gameinput.h"
#include "resourcemanager.h"

/** parsegamekeys.h
 * Provides the function that makes the keyboard input magic happen. Not going
 * to lie, i really don't like this design and it needs to be cahnged in the
 * future to something that makes more sense. Putting the parseGameInput
 * functions as a void mutator to ecs might be a better idea.
 */

namespace iow
{

extern void parseGameKeys(iow::ECS &ecs, float const dt,
			  iow::ResourceManager const &resourceManager);
}
