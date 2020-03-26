#include "../inc/cxz_vector3.h"
cxz::MyVector3 cxz::operator+(const cxz::MyVector3 &v1, const cxz::MyVector3 &v2)
{
    cxz::MyVector3 v3;
    v3.coord[0] = v1.coord[0] + v2.coord[0];
    v3.coord[1] = v1.coord[1] + v2.coord[1];
    v3.coord[2] = v1.coord[2] + v2.coord[2];
    return v3;
}

cxz::MyVector3 cxz::operator-(const cxz::MyVector3 &v1, const cxz::MyVector3 &v2)
{
    cxz::MyVector3 v3;
    v3.coord[0] = v1.coord[0] - v2.coord[0];
    v3.coord[1] = v1.coord[1] - v2.coord[1];
    v3.coord[2] = v1.coord[2] - v2.coord[2];
    return v3;
}

cxz::MyVector3 cxz::operator^(const cxz::MyVector3 &v1, const cxz::MyVector3 &v2)
{
    cxz::MyVector3 v3;
    v3.coord[0] = v1.coord[1] * v2.coord[2] - v1.coord[2] * v2.coord[1];
    v3.coord[1] = v1.coord[2] * v2.coord[0] - v1.coord[0] * v2.coord[2];
    v3.coord[2] = v1.coord[0] * v2.coord[1] - v1.coord[1] * v2.coord[0];
    return v3;
}

double cxz::operator*(const cxz::MyVector3 &v1, const cxz::MyVector3 &v2)
{
    return (v1.coord[0] * v2.coord[0] + v1.coord[1] * v2.coord[1] + v1.coord[2] * v2.coord[2]);
}

cxz::MyVector3 cxz::operator*(double &k, const cxz::MyVector3 &v)
{
    cxz::MyVector3 temp;
    temp.coord[0] = v.coord[0] * k;
    temp.coord[1] = v.coord[1] * k;
    temp.coord[2] = v.coord[2] * k;
    return temp;
}

bool cxz::operator==(const cxz::MyVector3 &v1, const cxz::MyVector3 &v2)
{
    if (v1.coord[0] == v2.coord[0] && v1.coord[1] == v2.coord[1] && v1.coord[2] == v2.coord[2])
        return 1;
    return 0;
}