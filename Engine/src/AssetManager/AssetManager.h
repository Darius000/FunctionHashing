#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include "Asset.h"
#include <filesystem>
#include "Renderer/Texture.h"


class AssetManager
{
	AssetManager() = delete;

public:

	template<typename AssetT>
	static void Add(std::string_view name, const Ref<AssetT>& asset);

	template<typename AssetT>
	static void Remove(std::string_view name);

	template<typename AssetT>
	static Ref<AssetT> Get(std::string_view name);

	template<typename AssetT>
	static bool Contains(std::string_view name);

	static bool LoadAssetsAtPath(std::filesystem::path path);

	static bool TryLoadAsset(std::filesystem::directory_entry entry);

	template<typename T>
	static bool LoadAsset(std::string_view filename, std::string_view path);

private:

	template<typename AssetT>
	static std::unordered_map<std::string, Scope<Asset<AssetT>>> m_Assets;
};

template<>
inline bool AssetManager::LoadAsset<Texture>(std::string_view filename, std::string_view path)
{
	auto texture = Texture::Create(path.data());

	if (texture)
	{
		Add<Texture>(filename, texture);

		LOG_TRACE("Loaded {0}", filename.data());

		return true;
	}

	return false;
}

template<typename AssetT>
inline Ref<AssetT> AssetManager::Get(std::string_view name)
{
	if (Contains<AssetT>(name)) return m_Assets<AssetT>[name.data()]->Get();

	return nullptr;
}

#endif // !ASSETMANAGER_H
