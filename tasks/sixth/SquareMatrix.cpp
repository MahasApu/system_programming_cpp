#include "SquareMatrix.hpp"
#include <cassert>
#include <utility>
#include <vector>



SquareMatrix::SquareMatrix(std::vector<double> diagonal) {
    size_ = diagonal.size();
    matrix_.resize(size_);
    int counter = 0;
    for (size_t i = 0; i < size_; i++) {
        matrix_[i].resize(size_, 0);
        matrix_[i][counter] = diagonal[counter];  
        elements_sum_ += get_vector_summ(matrix_[i]);
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

double SquareMatrix::get_vector_summ(std::vector<double> vector){
    double summ = 0;
    for(double element: vector) summ += element;
    return summ;
}


void SquareMatrix::apply(double scalar, std::function<double(double, double)> func) {
    for(size_t i = 0; i < size_; i++) {
        double result = func(matrix_[i][i], scalar);
        elements_sum_ += result - matrix_[i][i];
        matrix_[i][i] = result;
    }
}

void SquareMatrix::apply(const SquareMatrix& other, std::function<double(double, double)> func) {
    assert((other.size_ == this->size_) && "Sizes of matrices are not equal!");
    for(size_t i = 0; i < size_; i++) {
        for(size_t j = 0; j < size_; j++){
            double result = func(matrix_[i][j], other.matrix_[i][j]);
            elements_sum_ += result - matrix_[i][j];
            matrix_[i][j] = result;
        }
    }
}

SquareMatrix SquareMatrix::matrix_mult(const SquareMatrix& other){
    assert((other.size_ == this->size_) && "Sizes of matrices are not equal!");
    SquareMatrix result(size_);
    for(size_t i = 0; i < size_; i++) {
        for(size_t j = 0; j < size_; j++){
            for(size_t k = 0; k < size_; k++) {
                double value = matrix_[i][k] * other.matrix_[k][j];
                result.elements_sum_ += value;
                result[i][j] += value;
            }
        }
    }
    return result;
}

void SquareMatrix::print_matrix() {
    if (size_ == 0) {
        std::cout << "No elements to print. Matrix is empty!" << std::endl;
        return;
    } 

    for (std::vector<double> column : matrix_) {
        std::ostringstream row;
        for (size_t i = 0; i < column.size(); i++){
            row << column[i] << " ";
        }
        std::cout << row.str() << std::endl;
    }
}


// Returns summ of matrix elements
SquareMatrix::operator double() const { return elements_sum_;};
std::vector<double>& SquareMatrix::operator[](size_t index) { return matrix_[index];}
const std::vector<double>& SquareMatrix::operator[](size_t index) const { return matrix_[index];}


// Matrix operators
SquareMatrix& SquareMatrix::operator=(SquareMatrix other){
    assert((other.size_ == this->size_) && "Sizes of matrices are not equal!");
    std::swap(this->matrix_, other.matrix_);
    std::swap(elements_sum_, other.elements_sum_);
    std::swap(size_, other.size_);
    return *this;
 }

SquareMatrix SquareMatrix::operator+(const SquareMatrix& other){
    SquareMatrix new_matrix = *this;
    new_matrix.apply(other, [](double a, double b){return a + b;});
    return new_matrix;
}

SquareMatrix SquareMatrix::operator-(const SquareMatrix& other){
    SquareMatrix new_matrix = *this;
    new_matrix.apply(other, [](double a, double b){return a - b;});
    return new_matrix;
}

SquareMatrix SquareMatrix::operator*(const SquareMatrix& other){
    SquareMatrix new_matrix = matrix_mult(other);
    return new_matrix;
}

SquareMatrix& SquareMatrix::operator+=(const SquareMatrix& other){
    apply(other, [](double a, double b){return a + b;});
    return *this;
}

SquareMatrix& SquareMatrix::operator*=(const SquareMatrix& other){
    *this = *this * other;
    return *this;
}

bool SquareMatrix::operator==(const SquareMatrix& other) const {
    for(size_t i = 0; i < size_; i++) {
        for(size_t j = 0; j < size_; j++){
            if (matrix_[i][j] != other[i][j]) return false;
        }
    }
    return true;
}

bool SquareMatrix::operator!=(const SquareMatrix& other) const {
    return !(*this == other);
}


// Scalar opeartors
SquareMatrix SquareMatrix::operator+(const double scalar){
    SquareMatrix new_matrix = *this;
    new_matrix.apply(scalar, [](double a, double b){return a + b;});
    return new_matrix;
}

SquareMatrix SquareMatrix::operator-(const double scalar){
    SquareMatrix new_matrix = *this;
    new_matrix.apply(scalar, [](double a, double b){return a - b;});
    return new_matrix;
}

SquareMatrix SquareMatrix::operator*(const double scalar){
    SquareMatrix new_matrix = *this;
    std::vector<double> tmp(size_, scalar);
    new_matrix.apply({tmp}, [](double a, double b){return a * b;} );
    return new_matrix;
}

SquareMatrix& SquareMatrix::operator*=(const double scalar){
    std::vector<double> tmp(size_, scalar);
    apply({tmp}, [](double a, double b){return a * b;} );
    return *this;
}

SquareMatrix& SquareMatrix::operator+=(const double scalar){
    apply(scalar, [](double a, double b){return a + b;});
    return *this;
}

