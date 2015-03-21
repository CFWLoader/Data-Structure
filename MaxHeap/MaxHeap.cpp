#include"MaxHeap.h"
#include<iostream>
#include<stack>
#include<cstdlib>
#include<ctime>

template<typename T>
int MaxHeap_Test_Driver(MaxHeap<T>&);

template<typename T>
int MaxHeap_Test_Driver_tmp(MaxHeap<T>&);

template<typename T>
MaxHeap<T>::MaxHeap():node_number(0),_root(0){}

template<typename T>
bool MaxHeap<T>::Delete_the_node(Node<T>* &node){
    if(!node)return true;
    if(node->lchild)Delete_the_node(node->lchild);
    if(node->rchild)Delete_the_node(node->rchild);
    delete node;
    node=0;
}

template<typename T>
MaxHeap<T>::~MaxHeap(){
    if(node_number>0){
        Delete_the_node(_root);
    }
    _root=0;
    node_number=0;
}

template<typename T>
int MaxHeap<T>::height(Node<T>*& node){
    if(!node)return 0;
    else{
        int lheight = height(node->lchild);
        int rheight = height(node->rchild);
        return 1+(lheight>rheight?lheight:rheight);
    }
}

template<typename T>
bool MaxHeap<T>::IsEmpty(){
    if(node_number<=0)return true;
    return false;
}

template<typename T>
bool MaxHeap<T>::IsFull(){
    return false;
}

/*
template<typename T>
bool MaxHeap<T>::Insert(const T& item){

    ++node_number;
    if(node_number==1){
        _root = new Node<T>();
        _root->item = item;
        return true;
    }

    //该处没有对利用树的性质进行插入，而是模拟数组的行为，找出数组的最后一位元素并插入该位置
    //利用数组的这个特性暂时解决插入时树倾斜的问题
    std::stack<int> pathrecord;
    int counter=2;
    //利用栈从数值逆向找出从目标节点到根节点的路径
    while(node_number/counter>1){
        pathrecord.push(node_number/counter);
        counter*=2;
    }
    Node<T>* iterator = _root;
    counter=2;
    //从根节点出发找到目标节点的位置
    while(!pathrecord.empty()){
        if(pathrecord.top()%counter==0)iterator=iterator->lchild;
        else iterator=iterator->rchild;
        pathrecord.pop();
        counter*=2;
    }
    if(node_number%counter==0){
        iterator->lchild=new Node<T>();
        iterator->lchild->parent=iterator;
        iterator=iterator->lchild;
    }
    else{
        iterator->rchild=new Node<T>();
        iterator->rchild->parent=iterator;
        iterator=iterator->rchild;
    }
    //至此，将数组的最后一个元素位置找到并初始化完成,iterator就是最后一位元素

    while(0);
}
*/

