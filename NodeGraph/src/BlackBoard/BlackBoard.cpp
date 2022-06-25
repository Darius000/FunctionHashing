#include "BlackBoard.h"
#include "BlackBoardKey.h"
#include "Helpers/Vectors/VectorHelper.h"

BlackBoard::BlackBoard()
{
	Add(new TBlackBoardKey<int>("Int Key Default"));
}

BlackBoardKey* BlackBoard::Create(std::string_view name, rttr::type type)
{
	auto new_variant = type.create({name});
	auto new_key = new_variant.get_value<BlackBoardKey*>();

	assert(new_key != nullptr);

	return new_key;
};

void BlackBoard::Add(BlackBoardKey* key)
{
	if (!key) return;

	if (CanAdd(key->GetName()))
	{
		m_Keys.push_back(Ref<BlackBoardKey>(key));
	}
}

void BlackBoard::Remove(const Ref<BlackBoardKey>& key)
{
	auto name = key->GetName();
	if (Contains(name))
	{
		Helpers::Vector::Remove(m_Keys, [name](const Ref<BlackBoardKey>& item) {
			return item->GetName() == name;
		});
	}
}

bool BlackBoard::CanAdd(std::string_view name) const
{
	return !Contains(name);
}

bool BlackBoard::Contains(std::string_view name) const
{
	auto& it = std::find_if(cbegin(), cend(), [name](const Ref<BlackBoardKey>& item) {
		return item->GetName() == name;
		});

	return it != cend();
}

BlackBoardKeysList::iterator BlackBoard::begin()
{
	return m_Keys.begin();
}

BlackBoardKeysList::iterator BlackBoard::end()
{
	return m_Keys.end();
}

BlackBoardKeysList::const_iterator BlackBoard::cbegin() const
{
	return m_Keys.cbegin();
}

BlackBoardKeysList::const_iterator BlackBoard::cend() const
{
	return m_Keys.cend();
}
