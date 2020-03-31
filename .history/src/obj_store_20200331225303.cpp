#include <fstream>
#include <iostream>
#include <sstream>
#include"../inc/cxz_vector3.h"
int cxz::ObjStore::read_obj(const std::string &s)
{
    std::string line;
	MyVector3 *vec=NULL;
	Triangle *tri=NULL;
	std::ifstream file(s);

	if (!file) {
		std::cout << "No such file" << std::endl;
		return 1;
	}

	while (getline(file, line))
	{
		if (line[0] == 'v') {
			std::istringstream in(line);
			vec = new MyVector3();
			char temp;
			in >> temp >> vec->coord[0] >> vec->coord[1] >> vec->coord[2];
			point.push_back(*vec);
            delete vec;
		}
		else if (line[0] == 'f') {
			std::istringstream in(line);
			tri = new Triangle();
			char temp;
			in >> temp >> tri->point_index[0] >> tri->point_index[1] >> tri->point_index[2];
			tri->point_index[0] = tri->point_index[0] - 1;
			tri->point_index[1] = tri->point_index[1] - 1;
			tri->point_index[2] = tri->point_index[2]- 1;
			triangle.push_back(*tri);
		}
	}
    std::cout<<"successful read obj"<<std::endl;

	return 0;
}

int cxz::ObjStore::index_of_edge(const Edge &one_edge)
{
    Edge temp=one_edge;
    if(temp.point_index[1]<temp.point_index[0]){
        size_t tem=temp.point_index[1];
        temp.point_index[1]=temp.point_index[0];
        temp.point_index[0]=tem;
    }
    for(size_t i=0;i<edge_number;i++){
        if(temp.point_index[0]==edge[i].point_index[0] && temp.point_index[1]==edge[i].point_index[1])
            return i;
    }
}

void cxz::ObjStore::update_edge_index()
{
    Edge *edg=NULL;
    for(auto i:triangle){
        
    }
}