template<typename T>
bool MaxHeap<T>::Insert(const T& item){
    std::cout<<item<<" ";
    ++node_number;
    if(node_number==1){
        //std::cout<<"Situation 0."<<std::endl;
        _root = new Node<T>();
        _root->item = item;
        return true;
    }
    /*
    if(_root->item<=item){
        Node<T>* temp = new Node<T>();
        temp->item = item;
        temp->lchild = _root;
        _root = temp;
    }
    */
    Node<T>* insert_pos = _root;
    while((height(insert_pos->lchild)>0)&&(height(insert_pos->rchild)>0)&&(item<=(insert_pos->item))){
        if(height(insert_pos->lchild)>height(insert_pos->rchild)){
            //std::cout<<"Chose Right child.Item is minor? "<<(item<=(insert_pos->item))<<" "<<insert_pos->item<<std::endl;
            insert_pos=insert_pos->rchild;
        }
        else{
            //std::cout<<"Chose Left child.Item is minor? "<<(item<=(insert_pos->item))<<" "<<insert_pos->item<<std::endl;
            insert_pos=insert_pos->lchild;
        }
    }
    //if((height(insert_pos->lchild)>0)&&(height(insert_pos->rchild)>0)&&(item>(insert_pos->item))){
    Node<T>* newnode = new Node<T>();
    if(item>(insert_pos->item)){
        //std::cout<<"Situation 1."<<"Ready Node: "<<insert_pos->item<<std::endl;
        newnode->item = item;
        newnode->parent = insert_pos->parent;
        newnode->rchild = insert_pos->rchild;
        if(insert_pos->rchild)insert_pos->rchild->parent = newnode;
        //之前写的时候，上面一句一直没写，debug了两周一直没找出这个bug，父节点的指向子节点改变了，子节点的指向父节点也应随之改变。记得有值改变的时候，要全体变量的改变一致。
        //这个函数里面80%被注释的输出的信息的语句都是因为这个bug写的。
        newnode->lchild = insert_pos;
        //std::cout<<"Insert point Childs: L: "<<insert_pos->lchild<<" R: "<<insert_pos->rchild<<std::endl;
        insert_pos->rchild = 0;
        //std::cout<<"Item value: "<<newnode->item<<" Node Addr: "<<newnode<<" Lchild: "<<newnode->lchild<<" Rchild: "<<newnode->rchild<<std::endl;
        if(newnode->lchild == _root || newnode->rchild == _root){
            //newnode->lchild == _root?std::cout<<"Root updated,original changed to left child."<<std::endl:std::cout<<"Root updated,original changed to right child."<<std::endl;
            _root->parent = newnode;
            _root = newnode;
        }
        else{
            //insert_pos->parent->lchild==insert_pos?std::cout<<"Replace left child. "<<insert_pos->parent->lchild<<std::endl:std::cout<<"Replace right child. "<<insert_pos->parent->rchild<<std::endl;
            //std::cout<<"Insert point Childs: L: "<<insert_pos->lchild<<" R: "<<insert_pos->rchild<<std::endl;
            //std::cout<<"Newnode Childs: L: "<<newnode->lchild<<" R: "<<newnode->rchild<<std::endl;
            insert_pos->parent->lchild==insert_pos?insert_pos->parent->lchild=newnode:insert_pos->parent->rchild=newnode;
            //insert_pos->parent->lchild==newnode?std::cout<<"Replace left child. "<<insert_pos->parent->lchild<<std::endl:std::cout<<"Replace right child. "<<insert_pos->parent->rchild<<std::endl;
            //std::cout<<"Original: "<<insert_pos<<" Newnode: "<<newnode<<std::endl;
            insert_pos->parent = newnode;
        }

    }
    else{
        //std::cout<<"Situation 2."<<"Ready Node: "<<insert_pos->item<<std::endl;
        newnode->item = item;
        //height(insert_pos->lchild)>height(insert_pos->rchild)?std::cout<<"Insert to right child."<<std::endl:std::cout<<"Insert to left child."<<std::endl;
        height(insert_pos->lchild)>height(insert_pos->rchild)?insert_pos->rchild=newnode:insert_pos->lchild=newnode;
        //std::cout<<" Ins L R: "<<insert_pos->lchild<<" "<<insert_pos->rchild<<" Newnode addr: "<<newnode<<std::endl;
        newnode->parent = insert_pos;
    }
    newnode = 0;
    insert_pos = 0;
    //std::cout<<std::endl;
    return true;
}

