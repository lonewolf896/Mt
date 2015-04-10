/*
	Complex.cc - Implementation Details for complex number class
*/

#include "objects/Complex.hh"

namespace Mt {
	namespace objects {
		// Constructors
		Complex::Complex(void) {
			this->partReal = (this->partImaginary = 0.0l);
		}

		Complex::Complex(std::pair<Mt::objects::Scalar, Mt::objects::Scalar>& parts) {
			this->partReal = parts.first;
			this->partImaginary = parts.second;
		}

		Complex::Complex(Mt::objects::Scalar real, Mt::objects::Scalar i) {
			this->partReal = real;
			this->partImaginary = i;
		}

		Complex::Complex(Complex& cplx){
			this->SetPair(cplx.GetPair());
		}

		Complex::Complex(Complex&& cplx) {
			this->SetPair(cplx.GetPair());
		}

		Complex::Complex(std::string cplx) {
			
		}
		Complex::Complex(const char * cplx){
			
		}

		// Destructor
		Complex::~Complex(void) {

		}

		// Misc methods
		void Complex::SetRealPart(Mt::objects::Scalar real) {
			this->partReal = real;
		}

		void Complex::SetImaginaryPart(Mt::objects::Scalar i) {
			this->partImaginary = i;
		}

		void Complex::SetPair(std::pair<Mt::objects::Scalar, Mt::objects::Scalar> cmplxPair) {
			this->partReal = cmplxPair.first;
			this->partImaginary = cmplxPair.second;
		}

		Mt::objects::Scalar Complex::GetRealPart(void) {
			return this->partReal;
		}

		Mt::objects::Scalar Complex::GetImaginaryPart(void) {
			return this->partImaginary;
		}

		std::pair<Mt::objects::Scalar, Mt::objects::Scalar> Complex::GetPair(void) {
			return std::make_pair(this->partReal, this->partImaginary);
		}

		// Operator overloads

		Complex& Complex::operator=(Complex& rhs) {
			this->partReal = rhs.partReal;
			this->partImaginary = rhs.partImaginary;
			return *this;
		}

		// Basic Arithmetic operations
		Complex Complex::operator+(Complex& rhs) {
			Complex c((this->partReal + rhs.partReal), (this->partImaginary + rhs.partImaginary));
			return c;
		}

		Complex Complex::operator-(Complex& rhs) {
			Complex c((this->partReal + rhs.partReal), (this->partImaginary + rhs.partImaginary));
			return c;
		}

		Complex Complex::operator*(Complex& rhs) {
			Complex temp; 
			temp.partReal = rhs.partReal * this->partReal;

			if (this->partImaginary  == 1 && rhs.partImaginary  == 1) {
				temp.partImaginary = 0;
			}

			else{
				temp.partImaginary = rhs.partImaginary * this->partImaginary;
			}
			return temp;
		}

		Complex Complex::operator/(Complex& rhs) {
			Complex temp;
			temp.partReal = rhs.partReal / this->partReal;
			if (this->partImaginary == 1 && rhs.partImaginary == 1) {
				temp.partImaginary = 0;
			} 
			
			else{
				temp.partImaginary = rhs.partImaginary / this->partImaginary;	
			}
			return temp;
		}

		Complex Complex::operator%(Complex& rhs) {
			Complex c((this->partReal % rhs.partReal), (this->partImaginary % rhs.partImaginary));
			return c;
		}

		Complex& Complex::operator++() {
			this->partImaginary++;
			return *this;
		}

		Complex& Complex::operator++(int) {
			this->partReal++;
			return *this;
		}

		Complex& Complex::operator--() {
			this->partImaginary--;
			return *this;
		}

		Complex& Complex::operator--(int) {
			this->partReal--;
			return *this;
		}


		// Comparison operators
		bool Complex::operator==(Complex const& rhs) {
			return ((this->partReal == rhs.partReal) &&
				    (this->partImaginary == rhs.partImaginary));
		}

		bool Complex::operator!=(Complex const& rhs) {
			return !this->operator==(rhs);
		}

		bool Complex::operator>(Complex const& rhs) {
			return ((this->partReal > rhs.partReal) &&
				    (this->partImaginary > rhs.partImaginary));
		}

		bool Complex::operator<(Complex const& rhs) {
			return !this->operator>(rhs);
		}

		bool Complex::operator>=(Complex const& rhs) {
			return ((this->partReal >= rhs.partReal) &&
				    (this->partImaginary >= rhs.partImaginary));
		}

		bool Complex::operator<=(Complex const& rhs) {
			return ((this->partReal <= rhs.partReal) &&
				    (this->partImaginary <= rhs.partImaginary));
		}

		std::ostream& operator<<(std::ostream& os, const Complex& cplx) {
			return (os << cplx.partReal << " " << cplx.partImaginary << "i");
		}
	}
}
