#pragma once
#include "PCA.h"
#include <cmath>

PCA::PCA(const Matrix& X_matrix) {
	X = X_matrix;
}

double AVG(const std::vector<double>& col) {
	double avg = 0;
	for (const auto& el : col) {
		avg += el;
	}
	return avg / col.size();
}

double SD(const std::vector<double>& col, const double& avg) {
	double sd = 0;
	auto el_num = col.size();
	for (const auto& el : col) {
		sd += pow(el - avg, 2);
	}
	return sqrt(sd / (el_num - 1));
}

void PCA::Calibration() {
	auto Xt = TransposeMatrix(X);
	auto cols_data = Xt.get_data();
	for (auto& row : cols_data) {
		double r_avg = AVG(row);
		double r_sd = SD(row, r_avg);
		for (auto& elem : row) {
			elem = (elem - r_avg) / r_sd;
		}
	}
	auto res = Matrix(cols_data);
	X_cal = TransposeMatrix(res);
}

Matrix PCA::Get_scaled_matrix() const{
	return X_cal;
}

NIP PCA::Decompose(double eps, size_t A) {
	auto E = X_cal;
	auto rows = E.get_rows_amount();
	auto cols = E.get_cols_amount();
	std::vector <std::vector<double>> TT, PP;
	Matrix t(rows, 1), p(rows, 1), t_old(rows, 1);
	bool f1=false;

	for (size_t k = 0; k < A; k++) {
		for (size_t j = 0; j < rows; j++) {
			t.at(j, 0) = E.at(j, k);
		}
		do {
			p = TransposeMatrix(TransposeMatrix(t) * E);
			if (!f1) {
				std::cout << (TransposeMatrix(t) * E) << std::endl << std::endl;
				f1 = true;
			}
			p = p / ScalarComp(TransposeMatrix(t), t);
			p = p / sqrt(ScalarComp(TransposeMatrix(p), p));
			t_old = t;
			t = (E * p) / ScalarComp(TransposeMatrix(p), p);
		} while ((t_old - t).NormVector() > eps);
		TT.push_back(TransposeMatrix(t).get_data()[0]);
		PP.push_back(TransposeMatrix(p).get_data()[0]);
		E = E - t * TransposeMatrix(p);
	}
	this->decompose.E = E;
	this->decompose.T = TransposeMatrix(Matrix(TT));
	this->decompose.P = TransposeMatrix(Matrix(PP));
	this->nip_flag = true;
	return decompose;
}

std::vector<double> PCA::Scope() {
	if (!nip_flag) {
		throw std::runtime_error("Firstly, you have to use NIPALS");
	}
	Matrix TT = decompose.T;
	auto rows = TT.get_rows_amount();
	auto cols = TT.get_cols_amount();
	Matrix t(1, cols);
	Matrix TtT = TransposeMatrix(TT) * TT;
	TtT = InverseMatrix(TtT);
	for (auto i = 0; i < rows; i++) {
		for (auto j = 0; j < cols; j++) {
			t.at(0, j) = TT.at(i, j);
		}
		double Hi = (t * TtT * TransposeMatrix(t)).at(0, 0);
		H.push_back(Hi);
	}
	return H;
}

std::vector<double> PCA::Deviation() {
	if (!nip_flag) {
		throw std::runtime_error("Firstly, you have to use NIPALS");
	}
	Matrix EE = decompose.E;
	auto rows = EE.get_rows_amount();
	auto cols = EE.get_cols_amount();
	for (auto i = 0; i < rows; i++) {
		double Vi = 0;
		for (auto j = 0; j < cols; j++) {
			Vi += pow(EE.at(i, j), 2);
		}
		V.push_back(Vi);
	}
	return V;
}

Disperse PCA::ResidualsDisperse() {
	if (!nip_flag) {
		throw std::runtime_error("Firstly, you have to use NIPALS");
	}
	if (V.size() == 0) {
		this->Deviation();
	}
	double v0 = AVG(V);
	Matrix EE = decompose.E;
	auto rows = EE.get_rows_amount();
	auto cols = EE.get_cols_amount();
	auto x_rows = X_cal.get_rows_amount();
	auto x_cols = X_cal.get_cols_amount();
	residuals.TRV = v0 / cols;
	
	double s = 0;
	for (auto i = 0; i < x_rows; i++) {
		for (auto j = 0; j < x_cols; j++) {
			s += pow(X_cal.at(i, j), 2);
		}
	}
	residuals.ERV = 1 - v0 * rows / s;
	return residuals;
}

