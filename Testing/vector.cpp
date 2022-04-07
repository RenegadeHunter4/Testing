#include "vector.h"

// Constructor
Vector::Vector(int n)
{
	size = n;  
	vec = new double[size];

	for (int i = 0; i < size; i++) {
		vec[i] = 0;
	}
}

// Destructor
Vector::~Vector() { 
	delete[] vec; 
}

// Operators
double& Vector::operator[](int i) {
	return vec[range(i)];
}

Vector& Vector::operator=(const Vector& other)
{
	if (size != other.size) {
		std::cerr << "FATAL vecotr::operator(const vector &) size mismatch: " << size << " " << other.size << std::endl;
		exit(1);
	}
	for (int i = 0; i < size; i++) {
		vec[i] = other.vec[i];
	}
	return *this;
}

inline int Vector::range(int i)
{
	if (i < 0 || i >= size) {
		std::cerr << "FATAL vector::range(" << i << ") out of bounds [0," << size - 1 << "]\n";
		exit(1);
	}

	return i;
}

Vector operator+(const Vector& v1, const Vector& v2)
{
	if (v1.size != v2.size) {
		std::cerr << "FATAL vecotr::operator(const vector &) size mismatch: " << v1.size << " != " << v2.size << std::endl;
		exit(1);
	}
	Vector v(v1.size); //temp vector for sum
	for (int i = 0; i < v1.size; i++) {
		v.vec[i] = v1.vec[i] + v2.vec[i];
	}
	return v;
}
/*
inline Vector operator+(const Vector& v1, const Vector& v2) {
	if (v1.size != v2.size) {
		std::cerr << "FATAL vector::operator+(const vector &, const vector&) size mismatch: ";
		std::cerr << v1.size << " " << " != " << v2.size << "\n";
		exit(1);
	}
	
	Vector v(v1.size);   // Construct a temporary vector to hold the sum
	for (int i = 0; i < v1.size; i++)
		v.vec[i] = v1.vec[i] + v2.vec[i];
	return v;
	
}*/
