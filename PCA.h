#pragma once
#include "Matrix.h"
#include <cmath>
#include <vector>

struct NIP {
	Matrix T, P, E;
};

struct Disperse {
	double TRV;
	double ERV;
};

class PCA {
private:
	Matrix X, X_cal;
	bool nip_flag = false;
	NIP decompose;
	Disperse residuals;
	std::vector<double> H, V;

public:
	PCA(const Matrix& matrix);
	void Calibration();
	NIP Decompose(double eps = 0.00000001, size_t A = 1);
	Matrix Get_scaled_matrix() const;
	std::vector<double> Scope();
	std::vector<double> Deviation();
	Disperse ResidualsDisperse();
};

double SD(const std::vector<double>& col, const double& avg);
double AVG(const std::vector<double>& col);
