#ifndef BLACKBOARD_H
#define BLACKBOARD_H

#include <Core/Core.h>
#include "BlackBoardKey.h"

using BlackBoardKeysList = std::vector<Ref<BlackBoardKey>>;

class BlackBoard
{
public:
	BlackBoard();

	BlackBoardKey* Create(std::string_view name, rttr::type type);

	void Add(BlackBoardKey* key);

	void Remove(const Ref<BlackBoardKey>& key);

	bool CanAdd(std::string_view name) const;

	bool Contains(std::string_view name) const;

	BlackBoardKeysList::iterator begin();

	BlackBoardKeysList::iterator end();

	BlackBoardKeysList::const_iterator cbegin() const;

	BlackBoardKeysList::const_iterator cend() const;

	BlackBoardKeysList& GetKeys() { return m_Keys; }

private:

	BlackBoardKeysList m_Keys;

	REFLECTABLEV();
};


#endif