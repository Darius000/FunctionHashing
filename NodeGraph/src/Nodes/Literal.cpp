#include "Literal.h"
#include <rttr/registration.h>

#define DEFINE_LITERAL(type, name)\
	REFLECT_INLINE(Literal<##type>)\
		{\
			rttr::registration::class_<Literal<##type>>(STRINGIFY_MACRO(name))\
				(rttr::metadata(ClassMetaData::Category, "Literal | "), \
				rttr::metadata(ClassMetaData::Description, STRINGIFY_MACRO(Literal name value)))\
				.constructor<>()(rttr::policy::ctor::as_raw_ptr)\
				.property("Value", &Literal<##type>::m_Value)(rttr::metadata("Kind", "Input"));\
		}

DEFINE_LITERAL(int32_t, Int)
DEFINE_LITERAL(uint32_t, UInt)
DEFINE_LITERAL(bool, Boolean)
DEFINE_LITERAL(float, Float)
DEFINE_LITERAL(std::string, String)
DEFINE_LITERAL(glm::vec2, Vector2)
DEFINE_LITERAL(glm::vec3, Vector3)
DEFINE_LITERAL(glm::vec4, Vector4)