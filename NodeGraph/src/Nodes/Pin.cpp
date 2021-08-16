#include "PCH.h"
#include "Pin.h"
#include "DataTypes/Property.h"
#include "Node.h"


Pin::Pin()
{
	m_Connections = 0;
}

bool Pin::IsValidConnection(const Pin& pin) const
{
	bool is_not_connected = pinKind == ed::PinKind::Input ? m_Connections == 0 : true;
	bool same_kind = pinKind != pin.pinKind;
	bool same_type = GetPinType() == pin.GetPinType();
	return same_kind && same_type && is_not_connected;
}

bool DataPin::IsValidConnection(const Pin& pin) const
{
	if(Pin::IsValidConnection(pin) == false) return false;
	if(m_Property == nullptr || pin.GetProperty() == nullptr) return false;
	if(m_Property->GetTypeName() != pin.GetProperty()->GetTypeName()) return false;

	return true;
}
