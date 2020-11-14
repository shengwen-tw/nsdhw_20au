#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <iostream>
#include <string>
#include <vector>
#include "matrix_allocator.h"

#define N 1024
#define BLOCK_SIZE 64
#define PADDING_ZEROS 64 //in case block size doesn't fit

using namespace std;

extern MatrixDataAllocator<double> matrix_memory_manager;

class Matrix {
public:
	Matrix();
	Matrix(int _row, int _column): data(matrix_memory_manager) {
		_row += PADDING_ZEROS;
		_column += PADDING_ZEROS;

        //cout << "address of allocator = " << &matrix_memory_manager << endl;

        this->data.resize(_row * _column);

		this->n_row = _row;
		this->n_column = _column;
	}

	~Matrix() {
	}

	void clean(void) {
        data.clear();
	}

	int row(void) {
		return this->n_row - PADDING_ZEROS;
	}

	int column(void) {
		return this->n_column - PADDING_ZEROS;
	}

	bool operator== (const Matrix &rhs) {
		if(rhs.n_row != n_row) return false;
		if(rhs.n_column != n_column) return false;

		for(int r = 0; r < n_row; r++) {
			for(int c = 0; c < n_column; c++) {
				if(fabs(rhs.data.at(r * n_column + c) - data.at(r * n_column + c)) > 0.0001) {
					return false;
				}
			}
		}
		return true;
	}

	bool operator!= (const Matrix &rhs) {
		if(rhs.n_row != n_row) return true;
		if(rhs.n_column != n_column) return true;

		for(int r = 0; r < n_row; r++) {
			for(int c = 0; c < n_column; c++) {
				if(fabs(rhs.data.at(r * n_column + c) - data.at(r * n_column + c)) > 0.0001) {
					return true;
				}
			}
		}

		return false;
	}

	double & operator() (int r, int c) {
		return data.at(r * this->n_column + c);
	}

	const double & operator() (int r, int c) const {
		return data.at(r * this->n_column + c);
	}

	double at(int r, int c) {
		return data.at(r * n_column + c);
	}

	void set(int r, int c, double val) {
		data.at(r * n_column + c) = val;
	}

	double *raw_data(void) {
        return &data[0];
	}

    const MatrixDataAllocator<double>& get_mem_alloc() const {
        return mem_alloc;
    }

private:
	int n_row;
	int n_column;

    MatrixDataAllocator<double> mem_alloc;
    std::vector<double, MatrixDataAllocator<double>> data;
};

size_t bytes();
size_t allocated();
size_t deallocated();
void random_matrix(Matrix &mat, double max_val);
Matrix multiply_naive(Matrix &mat1, Matrix &mat2);
Matrix  multiply_tile(Matrix &mat1, Matrix &mat2, int tile_size);
int matrix_compare(Matrix &mat1, Matrix &mat2);
Matrix multiply_mkl(Matrix &mat1, Matrix &mat2);
void print_matrix(const char *prompt, Matrix &mat);

#endif
