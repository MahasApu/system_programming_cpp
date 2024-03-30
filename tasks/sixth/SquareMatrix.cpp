#include "SquareMatrix.hpp"
#include <cassert>

double SquareMatrix::get_vector_summ(std::vector<double> vector){
    double summ = 0;
    for(double element: vector) summ += element;
    return summ;
}


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

SquareMatrix::SquareMatrix(std::vector<std::vector<double>> raw_matrix) {
    size_ = raw_matrix.size();
    resize(size_);
}

void SquareMatrix::resize(size_t size) { 
    matrix_.resize(size);
    for (std::vector<double> column : matrix_) { column.resize(size, 0); }
}

// Returns summ of matrix elements
SquareMatrix::operator double() const { return elements_sum_;};
std::vector<double>& SquareMatrix::operator[](size_t index) { return matrix_[index];}
const std::vector<double>& SquareMatrix::operator[](size_t index) const { return matrix_[index];}


void SquareMatrix::print_matrix() {
    for (std::vector<double> column : matrix_) {
        std::ostringstream row;
        for (size_t i = 0; i < column.size(); i++){
            row << column[i] << " ";
        }
        std::cout << row.str() << std::endl;
    }
}

void SquareMatrix::apply(double scalar, std::function<double(double, double)> func) {
    for(size_t i = 0; i < size_; i++) {
        elements_sum_ += func(scalar, matrix_[i][i]) - matrix_[i][i];
        matrix_[i][i] = func(scalar, matrix_[i][i]);
    }
}

void SquareMatrix::apply(const SquareMatrix& other, std::function<double(double, double)> func) {
    assert((other.size_ == this->size_) && "Sizes of matrices are not equal!");
    for(size_t i = 0; i < size_; i++) {
        for(size_t j = 0; j < size_; j++){
            elements_sum_ += func(other[i][j], matrix_[i][j]) - matrix_[i][j];
            matrix_[i][j] = func(other[i][j], matrix_[i][j]);
        }
    }
}

// Matrix operators
SquareMatrix& SquareMatrix::operator=(SquareMatrix other){
    assert((other.size_ == this->size_) && "Sizes of matrices are not equal!");
    std::swap(this->matrix_, other.matrix_);
    elements_sum_ = other.elements_sum_;
    return *this;
 }

SquareMatrix SquareMatrix::operator+(const SquareMatrix& other){
    SquareMatrix new_matrix = *this;
    new_matrix.apply(other, [](double a, double b){return a + b;});
    return new_matrix;
};

SquareMatrix SquareMatrix::operator-(const SquareMatrix& other){
    SquareMatrix new_matrix = *this;
    new_matrix.apply(other, [](double a, double b){return a + b;});
    return new_matrix;
};

SquareMatrix SquareMatrix::operator*(const SquareMatrix& other){
    SquareMatrix new_matrix = *this;
    new_matrix.apply(other, [](double a, double b){return a + b;});
    return new_matrix;
};

SquareMatrix& SquareMatrix::operator+=(const SquareMatrix& other){
    apply(other, [](double a, double b){return a * b;});
    return *this;
};
SquareMatrix& SquareMatrix::operator*=(const SquareMatrix& other){
    apply(other, [](double a, double b){return a * b;});
    return *this;
};

bool SquareMatrix::operator==(const SquareMatrix& other){
    for(size_t i = 0; i < size_; i++) {
        for(size_t j = 0; j < size_; j++){
            if (matrix_[i][j] != other[i][j]) return false;
        }
    }
    return true;
}
bool SquareMatrix::operator!=(const SquareMatrix& other){
    return !(*this == other);
}


// Scalar opeartors
SquareMatrix SquareMatrix::operator+(const double scalar){
    SquareMatrix new_matrix = *this;
    new_matrix.apply(scalar, [](double a, double b){return a + b;});
    return new_matrix;
};

SquareMatrix SquareMatrix::operator-(const double scalar){
    SquareMatrix new_matrix = *this;
    new_matrix.apply(scalar, [](double a, double b){return a - b;});
    return new_matrix;
};

SquareMatrix SquareMatrix::operator*(const double scalar){
    SquareMatrix new_matrix = *this;
    new_matrix.apply(scalar, [](double a, double b){return a * b;});
    return new_matrix;
};

SquareMatrix& SquareMatrix::operator*=(const double scalar){
    apply(scalar, [](double a, double b){return a * b;});
    return *this;
};

SquareMatrix& SquareMatrix::operator+=(const double scalar){
    apply(scalar, [](double a, double b){return a + b;});
    return *this;
};

