#pragma once

#include "components.h"

iow::Components::Components(size_t capacity)
    : c_HP(capacity), c_HasHP(capacity), c_Position(capacity),
      c_Speed(capacity), c_RectAppearance(capacity),
      c_CircleAppearance(capacity)
{
}
