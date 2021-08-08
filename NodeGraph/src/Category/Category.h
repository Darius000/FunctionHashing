#pragma once

#include <string>
#include <vector>

struct CategoryList
{
	CategoryList() = default;
	CategoryList(CategoryList&& other)
	{
		m_Leafs = std::move(other.m_Leafs);
		m_SubCategories = std::move(other.m_SubCategories);
	}

	std::vector<std::string> m_Leafs;

	std::unordered_map<std::string, Scope<CategoryList>> m_SubCategories;
};