#include "objects/List.hh"

namespace Mt {
	namespace objects {	
		List::List(void)
		{ }

		List::List(std::initializer_list<Mt::core::IMtObject>)
		{ }

		void List::Add(Mt::core::IMtObject value)
		{
			elements.push_back(value);
		}
	}
}
