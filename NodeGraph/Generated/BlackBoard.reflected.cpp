#include "Reflection/Reflection.h"
#include "BlackBoard/BlackBoard.h"
#include "BlackBoard/BlackBoardKey.h"
#include "Types/Color.h"

REFLECT_INLINE(BlackBoard)
{
	rttr::registration::class_<BlackBoard>("BlackBoard")
		.constructor<>()(rttr::policy::ctor::as_raw_ptr)
		.property("Keys", &BlackBoard::m_Keys);

}

REFLECT_INLINE(BlackBoardKey)
{
	rttr::registration::class_<BlackBoardKey>("BlackBoardKey")
		.constructor<>()(rttr::policy::ctor::as_raw_ptr);
}

REFLECT_INLINE(TBlackBoardKey<int>)
{
	rttr::registration::class_<TBlackBoardKey<int>>("BlackBoardKey-Int")(rttr::metadata("Color", Color(0.0f, 0.6f, 0.0f, 1.0f)))
		.constructor<std::string_view>()(rttr::policy::ctor::as_raw_ptr)
		.property("Value", &TBlackBoardKey<int>::m_Value)(rttr::registration::public_access);


}

REFLECT_INLINE(TBlackBoardKey<float>)
{
	rttr::registration::class_<TBlackBoardKey<float>>("BlackBoardKey-Float")(rttr::metadata("Color", Color(0.2f, 1.0f, 0.2f, 1.0f)))
		.constructor<std::string_view>()(rttr::policy::ctor::as_raw_ptr)
		.property("Value", &TBlackBoardKey<float>::m_Value)(rttr::registration::public_access);


}

REFLECT_INLINE(TBlackBoardKey<bool>)
{
	rttr::registration::class_<TBlackBoardKey<bool>>("BlackBoardKey-Bool")(rttr::metadata("Color", Color(1.0f, 0.0f, 0.0f, 1.0f)))
		.constructor<std::string_view>()(rttr::policy::ctor::as_raw_ptr)
		.property("Value", &TBlackBoardKey<bool>::m_Value)(rttr::registration::public_access);
}

REFLECT_INLINE(TBlackBoardKey<std::string>)
{
	rttr::registration::class_<TBlackBoardKey<std::string>>("BlackBoardKey-String")(rttr::metadata("Color", Color(1.0f, 0.5f, 0.5f, 1.0f)))
		.constructor<std::string_view>()(rttr::policy::ctor::as_raw_ptr)
		.property("Value", &TBlackBoardKey<std::string>::m_Value)(rttr::registration::public_access);
}

REFLECT_INLINE(TBlackBoardKey<glm::vec2>)
{
	rttr::registration::class_<TBlackBoardKey<glm::vec2>>("BlackBoardKey-Vec2")(rttr::metadata("Color", Color(0.1f, 0.1f, 1.0f, 1.0f)))
		.constructor<std::string_view>()(rttr::policy::ctor::as_raw_ptr)
		.property("Value", &TBlackBoardKey<std::string>::m_Value)(rttr::registration::public_access);
}

REFLECT_INLINE(TBlackBoardKey<glm::vec3>)
{
	rttr::registration::class_<TBlackBoardKey<glm::vec3>>("BlackBoardKey-Vec3")(rttr::metadata("Color", Color(1.0f, 1.0f, 0.0f, 1.0f)))
		.constructor<std::string_view>()(rttr::policy::ctor::as_raw_ptr)
		.property("Value", &TBlackBoardKey<std::string>::m_Value)(rttr::registration::public_access);
}

REFLECT_INLINE(TBlackBoardKey<glm::vec4>)
{
	rttr::registration::class_<TBlackBoardKey<glm::vec4>>("BlackBoardKey-Vec4")(rttr::metadata("Color", Color(1.0f, 0.5f, 0.0f, 1.0f)))
		.constructor<std::string_view>()(rttr::policy::ctor::as_raw_ptr)
		.property("Value", &TBlackBoardKey<std::string>::m_Value)(rttr::registration::public_access);
}