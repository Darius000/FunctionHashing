#include "MakeVector.h"
#include "Reflection/Reflection.h"

REFLECT_INLINE(MakeVector2)
{
	rttr::registration::class_<MakeVector2>("Make Vector2")(rttr::metadata(ClassMetaData::Category, "Vector | "))
		.constructor<>()(rttr::policy::ctor::as_raw_ptr)
		.property("X", &MakeVector2::x)(rttr::metadata(EPropertyMetaData::PinType, EPinType::Input))
		.property("Y", &MakeVector2::y)(rttr::metadata(EPropertyMetaData::PinType, EPinType::Input))
		.property_readonly("Vec", &MakeVector2::GetVec)(rttr::metadata(EPropertyMetaData::PinType, EPinType::Output));
}

REFLECT_INLINE(MakeVector3)
{
	rttr::registration::class_<MakeVector3>("Make Vector3")(rttr::metadata(ClassMetaData::Category, "Vector | "))
		.constructor<>()(rttr::policy::ctor::as_raw_ptr)
		.property("X", &MakeVector3::x)(rttr::metadata(EPropertyMetaData::PinType, EPinType::Input))
		.property("Y", &MakeVector3::y)(rttr::metadata(EPropertyMetaData::PinType, EPinType::Input))
		.property("Z", &MakeVector3::z)(rttr::metadata(EPropertyMetaData::PinType, EPinType::Input))
		.property_readonly("Vec", &MakeVector3::GetVec)(rttr::metadata(EPropertyMetaData::PinType, EPinType::Output));
}

REFLECT_INLINE(MakeVector4)
{
	rttr::registration::class_<MakeVector4>("Make Vector4")(rttr::metadata(ClassMetaData::Category, "Vector | "))
		.constructor<>()(rttr::policy::ctor::as_raw_ptr)
		.property("X", &MakeVector4::x)(rttr::metadata(EPropertyMetaData::PinType, EPinType::Input))
		.property("Y", &MakeVector4::y)(rttr::metadata(EPropertyMetaData::PinType, EPinType::Input))
		.property("Z", &MakeVector4::z)(rttr::metadata(EPropertyMetaData::PinType, EPinType::Input))
		.property("W", &MakeVector4::w)(rttr::metadata(EPropertyMetaData::PinType, EPinType::Input))
		.property_readonly("Vec", &MakeVector4::GetVec)(rttr::metadata(EPropertyMetaData::PinType, EPinType::Output));
}

//------------Break Vector Reg-------------
REFLECT_INLINE(BreakVector2)
{
	rttr::registration::class_<BreakVector2>("Break Vector2")(rttr::metadata(ClassMetaData::Category, "Vector | "))
		.constructor<>()(rttr::policy::ctor::as_raw_ptr)
		.property_readonly("X", &BreakVector2::GetX)(rttr::metadata(EPropertyMetaData::PinType, EPinType::Output))
		.property_readonly("Y", &BreakVector2::GetY)(rttr::metadata(EPropertyMetaData::PinType, EPinType::Output))
		.property("Vec", &BreakVector2::vec)(rttr::metadata(EPropertyMetaData::PinType, EPinType::Input));
}

REFLECT_INLINE(BreakVector3)
{
	rttr::registration::class_<BreakVector3>("Break Vector3")(rttr::metadata(ClassMetaData::Category, "Vector | "))
		.constructor<>()(rttr::policy::ctor::as_raw_ptr)
		.property_readonly("X", &BreakVector3::GetX)(rttr::metadata(EPropertyMetaData::PinType, EPinType::Output))
		.property_readonly("Y", &BreakVector3::GetY)(rttr::metadata(EPropertyMetaData::PinType, EPinType::Output))
		.property_readonly("Z", &BreakVector3::GetZ)(rttr::metadata(EPropertyMetaData::PinType, EPinType::Output))
		.property("Vec", &BreakVector3::vec)(rttr::metadata(EPropertyMetaData::PinType, EPinType::Input));
}

REFLECT_INLINE(BreakVector4)
{
	rttr::registration::class_<BreakVector4>("Break Vector4")(rttr::metadata(ClassMetaData::Category, "Vector | "))
		.constructor<>()(rttr::policy::ctor::as_raw_ptr)
		.property_readonly("X", &BreakVector4::GetX)(rttr::metadata(EPropertyMetaData::PinType, EPinType::Output))
		.property_readonly("Y", &BreakVector4::GetY)(rttr::metadata(EPropertyMetaData::PinType, EPinType::Output))
		.property_readonly("Z", &BreakVector4::GetZ)(rttr::metadata(EPropertyMetaData::PinType, EPinType::Output))
		.property_readonly("W", &BreakVector4::GetW)(rttr::metadata(EPropertyMetaData::PinType, EPinType::Output))
		.property("Vec", &BreakVector4::vec)(rttr::metadata(EPropertyMetaData::PinType, EPinType::Input));
}
