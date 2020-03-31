#include"../inc/cxz_vector3.h"
using namespace std;
int cxz::ObjStore::read_obj(const std::string &s)
{
    string s, line;
	Point *v;
	Triangle *m;

	cout << "Input file location  .obj" << endl;
	cin >> s;
	ifstream file(s);

	if (!file) {
		cout << "No such file" << endl;
		return -1;
	}
	while (getline(file, line))
	{
		if (line[0] == 'v') {
			istringstream in(line);
			v = new Point();
			string head;
			in >> head >> v->x >> v->y >> v->z;
			V.push_back(*v);
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