/*
	Complex.hh - Complex number implementation
*/
#pragma once
#include <utility>
#include <iostream>

#include "core/INumeric.hh"

namespace Mt {
	namespace objects {
		/*! \class Complex
			\brief Mt Complex Number

			This class allows the representation of complex numbers 

			\todo Replace mtfloat_t with Mt::core::Scalar
		*/
		class Complex : public Mt::core::INumeric {
		private:
			mtfloat_t partReal;
			mtfloat_t partImaginary;
		public:

		// Constructors
		Complex(void);
		Complex(std::pair<mtfloat_t, mtfloat_t> parts);
		Complex(mtfloat_t real, mtfloat_t i);

		~Complex(void);

		// Misc functions
		void SetRealPart(mtfloat_t real);
		void SetImaginaryPart(mtfloat_t i);
		void SetPair(std::pair<mtfloat_t, mtfloat_t> cmplxPair);

		mtfloat_t GetRealPart(void);
		mtfloat_t GetImaginaryPart(void);
		std::pair<mtfloat_t, mtfloat_t> GetPair(void);

		// Operator overloads

		Complex& operator=(Complex& rhs);

		// Basic Arithmetic operations
		Complex& operator+(Complex& rhs);
		Complex& operator-(Complex& rhs);
		Complex& operator+();
		Complex& operator-();
		Complex& operator*(Complex& rhs);
		Complex& operator/(Complex& rhs);
		Complex& operator%(Complex& rhs);
		Complex& operator++();
		Complex& operator++(int);
		Complex& operator--();
		Complex& operator--(int);

		// Comparison operators
		bool operator==(Complex const& rhs);
		bool operator!=(Complex const& rhs);
		bool operator>(Complex const& rhs);
		bool operator<(Complex const& rhs);
		bool operator>=(Complex const& rhs);
		bool operator<=(Complex const& rhs);

		// Stream overloads
		friend std::ostream& operator<<(std::ostream& os, const Complex& cplx);

	};
	}
}
