/*
	IMtObject.hh - Root class for all objects that the Mt lexer, parser, and evaluation engine can work with
*/
#pragma once
#include <iostream>
namespace Mt {
	namespace core {
		/*! \class IMtObject
			\brief Base Object for SML 

			This is/was the planned base object for all SML related types, such as the Mt::Complex and Mt::Integer
			
		  \todo Implement some base logic
		*/
		class IMtObject {
		public:
			virtual ~IMtObject(void) { }
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#elif defined(__GCC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
			friend std::ostream& operator<<(std::ostream& os, const IMtObject& m) {
#if defined(__clang__)
#pragma clang diagnostic pop
#elif defined(__GCC__)
#pragma GCC diagnostics pop
#endif
					return (os << "DERP") ;
				}
		};



	}
}