template<typename T>
T MaxHeap<T>::Delete(){
    if(IsEmpty()){
        std::cout<<"The heap is empty."<<std::endl;
        throw std::string("The heap is empty.");
    }
    T item = _root->item;
    --node_number;
    if(node_number==0){
        delete _root;
        _root = 0;
        return item;
    }
       
    Node<T>* deprecated = _root;
    //Node<T>* iter = deprecated; 
    Node<T> tempnode;
    //bool lbtr_flag;                      //储存左子节点的键之值是否大于右子节点键值的变量
    Node<T>* lchild,*rchild,*parent;
    
    lchild = _root->lchild,rchild = _root->rchild;
    
    if(lchild&&rchild)_root=(lchild->item > rchild->item)?lchild:rchild;
    else if(lchild){
        _root = lchild;
        _root->parent = 0;
        goto rtim;
    }
    else{
        _root = rchild;
        _root->parent = 0;
        goto rtim;
    }
    
    parent = _root->parent;
    lchild = parent->lchild , rchild = parent->rchild;
    
    while(lchild || rchild){
        if(lchild && rchild){
            //std::cout<<"M1   ";
            if(lchild->item > rchild->item){
                //std::cout<<" Path: Left."<<std::endl;
                //std::cout<<" Original Parent info: "<<"Key: "<<parent->item<<" T: "<<parent<<" P: "<<parent->parent<<" L: "<<parent->lchild<<" R: "<<parent->rchild<<std::endl;
                tempnode = *lchild;
                if(parent->lchild == parent)parent->lchild = lchild;
                if(parent->rchild == parent)parent->rchild = lchild;
                //lchild->parent = parent;
                //parent->lchild = lchild,parent->rchild = rchild;
                lchild->parent = parent;
                parent = lchild;
                parent->lchild = lchild , parent->rchild = rchild;
                rchild->parent = parent;
                /*
                lchild->parent = parent->parent;
                parent = lchild;
                parent->rchild = rchild;
                rchild->parent = parent;
                parent->lchild = 0;
                 */             
                //std::cout<<" New Parent info: "<<"Key: "<<parent->item<<" T: "<<parent<<" P: "<<parent->parent<<" L: "<<parent->lchild<<" R: "<<parent->rchild<<std::endl;
                lchild = tempnode.lchild;
                rchild = tempnode.rchild;                
            }
            else{
                //std::cout<<" Path: Right."<<std::endl;
                //std::cout<<" Original Parent info: "<<"Key: "<<parent->item<<" T: "<<parent<<" P: "<<parent->parent<<" L: "<<parent->lchild<<" R: "<<parent->rchild<<std::endl;
                tempnode = *rchild;
                if(parent->lchild == parent)parent->lchild = rchild;
                if(parent->rchild == parent)parent->rchild = rchild;
                //rchild->parent = parent;
                rchild->parent = parent;
                //parent->lchild = lchild,parent->rchild = rchild;
                parent = rchild;
                parent->lchild = lchild , parent->rchild = rchild;
                lchild->parent = parent;
                //std::cout<<" New Parent info: "<<"Key: "<<parent->item<<" T: "<<parent<<" P: "<<parent->parent<<" L: "<<parent->lchild<<" R: "<<parent->rchild<<std::endl;
                lchild = tempnode.lchild;
                rchild = tempnode.rchild;
                tempnode;
            }
        }
        else if(lchild){            
            //std::cout<<"M2"<<std::endl;
            if(parent->lchild == parent)parent->lchild = lchild;
            if(parent->rchild == parent)parent->rchild = lchild;
            parent = lchild;
            lchild = parent->lchild;
            rchild = parent->rchild;
        }
        else if(rchild){
            //std::cout<<"M3"<<std::endl;
            if(parent->lchild == parent)parent->lchild = rchild;
            if(parent->rchild == parent)parent->rchild = rchild;
            parent = rchild;
            lchild = parent->lchild;
            rchild = parent->rchild;
        }
        else{
            parent->lchild = lchild;
            parent->rchild = rchild;
        }
    }
    
    if(parent->lchild == parent)parent->lchild = 0;
    if(parent->rchild == parent)parent->rchild = 0;
    //每个算法的开头初始化以及收尾步骤要做好，删除算法debug了两三天的原因就是没做上述两句，对结束算法的处理
    
    //if(lchild)parent->lchild = lchild;
    //else if(rchild)parent->rchild = rchild;
    /*
    if(lchild&&rchild)_root=(lchild->item > rchild->item)?lchild:rchild;
    else if(lchild){
        _root = lchild;
        goto rtim;
    }
    else{
        _root = rchild;
        goto rtim;
    }
    
    if(_root == lchild){
        lchild = Find_minor_position(lchild,rchild->item);
        if(!lchild->lchild){
            lchild->lchild = rchild;
            goto rtim;
        }
        if(!lchild->rchild){
            lchild ->rchild = rchild;
            goto rtim;
        }
    }
    else{
        rchild = Find_minor_position(rchild,lchild->item);
        if(!rchild->lchild){
            rchild->lchild = lchild;
            goto rtim;
        }
        if(!rchild->rchild){
            rchild->rchild = lchild;
            goto rtim;
        }
    }
    */
    /*
    while(lchild&&rchild){
        if(lchild->item > rchild->item){
            parent->lchild = lchild;
            lchild->parent = parent->parent;
            rchild->parent = lchild;
            tempnode = lchild->rchild;
            lchild->rchild = rchild;
            //rchild = lchild->rchild;
            rchild = tempnode;
            parent = lchild;
            lchild = parent->lchild;
        }
        else{
            parent->rchild = rchild;
            rchild->parent = parent->parent;
            lchild->parent = rchild;
            tempnode = rchild->lchild;
            rchild->lchild = lchild;
            lchild = tempnode;
            parent = rchild;
            rchild = parent->rchild;
        }
    }
    if(lchild)parent->lchild = lchild;
    else if(rchild)parent->rchild = rchild;
    */
    /*
    while(height(iter->lchild) && height(iter->rchild)){
        std::cout<<iter->lchild->item<<" "<<iter->rchild->item<<std::endl;
        if(iter->lchild->item > iter->rchild->item){
            iter->rchild->parent = iter->lchild;
            iter->lchild->parent = iter->parent;
            tempson = iter->rchild;
            iter = iter->lchild;
        }
        else{
            iter->lchild->parent = iter->rchild;
            iter->rchild->parent = iter->parent;
            tempson = iter->lchild;
            iter = iter->rchild;
        }
    }
    */
    //std::cout<<height(iter->lchild)<<" "<<height(iter->rchild)<<std::endl
    //std::cout<<iter<<std::endl;
rtim:    delete deprecated;
    //std::cout<<"Crashed."<<std::endl;
    deprecated = 0;
    _root->parent = 0;
    return item;
}


