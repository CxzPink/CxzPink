#include <iostream>
#include "../inc/cxz.h"
using namespace cxz;
int main(int argc,char *argv[])
{
    std::string s1=argv[1];
    std::string s2=argv[2];
    Mesh mesh_obj;
    mesh_obj.read_obj(s1);    
    mesh_obj.cut_edge(10);
    mesh_obj.write_obj(s2);
    return 0;
}