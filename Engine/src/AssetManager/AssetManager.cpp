#include "PCH.h"
#include "AssetManager.h"

namespace fs = std::filesystem;

template<typename AssetT>
void AssetManager::Remove(std::string_view name)
{
	if (Contains<AssetT>(name))
	{
		m_Assets<AssetT>.erase(name);
	}
}



template<typename AssetT>
bool AssetManager::Contains(std::string_view name)
{
	return m_Assets<AssetT>.find(name.data()) != m_Assets<AssetT>.end();
}

template<typename T>
void AssetManager::LoadAsset(std::string_view filename, std::string_view path)
{
	
}


void AssetManager::LoadAssetsAtPath(std::filesystem::path path)
{
	LoadAssetsAtPathAsync(path);
}

void AssetManager::TryLoadAsset(std::filesystem::directory_entry entry)
{
	auto path = entry.path();
	auto filename = path.filename();
	auto ext = path.extension().string();

	if (!path.has_extension())
	{
		LOG_ERROR("Not a valid extension for {0}", filename.string());

		return;
	}

	if (Texture::IsValidExtension(ext.c_str()))
	{
		LoadAsset<Texture>(filename.string(), path.string());
	}
}

void AssetManager::LoadAssetsAtPathAsync(std::filesystem::path path)
{
	if (!fs::is_directory(path))
	{
		LOG_ERROR("Not a valid directory {0}", path.string());

		return;
	}

	for (auto& item : fs::recursive_directory_iterator(path))
	{
		if (item.is_directory())
		{
			continue;
		}

		if (item.is_regular_file())
		{
			TryLoadAsset(item);
		}
	}
}

template<typename AssetT>
inline void AssetManager::Add(std::string_view name, const Ref<AssetT>& asset)
{
	if (!Contains<AssetT>(name))
	{
		m_Assets<AssetT>.emplace(name.data(), new Asset<AssetT>(name.data(), asset));
	}
}

template<typename AssetT>
std::unordered_map<std::string, Scope<Asset<AssetT>>> AssetManager::m_Assets;