template<typename T>
void MaxHeap<T>::Preorder(){
    Preorder_executor(_root,1);
}


template<typename T>
void MaxHeap<T>::Preorder_executor(Node<T>* &node,int depth){
    if(!node)return;
    std::cout<<"Level: "<<depth<<" Value: "<<node->item<<" Node addr: "<<node<<" L: "<<node->lchild<<" R: "<<node->rchild<<std::endl;
    Preorder_executor(node->lchild,depth+1);
    Preorder_executor(node->rchild,depth+1);
}

template<typename T>
int MaxHeap<T>::Get_nodes_number(){
    std::cout<<"Nodes Number: "<<node_number<<"  Order's result: "<<Nodes_counter(_root)<<std::endl;
    return node_number;
}

template<typename T>
int MaxHeap<T>::Nodes_counter(Node<T>*& node){
    if(node){
        return 1+Nodes_counter(node->lchild)+Nodes_counter(node->rchild);
    }
    return 0;
}

template<typename T>
Node<T>* MaxHeap<T>::Find_minor_position(Node<T>* node, const T& reference){
    while(Nodes_counter(node)>1 && node->item > reference){
        if(node->lchild && node->rchild)node = (node->lchild->item <= node->rchild->item)?node->lchild:node->rchild;
        else if(!node->lchild) node = node->rchild;
        else node = node->lchild;
    }
    return node;
}


template<typename T>
int MaxHeap_Test_Driver(MaxHeap<T>& maxheap){
    int nodenumber;
    std::srand(std::time(0));
    nodenumber = std::rand()%32+1;
    int counter = 1;
    std::cout<<"Generating "<<nodenumber<<" numbers."<<std::endl;
    while(counter<=nodenumber){
        maxheap.Insert(std::rand()%128);
        ++counter;
    }
    std::cout<<std::endl;
    maxheap.Preorder();
    maxheap.Get_nodes_number();
    return 0;
}

template<typename T>
int MaxHeap_Test_Driver_tmp(MaxHeap<T>& maxheap){
    int nodenumber = 13;
    maxheap.Insert(108);
    maxheap.Insert(44);
    maxheap.Insert(57);
    maxheap.Insert(16);
    maxheap.Insert(89);
    maxheap.Insert(50);
    maxheap.Insert(18);
    maxheap.Insert(102);
    maxheap.Insert(115);
    maxheap.Insert(20);
    maxheap.Insert(120);
    maxheap.Insert(122);
    maxheap.Insert(27);
    maxheap.Preorder();
    maxheap.Get_nodes_number();
    return 0;
}

template<typename T>
int MaxHeap_Test_Driver_tmp2(MaxHeap<T>& maxheap){
    int nodenumber = 13;
    maxheap.Insert(124);
    maxheap.Insert(119);
    maxheap.Insert(113);
    maxheap.Insert(65);
    maxheap.Insert(42);
    maxheap.Insert(13);
    maxheap.Insert(56);
    maxheap.Insert(54);
    maxheap.Insert(117);
    maxheap.Insert(77);
    maxheap.Insert(6);
    maxheap.Insert(113);
    maxheap.Insert(53);
    maxheap.Preorder();
    maxheap.Get_nodes_number();
    return 0;
}
