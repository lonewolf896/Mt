/*
	Complex.hh - Complex number implementation
*/
#pragma once
#include <utility>
#include <iostream>

#include "core/INumeric.hh"
#include "Scalar.hh"

namespace Mt {
	namespace objects {
		/*! \class Complex
			\brief Mt Complex Number

			This class allows the representation of complex numbers 

			\todo Replace Mt::core::Scalar with Mt::core::Scalar
		*/
		class Complex : public Mt::core::INumeric {
			private:
				Mt::core::Scalar partReal;
				Mt::core::Scalar partImaginary;
			public:

			// Constructors
			Complex(void);
			Complex(std::pair<Mt::core::Scalar, Mt::core::Scalar> parts);
			Complex(Mt::core::Scalar real, Mt::core::Scalar i);

			~Complex(void);

			// Misc functions
			void SetRealPart(Mt::core::Scalar real);
			void SetImaginaryPart(Mt::core::Scalar i);
			void SetPair(std::pair<Mt::core::Scalar, Mt::core::Scalar> cmplxPair);

			Mt::core::Scalar GetRealPart(void);
			Mt::core::Scalar GetImaginaryPart(void);
			std::pair<Mt::core::Scalar, Mt::core::Scalar> GetPair(void);

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
