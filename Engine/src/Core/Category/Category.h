#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

struct Leaf
{
	std::string m_Name;
	std::string m_Description;
};

struct CategoryList
{
	CategoryList() = default;
	CategoryList(CategoryList&& other) noexcept
	{
		m_Leafs = std::move(other.m_Leafs);
		m_SubCategories = std::move(other.m_SubCategories);
	}

	std::vector<Leaf> m_Leafs;

	std::unordered_map<std::string, std::unique_ptr<CategoryList>> m_SubCategories;
};

struct NodeCatgeories
{
	static void AddCategory(const std::string& name, const std::string& description);

	static const CategoryList& GetCategoryList() { return NodeTypes(); }

private:

private:
	static CategoryList& NodeTypes();

};