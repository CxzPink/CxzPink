#include <iostream>
#include "../inc/cxz_vector3.h"
using namespace cxz;
int main(int argc,char *argv[])
{
    double triangle[9]={0.5,0.5,0,0,0,1,1,1,1};
    double point[3]={1,0,3};
    std::cout<<compute_distance_triangle_point(triangle,point)<<std::endl;

    return 0;
}