#pragma once
#include <iostream>

class Vector {
public:
	// Constructor
	Vector(int n);

	// Destructor
	~Vector();

	// Operators
	double& operator[](int i);
	Vector& operator=(const Vector& other);
	friend Vector operator+(const Vector& v1, const Vector& v2);

private:
	int size;
	double* vec; //Pointer Only

	//Internal Range Checking
	int range(int i);
};