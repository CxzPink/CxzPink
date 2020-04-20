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
        size_t triangle_index[2];
        Edge(const size_t &i,const size_t &j,const size_t &k);
    };
    struct Triangle {
	    size_t edge_index[3];
	    size_t point_index[3];
    };
    class Mesh {
	    std::vector<MyVector3> point;
	    std::vector<Edge> edge;
	    std::vector<Triangle> triangle;
        size_t point_number;
        size_t edge_number;
        size_t triangle_number;
    public:
        Mesh()=default;
        int read_obj(const std::string &s);
        int write_obj(const std::string &s);
        double calc_min_distance(const double (&p)[3]);
        void cut_edge(const double &max_length);
    private:
        void update_edge_index();
        int search_index_of_edge(const size_t &p_index1,const size_t &p_index2);
        int binary_edge(const size_t &my_edge_index);
        int get_edge_around_infor(const size_t &my_edge_index,size_t (&p_index)[4],size_t (&e_index)[4]);
    };
    class Heap{
        size_t number;
        std::vector<double> length;
        std::vector<size_t> index;
    public:
        Heap();
        int push(const double len,const size_t ind);
        size_t pop(double &length_value);
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