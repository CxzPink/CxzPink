#include<../inc/cxz.h>
#include<iostream>
cxz::Heap::Heap()
{
    number=0;
    length.clear();
    length.push_back(0);
    index.clear();
    index.push_back(0);
}

int cxz::Heap::push(const double len,const size_t ind)
{
    number++;
    length.push_back(len);
    index.push_back(ind);

    size_t insert,front;
    insert=number;
    while(insert!=1){
        front=insert/2;
        if(length[insert]>length[front]){
            length[insert]=length[front];
            index[insert]=index[front];
            length[front]=len;
            index[front]=ind;
            insert=front;
        }
        else
            break;
    }
}

size_t cxz::Heap::pop(double &length_value)
{
    if(number==0){
        std::cout<<"empty heap"<<std::endl;
        exit(1);
    }

    index[0]=index[1];
    length[0]=length[1];
    length[1]=length[number];
    index[1]=index[number];
    length.pop_back();
    index.pop_back();
    number--;

    size_t remove,behind,max;
    size_t temp_s=index[1];
    double temp_d=length[1];
    remove=1;
    while(2*remove<=number){
        behind=remove*2;
        if((behind+1)<=number && length[behind]<length[behind+1])
            max=behind+1;
        else
            max=behind;
        if(length[max]>length[remove]){
            length[remove]=length[max];
            index[remove]=index[max];
            length[max]=temp_d;
            index[max]=temp_s;
            remove=max;
        }
        else
            break;
    }
    
    length_value=length[0];
    return index[0];
}