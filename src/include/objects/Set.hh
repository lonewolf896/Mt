/*
	Set.hh - A structure that contains an unordered collection of unique items
*/

#pragma once

#include "core/INumeric.hh"

#include <vector>
#include <algorithm>
#include <initializer_list>

namespace Mt {
	namespace objects {
		/*! \class Set
			\brief A collection of unique unordered objects

			This class represents a collection of unique unordered objects.
		*/
		template <class T>
		class Set : Mt::core::INumeric {
			private:
				std::vector<T> elements;
			public:
				Set(void);
				Set(std::initializer_list<T>);
				void Add(T value);
				int GetSize() const;

				T& operator[](int i);

				friend std::ostream& operator<<(std::ostream& os, Set<T>& set){
					os << "\n[";
					for(int i = 0; i < set.GetSize(); i++)
						os << set[i] << ",\t";
					os << "]\n";
					return os;
				}
		};

		template <class T>
		Set<T>::Set(void){}

		template <class T>
		Set<T>::Set(std::initializer_list<T>){}

		template <class T>
		void Set<T>::Add(T value) {
			if(std::none_of(elements.begin(), elements.end(), [&](T i){return i == value;}))
				elements.push_back(value);
		}

		template <class T>
		int Set<T>::GetSize() const{
			return elements.size();
		}

		template <class T>
		T& Set<T>::operator[](int i) {
			return elements[i];
		}
	}
}
