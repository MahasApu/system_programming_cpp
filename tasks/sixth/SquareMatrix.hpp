#pragma once

#include <iostream>
#include <sstream>
#include <functional>


class SquareMatrix {
    size_t size_ = 0;
    double elements_sum_ = 0;
    std::vector<std::vector<double>> matrix_;

public:
    SquareMatrix(std::vector<double> diagonal);
    SquareMatrix(size_t size):
                        size_(size) { resize(size_); }
    SquareMatrix(const SquareMatrix& other):
                        matrix_(other.matrix_),
                        size_(other.size_),
                        elements_sum_(other.elements_sum_) { }

    SquareMatrix(SquareMatrix&& other):
                        matrix_(std::move(other.matrix_)),
                        size_(other.size_),
                        elements_sum_(other.elements_sum_) 
    { 
        other.elements_sum_ = 0;
        other.size_ = 0;
    }

    // For double indexing
    std::vector<double>& operator[](size_t index);
    const std::vector<double>& operator[](size_t index) const;

    // Returns summ of matrix element
    explicit operator double() const; 

    SquareMatrix& operator=(SquareMatrix other);
    SquareMatrix operator+(const SquareMatrix& other);
    SquareMatrix operator-(const SquareMatrix& other);
    SquareMatrix operator*(const SquareMatrix& other);
    SquareMatrix& operator+=(const SquareMatrix& other);
    SquareMatrix& operator*=(const SquareMatrix& other);

    bool operator==(const SquareMatrix& other) const;
    bool operator!=(const SquareMatrix& other) const;

    SquareMatrix operator+(const double scalar);
    SquareMatrix operator-(const double scalar);
    SquareMatrix operator*(const double scalar);
    SquareMatrix& operator+=(const double scalar);
    SquareMatrix& operator*=(const double scalar);

    ~SquareMatrix() = default;

    void print_matrix();
    size_t get_size();

private:

    SquareMatrix matrix_mult(const SquareMatrix& other);
    void resize(size_t size);
    void apply(double scalar, std::function<double(double, double)> func);
    void apply(const SquareMatrix& other, std::function<double(double, double)> func);
    static double get_vector_summ(std::vector<double> vector);

    
};


