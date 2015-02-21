/*
	IScalar.hh - Scalar interface
*/
#pragma once

#include "core/INumeric.hh"

namespace Mt {
	namespace objects {
		/*! \class Scalar
			\brief Scalar Numeric Type

			This abstract class is the base of all non-complex and non-intricate numerical types

		*/
		class Scalar : INumeric {
		private:
			mtfloat_t Internal;
		};
	}
}
