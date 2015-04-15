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
		template <class T>
		class List : Mt::core::IMtObject {
		private:
			std::vector<T> elements;
		public:
			List(void);
			List(std::initializer_list<T>);
			void Add(T value);
			int GetSize() const;

			T& operator[](int i);

			friend std::ostream& operator<<(std::ostream& os, List<T>& list){
				os << "\n[";
				for(int i = 0; i < list.GetSize(); i++)
					os << list[i] << ",\t";
				os << "]\n";
				return os;
			}
		};

		template <class T>
		List<T>::List() {
			this->DerivedType = Mt::core::TYPE::LIST;
		}

		template <class T>
		List<T>::List(std::initializer_list<T>) {
			this->DerivedType = Mt::core::TYPE::LIST;
		}

		template <class T>
		void List<T>::Add(T value) {
			elements.push_back(value);
		}

		template <class T>
		int List<T>::GetSize() const{
			return elements.size();
		}

		template <class T>
		T& List<T>::operator[](int i) {
			return elements[i];
		}
	}
}
