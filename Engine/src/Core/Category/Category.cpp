#include "PCH.h"
#include "Category.h"
#include "Utilities/StringUtilites.h"


void NodeCatgeories::AddCategory(const std::string& name, const std::string& description)
{
	CategoryList* currentCatgory = &NodeTypes();
	std::vector<std::string> categories;
	StringUtilites::SplitString(name, "|", categories);

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
			Leaf leaf{ catname, description };
			currentCatgory->m_Leafs.push_back(leaf);
		}
	}
}


CategoryList& NodeCatgeories::NodeTypes()
{
	static CategoryList impl;
	return impl;
}
