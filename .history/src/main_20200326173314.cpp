#include <iostream>
#include "../inc/cxz_vector3.h"
using namespace cxz;
int main(int argc,char *argv[])
{
    double triangle[9]={0,0,0,1,0,0,0,1,0};
    double point[3]={0.5,0.5,1};
    std::cout<<compute_distance_triangle_point(triangle,point)<<std::endl;

    return 0;
}