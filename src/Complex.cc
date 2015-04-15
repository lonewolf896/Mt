/*
	Complex.cc - Implementation Details for complex number class
*/

#include "objects/Complex.hh"

namespace Mt {
	namespace objects {
		// Constructors
		Complex::Complex(void) {
			this->partReal = (this->partImaginary = 0.0l);
			this->DerivedType = Mt::core::TYPE::COMPLEX;
		}

		Complex::Complex(std::pair<Mt::objects::Scalar, Mt::objects::Scalar>& parts) {
			this->partReal = parts.first;
			this->partImaginary = parts.second;
			this->DerivedType = Mt::core::TYPE::COMPLEX;
		}

		Complex::Complex(Mt::objects::Scalar real, Mt::objects::Scalar i) {
			this->partReal = real;
			this->partImaginary = i;
			this->DerivedType = Mt::core::TYPE::COMPLEX;
		}

		Complex::Complex(Complex& cplx){
			this->SetPair(cplx.GetPair());
			this->DerivedType = Mt::core::TYPE::COMPLEX;
		}

		Complex::Complex(Complex&& cplx) {
			this->SetPair(cplx.GetPair());
			this->DerivedType = Mt::core::TYPE::COMPLEX;
		}
		Complex::Complex(std::string cplx) {
			// TODO, split #[+-]#i into # and [-+]#i
			this->DerivedType = Mt::core::TYPE::COMPLEX;

		}
		// Chained constructor
		Complex::Complex(const char * cplx) : Complex(std::string(cplx)) {
			// Nothing to do boss...
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
#pragma message("Fix scalar and make this not horribly ugly")
			Scalar a = rhs.partReal * this->partReal;
			Scalar b = rhs.partImaginary * this->partImaginary;
			Scalar c = rhs.partReal * this->partImaginary;
			Scalar d = rhs.partImaginary * this->partReal;

			Complex temp; 

			temp.partReal = a - b;
			temp.partImaginary = c + d;

			return temp;
		}

		Complex Complex::operator/(Complex& rhs) {
#pragma message("Fix scalar and make this not horribly ugly")
			Scalar a = rhs.partReal;
			Scalar b = rhs.partImaginary;
			Scalar c = rhs.partReal;
			Scalar d = rhs.partImaginary;

			Complex temp;

			//yes I do hate myself, thanks for asking
			Scalar e = c * c;
			Scalar f = d * d;
			Scalar bottom = e + f;

			Scalar x = a * c;
			Scalar y = b * d;
			Scalar top = x + y;

			temp.partReal = (top/bottom);

			Scalar x1 = b * c;
			Scalar y1 = a * d;
			Scalar top1 = x1 - y1;

			temp.partImaginary = (top1/bottom);

			return temp;
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
