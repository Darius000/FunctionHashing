#include "Reflection/Reflection.h"
#include "BlackBoard/BlackBoard.h"
#include "BlackBoard/BlackBoardKey.h"

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
	rttr::registration::class_<TBlackBoardKey<int>>("BlackBoardKey-Int")
		.constructor<std::string_view>()(rttr::policy::ctor::as_raw_ptr)
		.property("Value", &TBlackBoardKey<int>::m_Value)(rttr::registration::public_access);


}

REFLECT_INLINE(TBlackBoardKey<float>)
{
	rttr::registration::class_<TBlackBoardKey<float>>("BlackBoardKey-Float")
		.constructor<std::string_view>()(rttr::policy::ctor::as_raw_ptr)
		.property("Value", &TBlackBoardKey<float>::m_Value)(rttr::registration::public_access);


}

REFLECT_INLINE(TBlackBoardKey<bool>)
{
	rttr::registration::class_<TBlackBoardKey<bool>>("BlackBoardKey-Bool")
		.constructor<std::string_view>()(rttr::policy::ctor::as_raw_ptr)
		.property("Value", &TBlackBoardKey<bool>::m_Value)(rttr::registration::public_access);
}

REFLECT_INLINE(TBlackBoardKey<std::string>)
{
	rttr::registration::class_<TBlackBoardKey<std::string>>("BlackBoardKey-String")
		.constructor<std::string_view>()(rttr::policy::ctor::as_raw_ptr)
		.property("Value", &TBlackBoardKey<std::string>::m_Value)(rttr::registration::public_access);
}