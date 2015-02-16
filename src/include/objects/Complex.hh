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

			\todo Replace long long with Mt::core::IScalar
		*/
		class Complex : public Mt::core::INumeric {
		private:
			long long partReal;
			long long partImaginary;
		public:

		// Constructors
		Complex(void);
		Complex(std::pair<long long, long long> parts);
		Complex(long long real, long long i);

		~Complex(void);

		// Misc functions
		void SetRealPart(long long real);
		void SetImaginaryPart(long long i);
		void SetPair(std::pair<long long, long long> cmplxPair);

		long long GetRealPart(void);
		long long GetImaginaryPart(void);
		std::pair<long long, long long> GetPair(void);

		// Operator overloads

		Complex& operator=(Complex& rhs);

		// Basic Arithmatic operations
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

		// Comparason operators
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
