#ifndef FUNCTION_H
#define FUNCTION_H

#include <functional>
#include <vector>
#include <iostream>
#include <fstream>
#include "matrix.hpp"
#include "column.hpp"
#include <math.h>

using namespace std;

class Function
{
public:
    Function();
    Function(vector<double> x) {
        m_size = x.size();
        createMatrix(m_size);
        fillFunctionX(x);
    }
    Function(double step, double x0, double x1) {
        m_size = (x1-x0)/step+1;
        createMatrix(m_size);
        fillFunctionX(step,x0,x1);
    }
    Function(double step, double x0, double x1, const std::function<double(double)> &fun) {
        m_size = (x1-x0)/step+1;
        createMatrix(m_size);
        fillFunctionX(step,x0,x1);
        fillFunctionY(fun);
    }

    Function(vector<double> x, const std::function< double(double) >& fun) {
        m_size = x.size();
        createMatrix(m_size);
        fillFunction(x, fun);
    }
    Function(vector<double> x, vector<double> y) {
        if (x.size()!= y.size())
            abort();
        m_size = x.size();
        createMatrix(m_size);
        fillFunction(x,y);
    }
    Function(const Function& other) = delete;

    void fillFunctionX(vector<double> x) {
        if (!m_created_matrix) {
            m_size = x.size();
            createMatrix(m_size);
        }
        for (int i=0; i<m_size; i++)
            m_function[0][i] = x[i];
        m_x_filled = true;
    }
    void fillFunctionX(double step, double x0, double x1) {
        m_size = (x1-x0)/step+1;
        if (!m_created_matrix)
            createMatrix(m_size);

        for (int i=0; i<m_size; i++)
            m_function[0][i] = x0 + step*i;
        m_x_filled = true;
    }
    void fillFunctionY(vector<double> y) {
        for (int i=0; i<m_size; i++)
            m_function[1][i] = y[i];
        m_y_filled = true;
    }
    void fillFunctionY(const std::function<double(double) >& fun) {
        if (!m_x_filled)
            abort();

        for (int i=0; i<m_size; i++)
            m_function[1][i] = fun(m_function[0][i]);
        m_y_filled = true;
    }

    void fillFunction(vector<double> x, const std::function< double(double) >& fun) {
        if (!m_created_matrix)
            abort();
        fillFunctionX(x);
        fillFunctionY(fun);
    }
    void fillFunction(vector<double> x, vector<double> y) {
        if (!m_created_matrix)
            abort();
        fillFunctionX(x);
        fillFunctionY(y);
    }

    bool exportFunction(const char* file) const {
        if (!m_created_matrix)
            abort();
        ofstream f(file);
        if (f.is_open()){
            for (int i=0; i<m_size; i++)
                f << m_function[0][i] << '\t' << m_function[1][i] << '\n';
            f.close();
            return true;
        }
        return false;
    }

    double &x(int index) {
        return (m_function.getMatrix()[0][index]);
    }
    double &y(int index)  {
        return (m_function.getMatrix()[1][index]);
    }


    int size() const {
        return m_size;
    }
    ~Function() {
    }

    double& operator[] (int index) {
        return (m_function.getMatrix()[1][index]);
    }

    double operator() (double x) const {
        return interpolateLagrange(x);
    }

    Function &operator * (double val) {
        for (int i=0; i<m_size; i++)
            m_function[1][i] *= val;
        return *this;
    }
    Function &operator / (double val) {
        for (int i=0; i<m_size; i++)
            m_function[1][i] /= val;
        return *this;
    }
    Function &operator *= (double val) {
        return (*this)*val;
    }
    Function &operator /= (double val) {
        return (*this)/val;
    }

    double interpolateLagrange(double x, int order = 3) const;

private:
    void createMatrix(int size) {
        m_function = Matrix(2, size);
        m_created_matrix = true;
    }

private:
    Matrix m_function;
    int m_size = -1;
    bool m_x_filled = false;
    bool m_y_filled = false;
    bool m_created_matrix = false;

};

#endif // FUNCTION_H
