/*
	Matrix.hh - MxN matrix
*/
#pragma once

#include "core/INumeric.hh"
#include "objects/List.hh"

#include "core/IMtObject.hh"


namespace Mt {
	namespace objects {
		/*! \class Matrix
			\brief Represents an M by N matrix
		*/
		class Matrix : Mt::core::INumeric {
			private:
				IMtObject* data;
				int m, n;
				int RowColumnToIndex(int row, int column);
			public:
				Matrix(void);
				Matrix(int n);
				Matrix(int n, int m);
				~Matrix();

				List GetRow(int index);
				List GetColumn(int index);
		};
	}
}
