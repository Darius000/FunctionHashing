#include "PCH.h"
#include "Category.h"



void NodeCatgeories::AddCategory(const std::string& name, const std::string& description)
{
	CategoryList* currentCatgory = &NodeTypes();
	std::vector<std::string> categories;
	SplitString(name, "|", categories);

	size_t numCategories = categories.size();
	for (size_t i = 0; i < numCategories; i++)
	{
		auto& catname = categories[i];
		if (i != numCategories - 1)
		{
			//check if category already exists if not create a new one
			bool exists = currentCatgory->m_SubCategories.find(catname) != currentCatgory->m_SubCategories.end();
			if (exists)
			{
				currentCatgory = &*currentCatgory->m_SubCategories[catname];
			}
			else
			{
				CategoryList* newlist = new CategoryList();
				currentCatgory->m_SubCategories[catname] = std::unique_ptr<CategoryList>(newlist);
				currentCatgory = newlist;
			}
		}
		else
		{
			currentCatgory->m_Leafs.push_back(catname);
		}
	}
}

void NodeCatgeories::SplitString(const std::string& str, const std::string& delimiter, std::vector<std::string>& out)
{
	size_t pos = 0;
	size_t start;
	std::string token;

	while ((start = str.find_first_not_of(delimiter, pos)) != std::string::npos)
	{
		pos = str.find(delimiter, start);

		//add 1 to offset space character
		token = str.substr(start, pos - start);
		out.push_back(token);
	}
}

CategoryList& NodeCatgeories::NodeTypes()
{
	static CategoryList impl;
	return impl;
}
