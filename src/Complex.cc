/*
	Complex.cc - Implelentation Details for complex number class
*/

#include <objects/Complex.hh>

namespace Mt {
	namespace objects {
		// Constructors
		Complex::Complex(void) {
			this->partReal = (this->partImaginary = 0LL);
		}

		Complex::Complex(std::pair<long long, long long> parts) {
			this->partReal = parts.first;
			this->partImaginary = parts.second;
		}

		Complex::Complex(long long real, long long i) {
			this->partReal = real;
			this->partImaginary = i;

		}

		// Destructor
		Complex::~Complex(void) {

		}

		// Misc methods
		void Complex::SetRealPart(long long real) {
			this->partReal = real;
		}

		void Complex::SetImaginaryPart(long long i) {
			this->partImaginary = i;
		}

		void Complex::SetPair(std::pair<long long, long long> cmplxPair) {
			this->partReal = cmplxPair.first;
			this->partImaginary = cmplxPair.second;
		}

		long long Complex::GetRealPart(void) {
			return this->partReal;
		}

		long long Complex::GetImaginaryPart(void) {
			return this->partImaginary;
		}

		std::pair<long long, long long> Complex::GetPair(void) {
			return std::make_pair(this->partReal, this->partImaginary);
		}

		// Operator overloads

		Complex& Complex::operator=(Complex& rhs) {
			this->partReal = rhs.GetRealPart();
			this->partImaginary = rhs.GetImaginaryPart();
			return *this;
		}

		// Basic Arithmetic operations
		Complex& Complex::operator+(Complex& rhs) {

		}

		Complex& Complex::operator-(Complex& rhs) {

		}

		Complex& Complex::operator+() {

		}

		Complex& Complex::operator-() {

		}

		Complex& Complex::operator*(Complex& rhs) {

		}

		Complex& Complex::operator/(Complex& rhs) {

		}

		Complex& Complex::operator%(Complex& rhs) {

		}

		Complex& Complex::operator++() {

		}

		Complex& Complex::operator++(int) {

		}

		Complex& Complex::operator--() {

		}

		Complex& Complex::operator--(int) {

		}


		// Comparison operators
		bool Complex::operator==(Complex const& rhs) {

		}

		bool Complex::operator!=(Complex const& rhs) {
			return !this->operator==(rhs);
		}

		bool Complex::operator>(Complex const& rhs) {

		}

		bool Complex::operator<(Complex const& rhs) {
			return !this->operator>(rhs);
		}

		bool Complex::operator>=(Complex const& rhs) {

		}

		bool Complex::operator<=(Complex const& rhs) {

		}

		std::ostream& operator<<(std::ostream& os, const Complex& cplx) {
			return (os << cplx.partReal << " " << cplx.partImaginary << "i");
		}
	}
}
