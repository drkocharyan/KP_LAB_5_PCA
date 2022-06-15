#include <iostream>
#include <assert.h>

using namespace std;

class ComplexNumber {
public:
	ComplexNumber() : real(0),imaginary(0) {}
	ComplexNumber(double real_,double imaginary_) : real(real_),imaginary(imaginary_){}

	void setReal(double real_) {
		real = real_;
	}
	void setImaginary(double imaginary_) {
		imaginary = imaginary_;
	}

	double getReal() const {
		return real;
	}

	double getImaginary() const {
		return imaginary;
	}

	ComplexNumber operator+(const ComplexNumber& other) {
		return ComplexNumber(real + other.getReal(), imaginary + other.getImaginary());
	}

	ComplexNumber operator-(const ComplexNumber& other) {
		return ComplexNumber(real - other.getReal(), imaginary - other.getImaginary());
	}

	ComplexNumber operator*(const ComplexNumber& other) {
		auto new_real = real * other.getReal() - imaginary * other.getImaginary();
		auto new_imaginary = (real * other.getImaginary() + imaginary * other.getReal());
		return ComplexNumber(new_real, new_imaginary);
	}

	ComplexNumber operator/(const ComplexNumber& other) {
		ComplexNumber sopr(other.getReal(), (-1) * other.getImaginary());
		auto new_real = ( this->getReal() * other.getReal() + this->getImaginary() * other.getImaginary() ) / 
			(other.getReal() * other.getReal() + other.getImaginary()*other.getImaginary());
		auto new_imaginary = (this->getImaginary() * other.getReal() - this->getReal() * other.getImaginary()) /
			(other.getReal() * other.getReal() + other.getImaginary()*other.getImaginary());
		return ComplexNumber(new_real, new_imaginary);
	}

	friend ostream& operator<<(ostream& os, const ComplexNumber& cn);
	friend bool operator==(const ComplexNumber& left, const ComplexNumber& right);

private:
	double real = 0, imaginary = 0;
};

ostream& operator<<(ostream& os, const ComplexNumber& cn) {
	os << cn.real;
	if (cn.imaginary != 0) {
		cn.imaginary < 0 ? os << cn.imaginary : os << '+' << cn.imaginary;
		os << 'i' << endl;

	}
	return os;
}

bool operator==(const ComplexNumber& left, const ComplexNumber& right) {
	return left.getReal() == right.getReal() && left.getImaginary() == right.getImaginary();
}



