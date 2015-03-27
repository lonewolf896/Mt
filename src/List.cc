#include "objects/List.hh"

namespace Mt {
	namespace objects {	
		List::List(void)
		{ }

		List::List(std::initializer_list<Mt::core::INumeric>)
		{ }

		List::Add(Mt::core::INumeric value)
		{
			elements.push_back(value);
		}
	}
}
