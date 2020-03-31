#ifndef _CXZ_VECTOR3_
#define _CXZ_VECTOR3_
#define ZERO 0.0000001
#include <vector>
#include <cstddef>
#include <string>
namespace cxz{
    struct MyVector3{
        double coord[3];
    };
    struct Edge {
	    size_t point_index[2];
    };
    struct Triangle {
	    size_t edge_index[3];
	    size_t point_index[3];
    };
    class ObjStore {
	    std::vector<MyVector3> point;
	    std::vector<Edge> edge;
	    std::vector<Triangle> triangle;
    public:
        int read_obj(std::string s);
        int calc_min_distance()
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