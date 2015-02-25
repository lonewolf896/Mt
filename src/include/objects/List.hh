/*
	List.hh - A list of unordered non-unique objects
*/

#include "core/INumeric.hh"

#include <vector>
#include <initializer_list>


namespace Mt {
	namespace objects {
		/*! \class List
			\brief A collection of unordered non-unique objects

		*/
		class List : Mt::core::INumeric {
			public:
				std::vector<Mt::core::INumeric> elements;
			private:
				List(void);
				List(std::initializer_list<Mt::core::INumeric>);
		};	
	}
}
