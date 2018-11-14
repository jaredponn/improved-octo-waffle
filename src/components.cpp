#include "components.h"

iow::Components::Components(size_t capacity)
    :
#define X_CPT(name, type) MK_COMPONENT_MEMBER_VAR_NAME(name)(capacity),
      ID_VA_ARGS(IOW_COMPONENT_LIST)
#undef X_CPT
{
}
