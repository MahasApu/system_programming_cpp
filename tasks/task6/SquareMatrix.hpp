#pragma once

#include <cmath>
#include <exception>
#include <iostream>
#include <sstream>
#include <functional>


class SquareMatrix {
    size_t size_ = 0;
    double elements_sum_ = 0;
    double* matrix_;

public:
    SquareMatrix(std::vector<double> diagonal);
    SquareMatrix(size_t size): size_(size) { matrix_ = matrix_allocator(size_, true); }
    SquareMatrix(const SquareMatrix& other):
                        size_(other.size_),
                        elements_sum_(other.elements_sum_)
    {
        matrix_ = matrix_allocator(size_, true);
        for (size_t i = 0; i < size_ * size_; i++) {
            matrix_[i] = other.matrix_[i];
        }
    }

    SquareMatrix(SquareMatrix&& other):
                        matrix_(other.matrix_),
                        size_(other.size_),
                        elements_sum_(other.elements_sum_) 
    { 
        other.elements_sum_ = 0;
        other.size_ = 0;
        other.matrix_ = nullptr;
    }

    class Row {
        double* row_;
        size_t row_size;
        
    public:
        Row(double* row, size_t size): row_(row), row_size(size) {                      
            // for (size_t i = 0; i < row_size; i++) std::cout << row_[i];
            // std::cout << " " << std::endl;
        }

        // for double indexing
        double& operator[](size_t index) {
            if (index > row_size || index < 0) throw std::out_of_range("Incorrect index for double indexing!");
            return row_[index];
        }

        const double& operator[](size_t index) const {
            if (index > row_size || index < 0) throw std::out_of_range("Incorrect index for double indexing!");
            return row_[index];
        }

    };

    // For double indexing
    // TODO: add exception
    Row operator[](size_t index);
    const Row operator[](size_t index) const;

    // Returns summ of matrix element
    explicit operator double() const; 

    SquareMatrix& operator=(SquareMatrix other);
    friend SquareMatrix operator+(const SquareMatrix& first, const SquareMatrix& second);
    friend SquareMatrix operator-(const SquareMatrix& first, const SquareMatrix& second);
    friend SquareMatrix operator*(const SquareMatrix& first, const SquareMatrix& second);
    SquareMatrix& operator+=(const SquareMatrix& other);
    SquareMatrix& operator*=(const SquareMatrix& other);

    friend bool operator==(const SquareMatrix& first, const SquareMatrix& second);
    friend bool operator!=(const SquareMatrix& first, const SquareMatrix& second);

    friend SquareMatrix operator+(const SquareMatrix& matrix, const double scalar);
    friend SquareMatrix operator-(const SquareMatrix& matrix, const double scalar);
    friend SquareMatrix operator*(const SquareMatrix& matrix, const double scalar);
    friend SquareMatrix operator+(const double scalar, const SquareMatrix& matrix);
    friend SquareMatrix operator-(const double scalar, const SquareMatrix& matrix);
    friend SquareMatrix operator*(const double scalar, const SquareMatrix& matrix);

    SquareMatrix& operator+=(const double scalar);
    SquareMatrix& operator*=(const double scalar);

    ~SquareMatrix() { delete[] matrix_; };

    friend void print_matrix(const SquareMatrix& matrix);
    size_t get_size();

private:

    void resize(size_t size);
    double*  matrix_allocator(size_t size, bool fill_null = false);
    static double get_vector_summ(std::vector<double> vector);
    friend SquareMatrix matrix_mult(const SquareMatrix& first, const SquareMatrix& second);
    friend SquareMatrix apply(const SquareMatrix& first, const SquareMatrix& second, std::function<double(double, double)> func);

    
};


