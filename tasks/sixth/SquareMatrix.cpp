#include "SquareMatrix.hpp"
#include <cassert>
#include <vector>



SquareMatrix::SquareMatrix(d_vector_t diagonal) {
    size_ = diagonal.size();
    elements_sum_ = get_vector_summ(diagonal);
    matrix_.resize(size_);
    int counter = 0;
    for (size_t i = 0; i < size_; i++) {
        matrix_[i].resize(size_, 0);
        matrix_[i][counter] = diagonal[counter];  
        counter++;
    }
}

void SquareMatrix::resize(size_t size) { 
    matrix_.resize(size);
    for (size_t i = 0; i < size_; i++) { matrix_[i].resize(size, 0); }
}

size_t SquareMatrix::get_size() {
    return size_;
}

double SquareMatrix::get_vector_summ(d_vector_t vector){
    double summ = 0;
    for (double element: vector) summ += element;
    return summ;
}


SquareMatrix apply(const SquareMatrix& first, const SquareMatrix& second, std::function<double(double, double)> func) {
    assert((first.size_ == second.size_) && "Sizes of matrices are not equal!"); 
    SquareMatrix result(first.size_);
    for(size_t i = 0; i < result.size_; i++) {
        for(size_t j = 0; j < result.size_; j++){
            double value = func(first.matrix_[i][j], second.matrix_[i][j]);
            result.elements_sum_ += value - result.matrix_[i][j];
            result.matrix_[i][j] = value;
        }
    }
    return result;
}

SquareMatrix matrix_mult(const SquareMatrix& first, const SquareMatrix& second){
    assert((first.size_ == second.size_) && "Sizes of matrices are not equal!");
    SquareMatrix result(first.size_);
    for(size_t i = 0; i < result.size_; i++) {
        for(size_t j = 0; j < result.size_; j++){
            for(size_t k = 0; k < result.size_; k++) {
                double value = first.matrix_[i][k] * second.matrix_[k][j];
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
    for (d_vector_t column : matrix.matrix_) {
        std::ostringstream row;
        for (size_t i = 0; i < column.size(); i++){
            row << column[i] << " ";
        }
        std::cout << row.str() << std::endl;
    }
}


// Returns summ of matrix elements
SquareMatrix::operator double() const { return elements_sum_;};
d_vector_t& SquareMatrix::operator[](size_t index) { return matrix_[index];}
const d_vector_t& SquareMatrix::operator[](size_t index) const { return matrix_[index];}


// Matrix operators
SquareMatrix& SquareMatrix::operator=(SquareMatrix other){
    assert((other.size_ == this->size_) && "Sizes of matrices are not equal!");
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
    assert((first.size_ == second.size_) && "Sizes of matrices are not equal!");
    size_t size_ = first.size_;
    for(size_t i = 0; i < size_; i++) {
        for(size_t j = 0; j < size_; j++){
            if (first.matrix_[i][j] != second.matrix_[i][j]) return false;
        }
    }
    return true;
}

bool operator!=(const SquareMatrix& first, const SquareMatrix& second) {
    return !(first == second);
}

// Scalar opeartors
SquareMatrix operator+(const SquareMatrix& matrix, const double scalar){
    return matrix + d_vector_t(matrix.size_, scalar);
}

SquareMatrix operator-(const SquareMatrix& matrix, const double scalar){
    return matrix - d_vector_t(matrix.size_, scalar);
}

SquareMatrix operator*(const SquareMatrix& matrix, const double scalar){
    return matrix * d_vector_t(matrix.size_, scalar);
}

SquareMatrix& SquareMatrix::operator*=(const double scalar){
    *this *= d_vector_t(size_, scalar);
    return *this;
}

SquareMatrix& SquareMatrix::operator+=(const double scalar){
    *this += d_vector_t(size_, scalar);
    return *this;
}

