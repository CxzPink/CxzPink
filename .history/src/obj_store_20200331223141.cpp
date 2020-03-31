#include <fstream>
#include <iostream>
#include <sstream>
#include"../inc/cxz_vector3.h"
int cxz::ObjStore::read_obj(const std::string &s)
{
    std::string line;
	MyVector3 *vec;
    Edge *edge;
	Triangle *m;
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
            
		}
		else if (line[0] == 'f') {
			istringstream in(line);
			m = new Triangle();
			string head;
			in >> head >> m->f[0] >> m->f[1] >> m->f[2];
			m->f[0] = m->f[0] - 1;
			m->f[1] = m->f[1] - 1;
			m->f[2] = m->f[2] - 1;
			F.push_back(*m);
		}
	}
	return 0;
}