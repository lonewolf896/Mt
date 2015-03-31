#include "objects/Matrix.hh"

namespace Mt {
	namespace objects {

		Matrix::Matrix() {
			m = 0;
			n = 0;
			data = nullptr;
		}
		Matrix::Matrix(int n) {
			m = n;
			this->n = n;
			data = new INumeric[n * n];
		}
		Matrix::Matrix(int m, int n) {
			this->m = m;
			this->n = n;
			data = new INumeric[n * n];
		}
		Matrix::~Matrix() {
			delete [] data;
		}

		Mt::objects::List Matrix::GetRow(int index)
		{
			List returnList;
			for (int i = 0; i < n; ++i)
				returnList.Add(data[RowColumnToIndex(i, index)]);
		}

		Mt::objects::List Matrix::GetColumn(int index)
		{
			List returnList;
			for (int i = 0; i < m; ++i)
				returnList.Add(data[RowColumnToIndex(index, i)]);
		}

		int Matrix::RowColumnToIndex(int row, int column)
		{
			return (row * n) + row;
		}
	}
}
