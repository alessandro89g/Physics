#ifndef MATRIX4_HPP
#define MATRIX4_HPP

#include "../../../include/maths/vectors_matrices/matrix.hpp"
#include "../../../include/physics/four_vectors_tensors/vector4.hpp"

class Matrix4 : public Matrix {
public:
    Matrix4();
    Matrix4(const Vector4& v41, const Vector4& v42);
    Matrix4(const Matrix& m);

    static Matrix4 metricTensor();
    static Matrix4 identityMatrix();

    void setIndex(int index, Vector4::State state);
    void setIndex(Vector4::State state);


    void lowerIndex(int index);
    void lowerIndex();
    void raiseIndex(int index);
    void raiseIndex();
    void indexesState() const;

    Vector4 operator *(Vector4 v) const;

    int cols() const = delete;
    int rows() const = delete;
    int size() const;


protected:
    Vector4::State m_index1;
    Vector4::State m_index2;

protected:


};

#endif // MATRIX4_HPP
