#include "PCH.h"
#include "Pin.h"
#include "DataTypes/Property.h"
#include "Node.h"


Pin::Pin()
{
	m_Connections = 0;
}

bool Pin::IsValidConnection(const Pin& pin, TEnum<EPinRejectReason>& reason) const
{
	bool is_not_connected = pinKind == ed::PinKind::Input ? m_Connections == 0 : true;
	bool same_kind = pinKind != pin.pinKind;
	bool same_type = GetPinType() == pin.GetPinType();

	if(!is_not_connected) reason = EPinRejectReason::AlreadyHasConnection;
	else if(!same_kind || !same_type) reason = EPinRejectReason::DifferentPinTypes;

	return same_kind && same_type && is_not_connected;
}

bool DataPin::IsValidConnection(const Pin& pin, TEnum<EPinRejectReason>& reason) const
{
	if(Pin::IsValidConnection(pin, reason) == false) return false;
	bool valid_property = (m_Property != nullptr && pin.GetProperty() != nullptr);
	bool same_data_type = valid_property ? m_Property->GetTypeName() == pin.GetProperty()->GetTypeName() : false;

	if(!valid_property) reason = EPinRejectReason::InValid;
	else if(!same_data_type) reason = EPinRejectReason::DifferentDataTypes;

	return valid_property && same_data_type;
}
