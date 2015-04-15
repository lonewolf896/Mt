/*
	Matrix.hh - MxN matrix
*/
#pragma once

#include "objects/List.hh"

#include <iostream>
#include <stdexcept>

namespace Mt {
	namespace objects {
		/*! \class Matrix
			\brief Represents an M by N matrix
		*/
		template <class T>
		class Matrix : Mt::core::IMtObject {
			private:
				int m, n;
				int RowColumnToIndex(int row, int column) const;
				T* data;
			public:
				Matrix(void);
				Matrix(int n);
				Matrix(int m, int n);
				~Matrix();

				int GetRows() const;
				int GetColumns() const;
				List<T> GetRow(int index);
				List<T> GetColumn(int index);
				T& GetAtLocation(int row, int column) const;
				void SetAtLocation(int row, int column, T value);
				void SetAll(T value);
				
				Matrix<T> operator+(Matrix<T>& rhs);
				Matrix<T> operator*(Matrix<T>& rhs);

				friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix){
					os << "\n[\n";
					for(int row = 0; row < matrix.GetRows(); row++) {
						for(int column = 0; column < matrix.GetColumns(); column++)
							os << matrix.GetAtLocation(row,column) << "\t";
						os << "\n";
					}
					os << "]\n";
					return os;
				}
		};
		
		template<class T>
		Matrix<T>::Matrix(void) {
			m = 0;
			n = 0;
			data = nullptr;
			this->DerivedType = Mt::core::TYPE::MATRIX;
		}
		
		template<class T>
		Matrix<T>::Matrix(int n) {
			m = n;
			this->n = n;
			data = new T[n * n];
			this->DerivedType = Mt::core::TYPE::MATRIX;
		}
		
		template<class T>
		Matrix<T>::Matrix(int m, int n) {
			this->m = m;
			this->n = n;
			data = new T[n * m];
			this->DerivedType = Mt::core::TYPE::MATRIX;
		}
		
		template<class T>
		Matrix<T>::~Matrix() {
			delete [] data;
		}
		
		template<class T>
		int Matrix<T>::GetRows() const{
			return m; 
		}
		
		template<class T>
		int Matrix<T>::GetColumns() const{
			return n; 
		}
		
		template<class T>
		List<T> Matrix<T>::GetRow(int index) {
			List<T> returnList;
			for (int i = 0; i < n; ++i)
				returnList.Add(data[RowColumnToIndex(i, index)]);
			return returnList;
		}
		
		template<class T>
		List<T> Matrix<T>::GetColumn(int index) {
			List<T> returnList;
			for (int i = 0; i < m; ++i)
				returnList.Add(data[RowColumnToIndex(index, i)]);
			return returnList;
		}

		template<class T>
		T& Matrix<T>::GetAtLocation(int row, int column) const {
			return data[RowColumnToIndex(row,column)];
		}
		
		template<class T>
		void Matrix<T>::SetAtLocation(int row, int column, T value) {
			data[RowColumnToIndex(row, column)] = value; 
		}
		
		template<class T>
		void Matrix<T>::SetAll(T value) {
			for(int row = 0; row < m; row++) for(int column = 0; column < n; column++)
				GetAtLocation(row, column) = value;
		}

		template<class T>
		int Matrix<T>::RowColumnToIndex(int row, int column) const {
			return (row * n) + column;
		}
		
		template<class T>
		Matrix<T> Matrix<T>::operator+(Matrix<T>& rhs) {
			if(rhs.n != n || rhs.m != m) 
				throw std::invalid_argument("When adding two matrix togeather, make sure they are of the same dimentions.");
			
			Matrix<T> returnMatrix(n, m);
			for(int row = 0; row < m; row++) for(int column = 0; column < n; column++)
				returnMatrix.GetAtLocation(row, column) = rhs.GetAtLocation(row,column) + GetAtLocation(row, column);
			return returnMatrix;
		}
		
		template<class T>
		Matrix<T> Matrix<T>::operator*(Matrix<T>& rhs) {
			if(n != rhs.m)
				throw std::invalid_argument("When multiplying two matrix togeather, make sure that Matrix A's n is Matrix B's m.");
			Matrix<T> returnMatrix(m, rhs.GetColumns());
			for(int row = 0; row < m; row++) for(int column = 0; column < rhs.GetColumns(); column++)
				for(int inner = 0; inner < m; inner++)
					returnMatrix.GetAtLocation(row, column) += GetAtLocation(row, inner) * rhs.GetAtLocation(inner, column);
			return returnMatrix;
		}
	}
}
