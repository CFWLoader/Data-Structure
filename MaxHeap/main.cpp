//还是有一点bug，对应情况暂时不明，大多数情况下能正确运行得到结果
//堆调整算法的问题，性能不高

#include <iostream>
#include "MaxHeap.cpp"

using namespace std;

int main()
{
    MaxHeap<int> maxheap;
    MaxHeap_Test_Driver(maxheap);
    //MaxHeap_Test_Driver_tmp(maxheap);
    //MaxHeap_Test_Driver_tmp2(maxheap);
    while(!maxheap.IsEmpty()){
        cout<<maxheap.Delete()<<endl;
    }
    cout<<"Finished."<<endl;
    return 0;
}
