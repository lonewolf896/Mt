/*
	INumeric.hh - Base class for complex and any other special numbers (I.E Rational numbers, etc)
*/
#pragma once
#include "IMtObject.hh"
#include "Types.hh"
namespace Mt {
	namespace core {
		/*! \class INumeric
			\brief Core numeric implementation

			This abstract class is the base for all Mt numeric implementations, such as Mt::Complex, Mt::Integer, and Mt::Double,
			this allows for all of those types to be operated on by each other, and also allows for uniformity amoung the internal
			system.
		*/
		class INumeric : public IMtObject {
			public:
			// Disable default move and copy constructors for the interface
			INumeric(void) { }
			// This glob of pragmas is to stop the compiler from complaining about our
			// unused inum in the copy and move constructors, prevents the release build
			// from failing
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#elif defined(__GCC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
			INumeric(INumeric& inum) { };
			INumeric(INumeric&& inum) { };
#if defined(__clang__)
#pragma clang diagnostic pop
#elif defined(__GCC__)
#pragma GCC diagnostics pop
#endif

			// Virtual Destructor
			virtual ~INumeric(void) {}
		}; 
	}
}
