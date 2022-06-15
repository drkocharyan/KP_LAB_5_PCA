#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <cmath>
#include <string>
#include <cassert>
#include <iomanip>
#include <exception>
#include <algorithm>
#include <initializer_list>	
#include "string"
using std::setw;

enum class mode {
	bin,
	txt
};

class Matrix {
protected:
	int cols_amount, rows_amount;
	int rank;
	double det;
	std::vector <std::vector<double>> matrix_data;
public:
	//constructors
	Matrix();
	Matrix(int rows, int cols);
	Matrix(const Matrix& MM);
	Matrix(const std::vector<std::vector<double>>& data);
	Matrix(const std::initializer_list<std::initializer_list<double>>& list);
	
	virtual int get_rows_amount() const;
	virtual int get_cols_amount() const;

	virtual void set_matrix_size(int rows, int cols);

	virtual double& at(int row, int column);
	virtual const double& at(int row, int column) const;

	virtual std::pair<int, int> GetSize() const;

	virtual std::vector<std::vector<double>>& get_data();
	virtual const std::vector<std::vector<double>>& get_data() const;

	virtual int MatrixRank();
	virtual double Matrix_trace();
	virtual double Matrix_Det();

	Matrix operator=(const Matrix& right);
	Matrix operator*(const Matrix& right);
	Matrix operator+(const Matrix& right);
	Matrix operator-(const Matrix& right);

	double NormVector();
	

	friend std::istream& operator>>(std::istream& is, Matrix& matrix);//input
	friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix);//output

	virtual bool load_tfile(const std::string& directory, mode mode) const;
	virtual bool get_ffile(const std::string& directory, mode mode);

};

Matrix operator%(const Matrix& left, const Matrix& matrix);//������������ �������
Matrix operator*(const Matrix& matrix, double a);//������������ ������� �� �����
Matrix operator*(double a, const Matrix& matrix);//������������ ����� �� �������
Matrix operator/(const Matrix& matrix, double a);
Matrix operator/(double a, const Matrix& matrix);

void Transpose(Matrix& matrix);
Matrix TransposeMatrix(const Matrix& matrix);
Matrix InverseMatrix(Matrix& matrix);

void Gauss(Matrix& matrix);
double ScalarComp(const Matrix& left_vec, const Matrix& right_vec);
double Frobenius_norm(const Matrix& matrix);
double AngleBeetween(const Matrix& left_vec, const Matrix& right_vec);

bool Is_vector(const Matrix& matrix);
bool Is_Square_matrix(const Matrix& matrix);

class SquareMatrix : public Matrix {
public:
	SquareMatrix(int rows = 0) {
		rows_amount = rows;
		cols_amount = rows;
		matrix_data.assign(rows_amount, std::vector<double>(cols_amount, 0));
	}
	~SquareMatrix() = default;

};

class UnitMatrix : public SquareMatrix {
public:
	UnitMatrix(size_t size) : SquareMatrix(size) {
		for (size_t i = 0; i < size; i++) {
			this->at(i, i) = 1;
		}
	}
	~UnitMatrix() = default;
};

