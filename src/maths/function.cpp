#include "function.hpp"
#include "column.hpp"

Function::Function()
{

}


double Function::interpolateLagrange(double x, int order) const
{   // Deal with border cases!
    int size = order+1;

    int pos;
    for (pos=0; pos<m_function.cols(); ++pos) {
        if (m_function[0][pos]<=x && m_function[0][pos+1]>x) {
            if (m_function[0][pos]==x)
                return m_function[1][pos];
            break;
        }
    }
    pos--;

    Row L(size);
    Column F(size);
    for(int i=pos; i<pos+size; i++) {
        F[i-pos] = m_function[1][i];
        L[i-pos] = 1;
        for (int m = 0; m < size; ++m)
            if (m!=(i-pos))
                L[i-pos]*= (x-m_function[0][pos+m])/(m_function[0][i]-m_function[0][pos+m]);
    }
    return L*F;

}
