/*
	Scalar.cc - Scalar
*/
#pragma once

#include "core/INumeric.hh"
#include "objects/Scalar.hh"

namespace Mt {
	namespace objects {
		Scalar::Scalar(){
			Internal = 0;
		}

		Scalar::Scalar(mtfloat_t num){
			Internal = num;
		}

		Scalar::Scalar(Scalar&& s){
			Internal = s.Internal;
		}

		Scalar::Scalar(Scalar& s){
			Internal = s.Internal;
		}

		Scalar::~Scalar(){

		}

        /*!
        	The assigment operator, this should check for type so you cant assign a Mt::Complex to an Mt::Integer
        */
		Scalar& Scalar::operator=(Scalar& rhs){
			Internal = rhs.Internal;
			return *this;
		}
		Scalar& Scalar::operator=(mtfloat_t& rhs){
			Internal = rhs;
			return *this;
		}

		// Basic Arithmatic operations
		Scalar& Scalar::operator+(Scalar& rhs){
			Scalar s(Internal + rhs.Internal);
			return s;
		}
		Scalar& Scalar::operator-(Scalar& rhs){
			Scalar s(Internal - rhs.Internal);
			return s;
		}
		Scalar& Scalar::operator*(Scalar& rhs){
			Scalar s(Internal * rhs.Internal);
			return s;
		}
		Scalar& Scalar::operator/(Scalar& rhs){
			Scalar s(Internal / rhs.Internal);
			return s;
		}
		Scalar& Scalar::operator++(int){
			Internal++;
			return *this;
		}
		Scalar& Scalar::operator--(int){
			Internal--;
			return *this;
		}

		// Basic Arithmatic operations mtfloat_t
		Scalar& Scalar::operator+(mtfloat_t& rhs){
			Scalar s(Internal + rhs);
			return s;
		}
		Scalar& Scalar::operator-(mtfloat_t& rhs){
			Scalar s(Internal - rhs);
			return s;
		}
		Scalar& Scalar::operator*(mtfloat_t& rhs){
			Scalar s(Internal * rhs);
			return s;
		}
		Scalar& Scalar::operator/(mtfloat_t& rhs){
			Scalar s(Internal / rhs);
			return s;
		}

		// Comparason Scalar::operators
		bool Scalar::operator==(Scalar const& rhs){
			return Internal == rhs.Internal;
		}
		bool Scalar::operator!=(Scalar const& rhs){
			return Internal != rhs.Internal;
		}
		bool Scalar::operator>(Scalar const& rhs){
			return Internal > rhs.Internal;
		}
		bool Scalar::operator<(Scalar const& rhs){
			return Internal < rhs.Internal;
		}
		bool Scalar::operator>=(Scalar const& rhs){
			return Internal >= rhs.Internal;
		}
		bool Scalar::operator<=(Scalar const& rhs){
			return Internal <= rhs.Internal;
		}
		// Comparason mtfloat_t
		bool Scalar::operator==(mtfloat_t const& rhs){
			return Internal == rhs;
		}
		bool Scalar::operator!=(mtfloat_t const& rhs){
			return Internal != rhs;
		}
		bool Scalar::operator>(mtfloat_t const& rhs){
			return Internal > rhs;
		}
		bool Scalar::operator<(mtfloat_t const& rhs){
			return Internal < rhs;
		}
		bool Scalar::operator>=(mtfloat_t const& rhs){
			return Internal >= rhs;
		}
		bool Scalar::operator<=(mtfloat_t const& rhs){
			return Internal <= rhs;
		}
	}
}
