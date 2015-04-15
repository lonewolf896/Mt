#include "objects/List.hh"

namespace Mt {
	namespace objects {	
		List::List(void)
		{ this->DerivedType = Mt::core::TYPE::LIST; }

		List::List(std::initializer_list<Mt::core::IMtObject>)
		{ this->DerivedType = Mt::core::TYPE::LIST; }

		void List::Add(Mt::core::IMtObject value)
		{
			elements.push_back(value);
		}
	}
}
