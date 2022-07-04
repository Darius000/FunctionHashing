#pragma once

#include "Asset.h"
#include <filesystem>
#include "Renderer/Texture.h"
#include <future>


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

	static void LoadAssetsAtPath(std::filesystem::path path);

	static void TryLoadAsset(std::filesystem::directory_entry entry);

	template<typename T>
	static void LoadAsset(std::string_view filename, std::string_view path);

private:

	static void LoadAssetsAtPathAsync(std::filesystem::path path);

	template<typename AssetT>
	static std::unordered_map<std::string, Scope<Asset<AssetT>>> m_Assets;

};

template<>
inline void AssetManager::LoadAsset<Texture>(std::string_view filename, std::string_view path)
{
	auto texture = Texture::Create(path.data());

	if (texture)
	{	
		Add<Texture>(filename, texture);

		LOG_TRACE("Loaded {0}", filename.data());
	}
}

template<typename AssetT>
inline Ref<AssetT> AssetManager::Get(std::string_view name)
{
	
	if (Contains<AssetT>(name)) return m_Assets<AssetT>[name.data()]->Get();

	return nullptr;
}
