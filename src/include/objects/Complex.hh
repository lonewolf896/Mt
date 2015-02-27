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
		*/
		class Complex : public Mt::core::INumeric {
			private:
				Mt::objects::Scalar partReal;
				Mt::objects::Scalar partImaginary;
			public:

			// Constructors
			Complex(void);
			Complex(const std::pair<Mt::objects::Scalar, Mt::objects::Scalar>& parts);
			Complex(Mt::objects::Scalar real, Mt::objects::Scalar i);

			Complex(Complex& cplx);
			Complex(Complex&& cplx);

			~Complex(void);

			// Misc functions
			void SetRealPart(Mt::objects::Scalar real);
			void SetImaginaryPart(Mt::objects::Scalar i);
			void SetPair(const std::pair<Mt::objects::Scalar, Mt::objects::Scalar> cmplxPair);

			Mt::objects::Scalar GetRealPart(void);
			Mt::objects::Scalar GetImaginaryPart(void);
			std::pair<Mt::objects::Scalar, Mt::objects::Scalar> GetPair(void);

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
