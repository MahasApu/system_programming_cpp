#pragma once

#include <iostream>
#include <sstream>
#include <functional>


class SquareMatrix {
    size_t size_ = 0;
    double elements_sum_ = 0;
    std::vector<std::vector<double>> matrix_;

public:
    SquareMatrix(const SquareMatrix& other) = default;
    SquareMatrix(SquareMatrix&& other) = default;
    SquareMatrix(std::vector<double> diagonal);
    SquareMatrix(std::vector<std::vector<double>> raw_matrix);
    SquareMatrix(size_t size):
                  size_(size) { resize(size_); }

    SquareMatrix& operator=(SquareMatrix other);
    std::vector<double>& operator[](size_t index);
    const std::vector<double>& operator[](size_t index) const;
    explicit operator double() const; // Returns summ of matrix elements

    SquareMatrix operator+(const SquareMatrix& other);
    SquareMatrix operator-(const SquareMatrix& other);
    SquareMatrix operator*(const SquareMatrix& other);
    SquareMatrix& operator+=(const SquareMatrix& other);
    SquareMatrix& operator*=(const SquareMatrix& other);

    bool operator==(const SquareMatrix& other);
    bool operator!=(const SquareMatrix& other);

    SquareMatrix operator+(const double scalar);
    SquareMatrix operator-(const double scalar);
    SquareMatrix operator*(const double scalar);
    SquareMatrix& operator+=(const double scalar);
    SquareMatrix& operator*=(const double scalar);

    ~SquareMatrix() = default;

    void print_matrix();

private:

    void resize(size_t size);
    void apply(double scalar, std::function<double(double, double)> func);
    void apply(const SquareMatrix& other, std::function<double(double, double)> func);
    static double get_vector_summ(std::vector<double> vector);
    
};


