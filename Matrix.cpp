#pragma once
#include "Matrix.h"
#include <iomanip>
using std::setw;

Matrix::Matrix() {
	rows_amount = 0;
	cols_amount = 0;
	rank = 0;
	det = 0;
}
Matrix::Matrix(int rows, int cols) {
	rows_amount = rows;
	cols_amount = cols;
	matrix_data.assign(rows_amount, std::vector<double>(cols_amount, 0));
	det = 0;
	rank = 0;
}
Matrix::Matrix(const Matrix& MM) {
	rows_amount = MM.get_rows_amount();
	cols_amount = MM.get_cols_amount();
	matrix_data = MM.get_data();
	//det = MM.det;
	//rank = MM.rank;
}
Matrix::Matrix(const std::vector<std::vector<double>>& data) {
	rows_amount = data.size();
	cols_amount = data.at(0).size();
	matrix_data = data;
	det = 0;
	rank = 0;
}
Matrix::Matrix(const std::initializer_list<std::initializer_list<double>>& list)
	: matrix_data{ list.begin(),list.end() } {
	rows_amount = list.size();
	cols_amount = list.begin()->size();
	det = 0;
	rank = 0;
}
int Matrix::get_rows_amount() const {
	return rows_amount;
}
int Matrix::get_cols_amount() const {
	return cols_amount;
}
std::vector<std::vector<double>>& Matrix::get_data() {
	return matrix_data;
}
const std::vector<std::vector<double>>& Matrix::get_data() const {
	return matrix_data;
}
double& Matrix::at(int row, int column) {
	return matrix_data.at(row).at(column);
}
const double& Matrix::at(int row, int column) const {
	return matrix_data[row][column];
}
std::pair<int, int> Matrix::GetSize() const {
	return std::make_pair(rows_amount, cols_amount);
}

