/*
	Matrix.hh - MxN matrix
*/
#pragma once

#include "core/INumeric.hh"
#include "objects/List.hh"

namespace Mt {
	namespace objects {
		/*! \class Matrix
			\brief Represents an M by N matrix
		*/
		class Matrix : Mt::core::INumeric {
			private:
				INumeric* data;
				int m, n;
				int RowColumnToIndex(int row, int column);
			public:
				Matrix(void);
				Matrix(int n);
				Matrix(int n, int m);
				~Matrix();

				List GetRow(int index);
				List GetColumn(int index);
				INumeric& GetAtLocation(int row, int column);

				friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
		};
	}
}
