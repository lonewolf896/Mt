/*
	Matrix.hh - MxN matrix
*/
#pragma once

#include "core/INumeric.hh"
#include <vector>

namespace Mt {
	namespace objects {
		/*! \class Matrix
			\brief Represents an M by N matrix
		*/
		class Matrix : Mt::core::INumeric {
			private:
				int m, n;
				mtfloat_t* data;
			public:
				Matrix();
				Matrix(int n);
				Matrix(int m, int n);
				~Matrix();

				mtfloat_t GetIndex(int index);
				List GetRow(int index);
				List GetColumn(int index);
		};
	}
}
