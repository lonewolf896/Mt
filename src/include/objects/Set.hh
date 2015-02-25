/*
	Set.hh - A structure that contains an unordered collection of unique items
*/

#include "core/INumeric.hh"

#include <vector>
#include <initializer_list>

namespace Mt {
	namespace objects {
		/*! \class Set
			\brief A collection of unique unordered objects

			This class represents a collection of unique unordered objects.
		*/
		class Set : Mt::core::INumeric {
			private:
				std::vector<Mt::core::INumeric> elements;
			public:
				Set(void);
				Set(std::initializer_list<Mt::core::INumeric>);
		};
	}
}
