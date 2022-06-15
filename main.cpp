#include "Matrix.h"
#include "PCA.h"

#define eps 0.00000001
int main() {
	Matrix A;
	A.get_ffile("test_PCA.txt", mode::txt);
	std::cout << A.get_rows_amount() << " " << A.get_cols_amount() << std::endl;
	std::cout << A << std::endl;
	PCA p(A);
	auto data_test = A.get_data();

	std::cout << AVG(data_test[0]) << std::endl;
	std::cout << SD(data_test[0], AVG(data_test[0])) << std::endl;
	p.Calibration();
	std::cout << p.Get_scaled_matrix() << std::endl;
	NIP decomp = p.Decompose(eps, 12);
	std::cout << "Matrix T:" << std::endl;
	std::cout << decomp.T << std::endl;
	std::cout << "Matrix P:" << std::endl;
	std::cout << decomp.P << std::endl;
	std::cout << "Matrix E:" << std::endl;
	std::cout << decomp.E << std::endl;
	Disperse disperse = p.ResidualsDisperse();
	std::cout << "TRV:" << std::endl;
	std::cout << disperse.TRV << std::endl;
	std::cout << "ERV:" << std::endl;
	std::cout << disperse.ERV << std::endl;



}