#include "SquareMatrix.hpp"
#include <cassert>
#include <vector>



SquareMatrix::SquareMatrix(std::vector<double> diagonal) {
    size_ = diagonal.size();
    elements_sum_ = get_vector_summ(diagonal);
    matrix_ = matrix_allocator(size_, true);
    for (size_t i = 0; i < size_; i++) {
        matrix_[i * size_ + i] = diagonal[i];
    }
}

double* SquareMatrix::matrix_allocator(size_t size, bool fill_null) {
    if (fill_null) return new double[size * size]();
    return new double[size * size];
}

size_t SquareMatrix::get_size() {
    return size_;
}

double SquareMatrix::get_vector_summ(std::vector<double> vector){
    double summ = 0;
    for (double element: vector) summ += element;
    return summ;
}


SquareMatrix apply(const SquareMatrix& first, const SquareMatrix& second, std::function<double(double, double)> func) {
    if (first.size_ != second.size_) throw std::length_error("Sizes of matrices are not equal!");
    SquareMatrix result(first.size_);
    for(size_t i = 0; i < result.size_; i++) {
        for(size_t j = 0; j < result.size_; j++){
            double value = func(first[i][j], second[i][j]);
            result.elements_sum_ += value - result[i][j];
            result[i][j] = value;
        }
    }
    return result;
}

SquareMatrix matrix_mult(const SquareMatrix& first, const SquareMatrix& second){
    if (first.size_ != second.size_) throw std::length_error("Sizes of matrices are not equal!");
    SquareMatrix result(first.size_);
    for(size_t i = 0; i < result.size_; i++) {
        for(size_t j = 0; j < result.size_; j++){
            for(size_t k = 0; k < result.size_; k++) {
                double value = first[i][k] * second[k][j];
                result.elements_sum_ += value;
                result[i][j] += value;
            }
        }
    }
    return result;
}

void print_matrix(const SquareMatrix& matrix) {
    if (matrix.size_ == 0) {
        std::cout << "No elements to print. Matrix is empty!" << std::endl;
        return;
    } 
    for (size_t i = 0; i < matrix.size_; i++) {
        std::ostringstream row;
        for (size_t j = 0; j < matrix.size_; j++){
            row << matrix[i][j] << " ";
        }
        std::cout << row.str() << std::endl;
    }
}


// Returns summ of matrix elements
SquareMatrix::operator double() const { return elements_sum_;};
SquareMatrix::Row SquareMatrix::operator[](size_t index) {
    if (index > size_ || index < 0) throw std::out_of_range("Index is out of range!");
    return Row(matrix_ + index * size_, size_);
}
const SquareMatrix::Row SquareMatrix::operator[](size_t index) const {
    if (index > size_ || index < 0) throw std::out_of_range("Index is out of range!");
    return Row(matrix_ + index * size_, size_);
}


// Matrix operators
SquareMatrix& SquareMatrix::operator=(SquareMatrix other){
    if (other.size_ == this->size_) throw std::length_error("Sizes of matrices are not equal!");
    std::swap(this->matrix_, other.matrix_);
    std::swap(elements_sum_, other.elements_sum_);
    std::swap(size_, other.size_);
    return *this;
 }

SquareMatrix operator+(const SquareMatrix& first, const SquareMatrix& second){
    return apply(first, second, [](double a, double b){return a + b;});
}

SquareMatrix operator-(const SquareMatrix& first, const SquareMatrix& second){
    return apply(first, second, [](double a, double b){return a - b;});
}

SquareMatrix operator*(const SquareMatrix& first, const SquareMatrix& second){
    return matrix_mult(first, second);
}

SquareMatrix& SquareMatrix::operator+=( const SquareMatrix& other){
    *this = *this + other;
    return *this;
}

SquareMatrix& SquareMatrix::operator*=(const SquareMatrix& other){
    *this = *this * other;
    return *this;
}

bool operator==(const SquareMatrix& first, const SquareMatrix& second) {
    if (first.size_ != second.size_) throw std::length_error("Sizes of matrices are not equal!");
    size_t size_ = first.size_;
    for(size_t i = 0; i < size_; i++) {
        for(size_t j = 0; j < size_; j++){
            if (first[i][j] != second[i][j]) return false;
        }
    }
    return true;
}

bool operator!=(const SquareMatrix& first, const SquareMatrix& second) {
    return !(first == second);
}

// TODO : add scalar on the left side operator
// Scalar opeartors
SquareMatrix operator+(const SquareMatrix& matrix, const double scalar){
    return matrix + std::vector<double>(matrix.size_, scalar);
}

SquareMatrix operator-(const SquareMatrix& matrix, const double scalar){
    return matrix - std::vector<double>(matrix.size_, scalar);
}

SquareMatrix operator*(const SquareMatrix& matrix, const double scalar){
    return matrix * std::vector<double>(matrix.size_, scalar);
}

SquareMatrix operator+(const double scalar, const SquareMatrix& matrix){
    return std::vector<double>(matrix.size_, scalar) + matrix;
}

SquareMatrix operator-(const double scalar, const SquareMatrix& matrix){
    return std::vector<double>(matrix.size_, scalar) - matrix;
}

SquareMatrix operator*(const double scalar, const SquareMatrix& matrix){
    return std::vector<double>(matrix.size_, scalar) * matrix ;
}

SquareMatrix& SquareMatrix::operator*=(const double scalar){
    *this *= std::vector<double>(size_, scalar);
    return *this;
}

SquareMatrix& SquareMatrix::operator+=(const double scalar){
    *this += std::vector<double>(size_, scalar);
    return *this;
}