std::istream& operator>>(std::istream& in, Matrix& matrix) {
	auto rows = matrix.get_rows_amount();
	auto cols = matrix.get_cols_amount();
	double num;
	for (auto i = 0; i < rows; i++) {
		for (auto j = 0; j < cols; j++) {
			
			in >> num;
			matrix.at(i, j) = num;
		}
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, const Matrix& matrix) {
	auto rows = matrix.get_rows_amount();
	auto cols = matrix.get_cols_amount();
	for (auto i = 0; i < rows; i++) {
		out << std::endl;
		for (auto j = 0; j < cols; j++) {
			out << setw(15) << matrix.at(i,j);
		}
	}
	return out;
}

Matrix Matrix::operator=(const Matrix& right) {
	rows_amount = right.rows_amount;
	cols_amount = right.cols_amount;
	matrix_data = right.get_data();
	//rank = right.rank;
	//det = right.det;
	return *this;
}

Matrix Matrix::operator*(const Matrix& right) {
	auto& left = *this;
	auto left_rows = left.get_rows_amount();
	auto left_cols = left.get_cols_amount();
	auto right_rows = right.get_rows_amount();
	auto right_cols = right.get_cols_amount();
	if (left_cols != right_rows) {
		throw std::runtime_error("Invalid matrix sizes");
	}
	Matrix res(left_rows, right_cols);
	
	for (auto i = 0; i < left_rows; i++) {
		for (auto j = 0; j < right_cols; j++) {
			double i_res = 0;
			for (auto k = 0; k < left_cols; k++) {
				i_res += left.matrix_data[i][k] * right.matrix_data[k][j];
				if (abs(i_res - 0) < 0.00001) {
					res.at(i, j) = 0;
				}
				res.matrix_data[i][j] = i_res;
			}
		}
	}
	return res;
}

Matrix Matrix::operator+(const Matrix& right) {
	auto& left = *this;
	auto left_rows = left.get_rows_amount();
	auto left_cols = left.get_cols_amount();
	auto right_rows = right.get_rows_amount();
	auto right_cols = right.get_cols_amount();
	if ((left_rows != right_rows) || (left_cols != right_cols)) {
		throw std::runtime_error("Invalid matrix sizes");
	}
	
	Matrix res(left_rows, left_cols);
	for (auto i = 0; i < left_rows; i++) {
		for (auto j = 0; j < left_cols; j++) {
			res.at(i, j) = left.at(i, j) + right.at(i, j);
		}
	}
	return res;
}
Matrix Matrix::operator-(const Matrix& right) {
	return *this + (-1) * right;
}

Matrix operator*(const Matrix& matrix, double a) {
	auto left_rows = matrix.get_rows_amount();
	auto left_cols = matrix.get_cols_amount();
	Matrix res(left_rows, left_cols);
	for (auto i = 0; i < left_rows; i++) {
		for (auto j = 0; j < left_cols; j++) {
			res.at(i, j) = matrix.at(i, j) * a;
		}
	}
	return res;
}

Matrix operator*(double a, const Matrix& matrix) {
	return matrix * a;
}

Matrix operator/(double a, const Matrix& matrix) {
	return matrix * (1/a);
}

Matrix operator/(const Matrix& matrix, double a) {
	return matrix * (1 / a);
}
Matrix operator%(const Matrix& left, const Matrix& right) {
	auto left_rows = left.get_rows_amount();
	auto left_cols = left.get_cols_amount();
	auto right_rows = right.get_rows_amount();
	auto right_cols = right.get_cols_amount();
	if ((left_rows != right_rows) || (left_cols != right_cols)) {
		throw std::runtime_error("Invalid matrix sizes");
	}
	Matrix C(left_rows, left_cols);
	for (auto i = 0; i < left_rows; i++) {
		for (auto j = 0; j < left_cols; j++) {
			C.at(i,j) = left.at(i, j) * right.at(i, j);
		}
	}
	return C;
}

void Gauss(Matrix& matrix) {
	int m_cols = matrix.get_cols_amount();
	int m_rows = matrix.get_rows_amount();
	auto& matr = matrix.get_data();
	bool first = true;
	int max_index = -1;
	double max_value;
	for (auto cur = 0; cur < std::min(m_rows, m_cols); cur++) {
		for (auto j = cur; j < m_rows; j++) {
			if (first) {
				max_value = matrix.at(j, cur);
				max_index = j;
				first = false;
			}
			else {
				if (matrix.at(j, cur) > max_value) {
					max_value = matrix.at(j, cur);
					max_index = j;
				}
			}
		}
		if (cur != max_index) {
			for (auto& c : matr[max_index]) {
				c *= -1;
			}
			std::swap(matr[cur], matr[max_index]);
		}
		for (auto j = cur + 1; j < m_rows; j++) {
			if (matr[cur][cur] == 0)
				break;
			double norm_coeff = matr[j][cur] / matr[cur][cur];
			for (auto k = 0; k < m_cols; k++) {
				matr[j][k] -= matr[cur][k] * norm_coeff;
				if (abs(matr[j][k] - 0) < 0.00001)
					matr[j][k] = 0;
			}
		}
	}
	for (auto cur = std::min(m_cols, m_rows) - 1; cur >= 0; cur--) {
		for (auto j = cur - 1; j >= 0; j--) {
			if (matr[cur][cur] == 0)
				break;
			double norm_coeff = matr[j][cur] / matr[cur][cur];
			for (auto k = 0; k < m_cols; k++) {
				matr[j][k] -= matr[cur][k] * norm_coeff;
				if (abs(matr[j][k] - 0) < 0.00001)
					matr[j][k] = 0;
			}
		}
	}
}

Matrix InverseMatrix(Matrix& matrix) {
	if (!Is_Square_matrix(matrix)) {
		throw std::runtime_error("The matrix is not square");
	}
	int rows = matrix.get_rows_amount();
	auto& tmp = matrix.get_data();
	Matrix inv(rows, rows);
	std::vector<std::vector<double>> inverse;
	double temp;

	for (auto i = 0; i < rows; i++) {
		tmp[i].resize(2 * rows);
		for (auto j = 0; j < 2 * rows; j++) {
			if ((i < rows) & (j < rows)) {
				tmp[i][j] = matrix.at(i, j);
			}
			if (j == (i + rows)) {
				matrix.at(i, j) = 1;
			}
		}
	}
	for (auto i = rows - 1; i > 0; i--) {
		if (tmp[i - 1][0] < tmp[i][0]) {
			for (auto j = 0; j < 2 * rows; j++) {
				std::swap(tmp[i][j], tmp[i - 1][j]);
			}
		}
	}
	for (auto i = 0; i < rows; i++) {//цикл по строкам
		for (auto j = 0; j < rows; j++) {//цикл по столбцам
			if (j != i) {
				temp = tmp[j][i] / tmp[i][i];
				for (auto k = 0; k < 2 * rows; k++) {
					tmp[j][k] -= tmp[i][k] * temp;
				}
			}

		}

	}
	for (auto i = 0; i < rows; i++) {
		temp = tmp[i][i];
		for (auto j = 0; j < 2 * rows; j++) {
			tmp[i][j] = tmp[i][j] / temp;
			if (abs(tmp[i][j] - 0) < 0.00001) {
				tmp[i][j] = 0;
			}
		}
	}

	for (auto i = 0; i < rows; i++) {
		for (auto j = 0; j < rows; j++) {
			inv.at(i, j)= tmp[i][j + rows];
		}
	}
	return inv;
}

Matrix TransposeMatrix(const Matrix& matrix) {
	auto cols = matrix.get_cols_amount();
	auto rows = matrix.get_rows_amount();
	Matrix transp(cols, rows);
	for (auto i = 0; i < rows; i++) {
		for (auto j = 0; j < cols; j++) {
			transp.at(j,i) = matrix.at(i,j);
		}
	}
	return transp;
}

void Transpose(Matrix& matrix) {
	auto cols = matrix.get_cols_amount();
	auto rows = matrix.get_rows_amount();
	Matrix transp(cols, rows);
	auto& data = matrix.get_data();
	for (auto i = 0; i < cols; i++) {
		for (auto j = 0; j < rows; j++) {
			transp.at(i, j) = data[j][i];
		}
	}
	matrix = transp;
}

bool Is_vector(const Matrix& matrix) {
	return matrix.get_cols_amount() == 1 || matrix.get_rows_amount() == 1;
}

double ScalarComp(const Matrix& left_vec, const Matrix& right_vec) {
	if (Is_vector(left_vec) * Is_vector(right_vec) == 0) {
		throw std::runtime_error("Scalar product is defined only for vectors");
	}
	else {
		auto left_cols = left_vec.get_cols_amount();
		auto left_rows = left_vec.get_rows_amount();
		auto right_cols = right_vec.get_cols_amount();
		auto right_rows = right_vec.get_rows_amount();
		double res = 0;
		if (std::max(left_cols, left_rows) != std::max(right_cols, right_rows)) {
			throw std::runtime_error("Different size of vectors");
		}
		else {
			if (left_cols < left_rows && right_cols < right_rows) {
				for (auto i = 0; i < left_rows; i++) {
					res += left_vec.at(i, 0) * right_vec.at(i, 0);
				}
			}
			else if (left_cols < left_rows && right_cols > right_rows) {
				for (auto i = 0; i < left_rows; i++) {
					res += left_vec.at(i, 0) * right_vec.at(0, i);
				}
			}
			else if (left_cols > left_rows && right_cols < right_rows) {
				for (auto i = 0; i < left_cols; i++) {
					res += left_vec.at(0, i) * right_vec.at(i, 0);
				}
			}
			else if (left_cols > left_rows && right_cols > right_rows) {
				for (auto i = 0; i < left_cols; i++) {
					res += left_vec.at(0, i) * right_vec.at(0, i);
				}
			}
			return res;
		}
	}
}
double Matrix::NormVector() {
	return std::sqrt(ScalarComp(*this, *this));
}
double Frobenius_norm(const Matrix& matrix) {
	double res = 0;
	auto cols = matrix.get_cols_amount();
	auto rows = matrix.get_rows_amount();
	for (auto i = 0; i < rows; i++) {
		for (auto j = 0; j < cols; j++) {
			res += matrix.at(i, j) * matrix.at(i, j);
		}
	}
	return res;
}

double AngleBeetween(const Matrix& left_vec, const Matrix& right_vec) {
	return (ScalarComp(left_vec, right_vec)) /
		(ScalarComp(left_vec, left_vec) *
			ScalarComp(right_vec, right_vec));
}
bool Is_Square_matrix(const Matrix& matrix) {
	return (matrix.get_cols_amount() == matrix.get_rows_amount());
}
int Matrix::MatrixRank() {
	if (!Is_Square_matrix(*this)) {
		throw std::runtime_error("The matrix is not square");
	}
	else {
		if (!rank) {
			auto& tmp = *this;
			Gauss(tmp);
			auto& matrix = tmp.get_data();
			int r = 0;
			for (const auto& line : matrix) {
				if (!(count(line.begin(), line.end(), 0) == line.size())) {
					r++;
				}
			}
			this->rank = r;
		}
	}
	return rank;
}

double Matrix::Matrix_trace() {
	if (!Is_Square_matrix(*this)) {
		throw std::runtime_error("The matrix is not square");
	}
	else {
		auto& matrix = this->get_data();
		auto rows = this->get_rows_amount();
		double trace = 0;
		for (auto i = 0; i < rows; i++) {
			trace += matrix[i][i];
		}
		return trace;
	}
}

double Matrix::Matrix_Det() {

	if (!Is_Square_matrix(*this)) {
		throw std::runtime_error("The matrix is not square");
	}
	if (!det) {
		auto& matrix = *this;
		auto rows = matrix.get_rows_amount();
		double det = 0;
		Gauss(matrix);
		for (auto i = 0; i < rows; i++) {
			det += matrix.at(i, i);
		}
		this->det = det;
	}
	return det;
}

bool Matrix::load_tfile(const std::string& directory, mode mode) const {
	std::ofstream fout;
	auto& matrix = *this;
	auto rows = matrix.get_rows_amount();
	auto cols = matrix.get_cols_amount();
	if (mode == mode::txt) {
		fout.open(directory);
		fout << rows << cols << std::endl;
		fout << *this;
	}
	else if (mode == mode::bin) {
		fout.open(directory, std::ifstream::binary);
		fout.write((char*)&rows, sizeof rows);
		fout.write((char*)&cols, sizeof cols);
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				fout.write((char*)&matrix.at(i, j), sizeof(double));
	}
	return true;
}
void Matrix::set_matrix_size(int rows, int cols) {
	rows_amount = rows;
	cols_amount = cols;
	matrix_data.assign(rows, std::vector<double>(cols, 0));
}

bool Matrix::get_ffile(const std::string& directory, mode mode) {
	std::ifstream fin;
	int rows, cols;
	double current_num = 0;
	auto i = 0;
	auto j = 0;
	if (mode == mode::txt) {
		fin.open(directory);
		fin >> rows >> cols;
		this->set_matrix_size(int(rows), int(cols));
		fin >> *this;
	}
	else if (mode == mode::bin)
	{
		fin.open(directory, std::ifstream::binary);

		fin.read((char*)&rows, sizeof(int));
		fin.read((char*)&cols, sizeof(int));
		this->set_matrix_size(int(rows), int(cols));
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				fin.read((char*)&this->at(i, j), sizeof(double));
	}
	return true;
}
