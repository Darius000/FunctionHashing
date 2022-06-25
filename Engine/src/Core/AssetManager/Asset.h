#ifndef ASSET_H
#define ASSET_H

#include "Core/Core.h"

template<typename T>
class Asset
{
public:

	Asset(const std::string& name, const Ref<T>& asset)
		:m_Name(name), m_WrappedAsset(asset)
	{

	}

	Ref<T> Get() { return m_WrappedAsset;  }

	const std::string& GetName() { return m_Name; }

private:

	Ref<T> m_WrappedAsset;

	std::string m_Name;
};


#endif // !ASSET_H
