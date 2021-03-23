#pragma once
class Matrix
{
public:
	int rows, cols;
	float* values;

	Matrix();
	Matrix(int rows, int cols);
	Matrix copy();

	static Matrix fromArray(float arr[], int length);

	float* toArray();

	void multiply(float n);
	void add(float n);

	static Matrix random(int rows, int cols);
	void randomize();

	static Matrix subtract(Matrix a, Matrix b);
	void add(Matrix other);
	void multiply(Matrix other);

	static Matrix transpose(Matrix a);
	static Matrix product(Matrix a, Matrix b);

	float get(int x, int y);
	void set(int x, int y, float val);
};

