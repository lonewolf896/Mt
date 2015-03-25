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
			data = new mtfloat_t[n][n];
		}
		Matrix::Matrix(int m, int n) {
			this->m = m;
			this->n = n;
			data = new mtfloat_t[m][n];
		}
		Matrix::~Matrix() {
			delete [][] data;
		}

		
	}
}