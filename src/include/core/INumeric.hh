/*
	INumeric.hh - Base class for complex and any other special numbers (I.E Rational numbers, etc)
*/
#pragma once
#include "IMtObject.hh"
namespace Mt {
	class INumeric : IMtObject {
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
		virtual INumeric& operator=(INumeric& rhs) = 0;

		// Basic Arithmatic operations
		virtual INumeric& operator+(INumeric& rhs) = 0;
		virtual INumeric& operator-(INumeric& rhs) = 0;
		virtual INumeric& operator+() = 0;
		virtual INumeric& operator-() = 0;
		virtual INumeric& operator*(INumeric& rhs) = 0;
		virtual INumeric& operator/(INumeric& rhs) = 0;
		virtual INumeric& operator%(INumeric& rhs) = 0;
		virtual INumeric& operator++() = 0;
		virtual INumeric& operator++(int) = 0;
		virtual INumeric& operator--() = 0;
		virtual INumeric& operator--(int) = 0;

		// Comparason operators
		virtual bool operator==(INumeric const& rhs) = 0;
		virtual bool operator!=(INumeric const& rhs) = 0;
		virtual bool operator>(INumeric const& rhs) = 0;
		virtual bool operator<(INumeric const& rhs) = 0;
		virtual bool operator>=(INumeric const& rhs) = 0;
		virtual bool operator<=(INumeric const& rhs) = 0;

		// Virtual Destructor
		virtual ~INumeric(void) {}
	};
}
