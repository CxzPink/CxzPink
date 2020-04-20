#include <fstream>
#include <iostream>
#include <sstream>
#include <cfloat>
#include"../inc/cxz.h"
double cxz::compute_distance_triangle_point(const double (&triangle_coord)[9],const double (&point_coord)[3]);
using namespace cxz;
int cxz::Mesh::read_obj(const std::string &s)
{
    std::string line;
	MyVector3 *vec=NULL;
	Triangle *tri=NULL;
	std::ifstream file(s);

	if (!file) {
		std::cout << "---No such file---" << std::endl;
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
    point_number=point.size();
    triangle_number=triangle.size();
    update_edge_index();
    std::cout<<"--- successful read obj from "<<s<<" ---"<<std::endl;

	return 0;
}

int cxz::Mesh::write_obj(const std::string &s)
{
	std::ofstream file(s);
    for(auto i:point)
        file<<"v "<<i.coord[0]<<" "<<i.coord[1]<<" "<<i.coord[2]<<std::endl;
	for (auto i : triangle)
		file << "f " << (i.point_index[0]+1) << " " << (i.point_index[1]+1)  <<" "<< (i.point_index[2]+1)<< std::endl;
	file.close();
    std::cout<<"--- successful write the obj to "<<s<<" ---"<<std::endl;
	return 0;
}

double cxz::Mesh::calc_min_distance(const double (&p)[3])
{
    double min_distance=DBL_MAX;
    double temp_distance=0;
    double triangle_coord[9];
    for(auto i:triangle){
        for(size_t j=0;j<3;j++){
            triangle_coord[3*j]=point[i.point_index[j]].coord[0];
            triangle_coord[3*j+1]=point[i.point_index[j]].coord[1];
            triangle_coord[3*j+2]=point[i.point_index[j]].coord[2];
        }
        temp_distance=compute_distance_triangle_point(triangle_coord,p);
        if(temp_distance<min_distance)
            min_distance=temp_distance;
    }
    if(min_distance<ZERO)
        return 0;
    else
        return min_distance;
}

void cxz::Mesh::cut_edge(const double &max_length)
{
    Heap heap;
    double length_value;
    size_t my_edge_index;
    for(size_t  i=0;i<edge_number;i++){
        heap.push(length(point[edge[i].point_index[0]]-point[edge[i].point_index[1]]),i);
    }
    my_edge_index=heap.pop(length_value);
    while(length_value>max_length){
        if(binary_edge(my_edge_index)){
            heap.push(length(point[edge[my_edge_index].point_index[0]]-point[edge[my_edge_index].point_index[1]]),my_edge_index);
            heap.push(length(point[edge[edge_number-3].point_index[0]]-point[edge[edge_number-3].point_index[1]]),edge_number-3);
            heap.push(length(point[edge[edge_number-2].point_index[0]]-point[edge[edge_number-2].point_index[1]]),edge_number-2);
            heap.push(length(point[edge[edge_number-1].point_index[0]]-point[edge[edge_number-1].point_index[1]]),edge_number-1); 
        }
        else{
            heap.push(length(point[edge[my_edge_index].point_index[0]]-point[edge[my_edge_index].point_index[1]]),my_edge_index);
            heap.push(length(point[edge[edge_number-2].point_index[0]]-point[edge[edge_number-2].point_index[1]]),edge_number-2);
            heap.push(length(point[edge[edge_number-1].point_index[0]]-point[edge[edge_number-1].point_index[1]]),edge_number-1);            
        }
        my_edge_index=heap.pop(length_value);
    }
}

int cxz::Mesh::search_index_of_edge(const size_t &p_index1,const size_t &p_index2)
{
    size_t temp_index[2];
    if(p_index1<p_index2){
        temp_index[0]=p_index1;
        temp_index[1]=p_index2;        
    }
    else{
        temp_index[0]=p_index2;
        temp_index[1]=p_index1;     
    }
    for(size_t i=0;i<edge_number;i++)
        if(temp_index[0]==edge[i].point_index[0] && temp_index[1]==edge[i].point_index[1])
            return i;
    return -1;
}

void cxz::Mesh::update_edge_index()
{
    Edge *edg=NULL;
    edge_number=0;
    int temp_index;
    for(size_t k=0;k<triangle_number;k++){
        for(size_t i=0;i<3;i++){
            if((temp_index=search_index_of_edge(triangle[k].point_index[i%3],triangle[k].point_index[(i+1)%3]))!=-1){
                edge[temp_index].triangle_index[1]=k;
                triangle[k].edge_index[i]=temp_index;
            }
            else{
                edg=new Edge(triangle[k].point_index[i%3],triangle[k].point_index[(i+1)%3],k);
                edge.push_back(*edg);
                delete edg;
                triangle[k].edge_index[i]=edge_number;
                edge_number++;                
            }
        }
    }
}

cxz::Edge::Edge(const size_t &i,const size_t &j,const size_t &k)
{
    if(i>j){
        point_index[0]=j;
        point_index[1]=i;
    }
    else{
        point_index[0]=i;
        point_index[1]=j;
    }
    triangle_index[0]=k;
    triangle_index[1]=k;
}

int cxz::Mesh::binary_edge(const size_t &my_edge_index)
{
    MyVector3 new_point=point[edge[my_edge_index].point_index[0]]+point[edge[my_edge_index].point_index[1]];
    new_point.coord[0]=new_point.coord[0]*0.5;
    new_point.coord[1]=new_point.coord[1]*0.5;
    new_point.coord[2]=new_point.coord[2]*0.5;
    point.push_back(new_point);
    point_number++;

    Edge temp_edge=edge[my_edge_index];
    size_t p_index[4],e_index[4];
    size_t temp_index1,temp_index2;
    bool flag=(get_edge_around_infor(my_edge_index,p_index,e_index));
//edge0
    edge[my_edge_index].point_index[1]=point_number-1;
//edge1
    if(flag==1){
        Edge new_edge_1(temp_edge.point_index[1],point_number-1,0);
        new_edge_1.triangle_index[0]=triangle_number;
        new_edge_1.triangle_index[1]=triangle_number+1;
        edge.push_back(new_edge_1);
        edge_number++;
    }
    else{
        Edge new_edge_1(temp_edge.point_index[1],point_number-1,0);
        new_edge_1.triangle_index[0]=triangle_number;
        new_edge_1.triangle_index[1]=triangle_number;
        edge.push_back(new_edge_1);
        edge_number++;        
    }
//edge2
    Edge new_edge_2(p_index[2],point_number-1,0);
    new_edge_2.triangle_index[0]=temp_edge.triangle_index[0];
    new_edge_2.triangle_index[1]=triangle_number;
    edge.push_back(new_edge_2);
    edge_number++;
//edge3   
    if(flag==1){
        Edge new_edge_3(p_index[3],point_number-1,0);
        new_edge_3.triangle_index[0]=temp_edge.triangle_index[1];
        new_edge_3.triangle_index[1]=triangle_number+1;
        edge.push_back(new_edge_3);
        edge_number++;
    }
//triangle0
    for(auto i=0;i<3;i++){
        if(triangle[edge[my_edge_index].triangle_index[0]].point_index[i]==p_index[1]){
            triangle[edge[my_edge_index].triangle_index[0]].point_index[i]=point_number-1;
        }
    }
    for(auto i=0;i<3;i++){
        if(edge[triangle[edge[my_edge_index].triangle_index[0]].edge_index[i]].point_index[0]!=p_index[0]
        && edge[triangle[edge[my_edge_index].triangle_index[0]].edge_index[i]].point_index[1]!=p_index[0]){
            temp_index1=triangle[edge[my_edge_index].triangle_index[0]].edge_index[i];
            if(flag==1)
                triangle[edge[my_edge_index].triangle_index[0]].edge_index[i]=edge_number-2;
            else
                triangle[edge[my_edge_index].triangle_index[0]].edge_index[i]=edge_number-1;
            break;  
        }          
    }
//triangle1
    if(flag==1){
        for(auto i=0;i<3;i++){
            if(triangle[edge[my_edge_index].triangle_index[1]].point_index[i]==p_index[1]){
                triangle[edge[my_edge_index].triangle_index[1]].point_index[i]=point_number-1;
            }
        }
        for(auto i=0;i<3;i++){
            if(edge[triangle[edge[my_edge_index].triangle_index[1]].edge_index[i]].point_index[0]!=p_index[0]
            && edge[triangle[edge[my_edge_index].triangle_index[1]].edge_index[i]].point_index[1]!=p_index[0]){
                temp_index2=triangle[edge[my_edge_index].triangle_index[1]].edge_index[i];
                triangle[edge[my_edge_index].triangle_index[1]].edge_index[i]=edge_number-1; 
                break;
            }           
        }
    }
//triangle2
    Triangle new_triangle;
    new_triangle.point_index[0]=p_index[1];
    new_triangle.point_index[1]=p_index[2];
    new_triangle.point_index[2]=point_number-1;
    new_triangle.edge_index[0]=temp_index1;
    if(flag==1)
        new_triangle.edge_index[1]=edge_number-3;
    else
        new_triangle.edge_index[1]=edge_number-1;    
    new_triangle.edge_index[2]=edge_number-2;
    triangle.push_back(new_triangle);
    triangle_number++;
//triangle3
    if(flag==1){
        Triangle new_triangle;
        new_triangle.point_index[0]=p_index[1];
        new_triangle.point_index[1]=p_index[3];
        new_triangle.point_index[2]=point_number-1;
        new_triangle.edge_index[0]=temp_index2;
        new_triangle.edge_index[1]=edge_number-3;
        new_triangle.edge_index[2]=edge_number-1;
        triangle.push_back(new_triangle);
        triangle_number++;
    }
//edge5
    if(flag==1){
        for(auto i=0;i<2;i++){
            if(edge[temp_index1].triangle_index[i]==edge[my_edge_index].triangle_index[0])
                edge[temp_index1].triangle_index[i]=triangle_number-2;
        }
    }
    else{
        for(auto i=0;i<2;i++){
            if(edge[temp_index1].triangle_index[i]==edge[my_edge_index].triangle_index[0])
                edge[temp_index1].triangle_index[i]=triangle_number-1;
        }        
    }
//edge6
    if(flag==1){
        for(auto i=0;i<2;i++){
            if(edge[temp_index2].triangle_index[i]==edge[my_edge_index].triangle_index[1])
                edge[temp_index2].triangle_index[i]=triangle_number-1;
        }        
    }
    return flag;    
}

int cxz::Mesh::get_edge_around_infor(const size_t &my_edge_index,size_t (&p_index)[4],size_t (&e_index)[4])
{
    p_index[0]=edge[my_edge_index].point_index[0];
    p_index[1]=edge[my_edge_index].point_index[1];
    for(auto i=0;i<3;i++){
        if(triangle[edge[my_edge_index].triangle_index[0]].point_index[i]!=p_index[0]
        && triangle[edge[my_edge_index].triangle_index[0]].point_index[i]!=p_index[1])
            p_index[2]=triangle[edge[my_edge_index].triangle_index[0]].point_index[i];
    }
    for(auto i=0;i<3;i++){
        if(triangle[edge[my_edge_index].triangle_index[1]].point_index[i]!=p_index[0]
        && triangle[edge[my_edge_index].triangle_index[1]].point_index[i]!=p_index[1])
            p_index[3]=triangle[edge[my_edge_index].triangle_index[1]].point_index[i];
    }
    size_t count=0;
    for(auto i=0;i<3;i++){
        if(triangle[edge[my_edge_index].triangle_index[0]].edge_index[i]!=my_edge_index){
            e_index[count]=triangle[edge[my_edge_index].triangle_index[0]].edge_index[i];
            count++;
        }
    }
    for(auto i=0;i<3;i++){
        if(triangle[edge[my_edge_index].triangle_index[1]].edge_index[i]!=my_edge_index){
            e_index[count]=triangle[edge[my_edge_index].triangle_index[1]].edge_index[i];
            count++;
        }
    }
    if(edge[my_edge_index].triangle_index[0]==edge[my_edge_index].triangle_index[1])
        return 0;
    else
        return 1;
} 