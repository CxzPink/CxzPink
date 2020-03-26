#include <cstddef>
#include <math.h>
#include "../inc/cxz_vector3.h"
using namespace cxz;

double cxz::compute_distance_triangle_point(const double (&triangle_coord)[9],const double (&point_coord)[3])
{
    MyVector3 p[4];
    MyVector3 vertical_line,point,temp_point;
    double h,min;

    for(size_t i=0;i<3;i++)
        p[0].coord[i]=point_coord[i];
    for(size_t i=1;i<4;i++)
        for(size_t j=0;j<3;j++)
            p[i].coord[j]=triangle_coord[(i-1)*3+j];
    
    if(area(p[1],p[2],p[3])>ZERO){
        vertical_line=unitize((p[1]-p[3])^(p[2]-p[3]));
        h=fabs(((p[1]-p[0])^(p[2]-p[0]))*(p[3]-p[0]))/(2*area(p[1],p[2],p[3]));
        temp_point=p[0]+h*vertical_line;
        point=p[0]-h*vertical_line;
        if(fabs(((p[1]-point)^(p[2]-point))*(p[3]-point))>ZERO)
            point=temp_point;
        //point in triangle
        if(fabs(area(point,p[1],p[2])+area(point,p[1],p[3])+area(point,p[2],p[3])-area(p[1],p[2],p[3]))<ZERO) 
            return h;
    }
// when triangle degeneration or point out of triangle  
    min=distance_edge_point(p[0],p[1],p[2]);
    if(min>distance_edge_point(p[0],p[1],p[3]))
        min=distance_edge_point(p[0],p[1],p[3]);
    if(min>distance_edge_point(p[0],p[2],p[3]))
        min=distance_edge_point(p[0],p[2],p[3]);
    return min;
}

double cxz::length(const MyVector3 &v)
{
    return pow(v.coord[0]*v.coord[0]+v.coord[1]*v.coord[1]+v.coord[2]*v.coord[2],0.5);
}

double cxz::area(const MyVector3 &p_0,const MyVector3 &p_1,const MyVector3 &p_2)
{
    return 0.5*length((p_1-p_0)^(p_2-p_0));
}

MyVector3 cxz::unitize(const MyVector3 &v)
{
    MyVector3 v1;
    double len=length(v);
    if(len==0)
        v1.coord[0]=v1.coord[1]=v1.coord[2]=0;
    else{
        v1.coord[0]=v1.coord[0]/len;
        v1.coord[1]=v1.coord[1]/len;
        v1.coord[2]=v1.coord[2]/len;
    }
    return v1;
}

double cxz::distance_edge_point(const MyVector3 &p_0,const MyVector3 &p_1,const MyVector3 &p_2)
{
    if(p_0==p_1 || p_0==p_2) //when point=edge point
        return 0;
    else if(p_1==p_2)           // when edge is a point
        return length(p_0-p_2);
    else if(((p_0-p_1)*(p_2-p_1))>=0){
        if(((p_0-p_2)*(p_1-p_2))>=0)   //when angle1 and angle2 <90
            return length((p_0-p_1)^(p_2-p_1))/length(p_2-p_1);
        else               //when angle2 >90
            return length(p_0-p_2);
    }
    else   //when angle1 >90
        return length(p_0-p_1);
}