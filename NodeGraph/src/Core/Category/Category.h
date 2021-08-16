#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

struct CategoryList
{
	CategoryList() = default;
	CategoryList(CategoryList&& other) noexcept
	{
		m_Leafs = std::move(other.m_Leafs);
		m_SubCategories = std::move(other.m_SubCategories);
	}

	std::vector<std::string> m_Leafs;

	std::unordered_map<std::string, std::unique_ptr<CategoryList>> m_SubCategories;
};

struct NodeCatgeories
{
	static void AddCategory(const std::string& name, const std::string& description);

	static const CategoryList& GetCategoryList() { return NodeTypes(); }

private:
	static void SplitString(const std::string& str,
		const std::string& delimiter, std::vector<std::string>& out);
private:
	static CategoryList& NodeTypes();

};