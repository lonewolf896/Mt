/*
	List.hh - A list of unordered non-unique objects
*/

#pragma once

#include "core/IMtObject.hh"

#include <vector>
#include <initializer_list>

namespace Mt {
	namespace objects {
		/*! \class List
			\brief A collection of unordered non-unique objects

		*/
		class List : Mt::core::IMtObject {
			public:
				std::vector<Mt::core::IMtObject> elements;
				List(void);
				List(std::initializer_list<Mt::core::IMtObject>);
				void Add(Mt::core::IMtObject value);
			private:
		};	
	}
}
