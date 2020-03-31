#include <iostream>
#include "../inc/cxz_vector3.h"
using namespace cxz;
int main(int argc,char *argv[])
{
    std::string s1="face.obj";
    double p[3]={0,0,0};
    ObjStore mesh_obj;
    mesh_obj.read_obj(s1); 
    std::cout<<mesh_obj.calc_min_distance(p)<<std::endl;
    return 0;
}