#include <iostream>
#include "../inc/cxz_vector3.h"
using namespace cxz;
int main(int argc,char *argv[])
{
    std::string s1="face.obj";
    std::string s2="face2.obj";
    ObjStore mesh_obj;
    mesh_obj.read_obj(s1);
    mesh_obj.write_obj(s2);
    return 0;
}