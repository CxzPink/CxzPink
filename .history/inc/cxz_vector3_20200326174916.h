#ifndef _CXZ_VECTOR3_
#define _CXZ_VECTOR3_
#define ZERO 0.0000001
namespace cxz{
    struct MyVector3{
        double coord[3];
    };
    double compute_distance_triangle_point(const double (&triangle_coord)[9],const double (&point_coord)[3]);
    double distance_edge_point(const MyVector3 &p_0,const MyVector3 &p_1,const MyVector3 &p_2);
    double area(const MyVector3 &p_0,const MyVector3 &p_1,const MyVector3 &p_2);
    double length(const MyVector3 &v);
    MyVector3 unitize(const MyVector3 &v);
    
    MyVector3 operator+(const MyVector3 &v1, const MyVector3 &v2);
    MyVector3 operator-(const MyVector3 &v1, const MyVector3 &v2);
    MyVector3 operator^(const MyVector3 &v1, const MyVector3 &v2);
    double operator*(const MyVector3 &v1, const MyVector3 &v2);
    MyVector3 operator*(double &k, const MyVector3 &v);
bool operator==(const MyVector3 &v1, const MyVector3 &v2);
}
#endif