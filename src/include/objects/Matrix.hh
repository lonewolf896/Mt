/*
	Matrix.hh - MxN matrix
*/
#pragma once

#include "core/INumeric.hh"
#include "objects/List.hh"
#include <vector>

namespace Mt {
	namespace objects {
		/*! \class Matrix
			\brief Represents an M by N matrix
		*/
		class Matrix : Mt::core::INumeric {
			private:
				int m, n;
				INumeric* data;
				int RowColumnToIndex(int row, int column);
			public:
				Matrix();
				Matrix(int n);
				Matrix(int m, int n);
				~Matrix();

				Mt::objects::List GetRow(int index);
				Mt::objects::List GetColumn(int index);
		};
	}
}
