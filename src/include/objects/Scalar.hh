/*
	Scalar.hh - Scalar
*/
#pragma once
#include <iostream>
#include "core/INumeric.hh"

namespace Mt {
	namespace objects {
		/*! \class Scalar
			\brief Scalar Numeric Type

			This abstract class is the base of all non-complex and non-intricate numerical types

		*/
		class Scalar : public core::INumeric {
		private:
			mtfloat_t Internal;
		public:
			Scalar();
			Scalar(mtfloat_t num);
			Scalar(Scalar& s);
			Scalar(Scalar const& s);
			Scalar(Scalar&& s);
			~Scalar();
			mtfloat_t GetInternal();
			Scalar& operator=(Scalar const& rhs);
			Scalar& operator=(Scalar& rhs);
			Scalar& operator=(mtfloat_t const& rhs);
			Scalar 	operator+(Scalar& rhs);
			Scalar 	operator+(mtfloat_t& rhs);
			Scalar& operator+=(Scalar const& rhs);
			Scalar 	operator-(Scalar& rhs);
			Scalar 	operator-(mtfloat_t& rhs);
			Scalar 	operator*(Scalar& rhs);
			Scalar 	operator*(mtfloat_t& rhs);
			Scalar 	operator/(Scalar& rhs);
			Scalar 	operator/(mtfloat_t& rhs);
			Scalar& operator++(int);
			Scalar& operator--(int);
			bool operator==(Scalar const& rhs);
			bool operator==(mtfloat_t const& rhs);
			bool operator!=(Scalar const& rhs);
			bool operator!=(mtfloat_t const& rhs);
			bool operator>(Scalar const& rhs);
			bool operator>(mtfloat_t const& rhs);
			bool operator<(Scalar const& rhs);
			bool operator<(mtfloat_t const& rhs);
			bool operator>=(Scalar const& rhs);
			bool operator>=(mtfloat_t const& rhs);
			bool operator<=(Scalar const& rhs);
			bool operator<=(mtfloat_t const& rhs);

			// Stream overloads
			friend std::ostream& operator<<(std::ostream& os, const Scalar& sclr);

		};
	}
}
