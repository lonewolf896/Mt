/*
	INumeric.hpp - Base class for complex and any other special numbers (I.E Rational numbers, etc)
*/
#pragma once
#include "IMtObject.hpp";
namespace Mt {
	class INumeric : IMtObject {
		public:
		// Disable default move and copy constructors for the interface
		INumeric(void) { }
		INumeric(INumeric& inum) { };
		INumeric(INumeric&& inum) { };

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