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
			data = new INumeric[n * m];
		}
		Matrix::~Matrix() {
			std::cout << "\n\nDEATH TO THE MATRIX\n\n";
			// ^-- It's because of silly messages like this that make us realise that there is a memory leak.
			// Practice silly code in your projects.  Add practices like this to your company's code standards document.
			delete [] data;
		}

		List Matrix::GetRow(int index) {
			List returnList;
			for (int i = 0; i < n; ++i)
				returnList.Add(data[RowColumnToIndex(i, index)]);
			return returnList;
		}

		List Matrix::GetColumn(int index) {
			List returnList;
			for (int i = 0; i < m; ++i)
				returnList.Add(data[RowColumnToIndex(index, i)]);
			return returnList;
		}

		core::INumeric& Matrix::GetAtLocation(int row, int column) {
			return data[RowColumnToIndex(row,column)];
		}
		
		void Matrix::SetAtLocation(int row, int column, INumeric value) {
			data[RowColumnToIndex(row, column)] = value; 
		}

		int Matrix::RowColumnToIndex(int row, int column) {
			return (row * n) + column;
		}

		std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
			return os << "MATRIX OVERLOAD USED";
		}
	}
}
