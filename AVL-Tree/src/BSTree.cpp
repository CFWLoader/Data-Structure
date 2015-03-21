#include "BSTree.h"
//#define DEBUG_MODE_POS0
//#define DEBUG_MODE_POS1

BSTree::BSTree() : root(0)
{
    //ctor
}

BSTree::~BSTree()
{
    //dtor
    delete root;
}

void BSTree::inorder(std::ostream& os) const{
    if(root != 0){
        inorder(os, root->GetleftChild());
        os << root->Getkey() << "  ";
        inorder(os, root->GetrightChild());
    }
    os << std::endl;
}

void BSTree::inorder(std::ostream& os, const TreeNode* ptr) const{
    if(ptr != 0){
        inorder(os, ptr->GetleftChild());
        os << ptr->Getkey() << "  ";
        inorder(os, ptr->GetrightChild());
    }
}


void BSTree::traceInorder(std::ostream& os) const{
    if(root != 0){
        traceInorder(os, root->GetleftChild(), 1);
        os << root->Getkey() << std::endl;
        traceInorder(os, root->GetrightChild(), 1);
    }
    os << std::endl;
}

void BSTree::traceInorder(std::ostream& os, const TreeNode* ptr, int indent) const{
    if(ptr != 0){
        int counter = 0;
        while(counter < indent){
            os << "- ";
            ++counter;
        }
        traceInorder(os, ptr->GetleftChild(), indent + 1);
        os << ptr->Getkey() << std::endl;
        traceInorder(os, ptr->GetrightChild(), indent + 1);
    }
}

void BSTree::insertToBSTree(int keyValue){
    if(root == 0){
        root = new TreeNode(keyValue);
        return;
    }
    TreeNode* ptr = root;
    TreeNode* nextPos = 0;
    while(ptr != 0){
        nextPos = (ptr->Getkey() > keyValue) ? ptr->GetleftChild() : ptr->GetrightChild();
        if(nextPos == 0)break;
        ptr = nextPos;
    }
    if(ptr->Getkey() > keyValue)ptr->SetleftChild(new TreeNode(keyValue));
    else ptr->SetrightChild(new TreeNode(keyValue));
}

TreeNode* BSTree::search(int value) const {
    if(root == 0) return 0;
    if(root->Getkey() == value)return root;
    TreeNode* ptr = root;
    TreeNode* nextPos = 0;
    while(ptr != 0){
        nextPos = (ptr->Getkey() > value) ? ptr->GetleftChild() : ptr->GetrightChild();
        if(nextPos == 0 || nextPos->Getkey() == value)break;
        ptr = nextPos;
    }
    return nextPos;
}

int BSTree::Depth() const{
    if(root != 0){
        int leftTreeDepth = Depth(root->GetleftChild());
        int rightTreeDepth = Depth(root->GetrightChild());
        return (1 + ((leftTreeDepth > rightTreeDepth)? leftTreeDepth : rightTreeDepth));
    }
    else return 0;
}

int BSTree::Depth(const TreeNode* ptr) const{
    if(ptr != 0){
        int leftTreeDepth = Depth(ptr->GetleftChild());
        int rightTreeDepth = Depth(ptr->GetrightChild());
        return (1 + ((leftTreeDepth > rightTreeDepth)? leftTreeDepth : rightTreeDepth));
    }
    else return 0;
}

void BSTree::avlInsert(int keyValue){
    if(root == 0){
        root = new TreeNode(keyValue);
    }
    else if(keyValue < root->Getkey()){
        bool unbalanceFlag = false;
        /*
        if(root->GetleftChild() == 0)root->SetleftChild(new TreeNode(keyValue));
        else avlInsert(root->GetleftChild(), keyValue, unbalanceFlag);
        */
        avlInsert(root->leftChild, keyValue, unbalanceFlag);
        int balance = Depth(root->GetleftChild()) - Depth(root->GetrightChild());
        if(balance < -1 || balance > 1)unbalanceFlag = true;
        if(unbalanceFlag){
#ifdef DEBUG_MODE_POS0
            std::cout << "Unbalance happened in left tree.Key valve: " << keyValue <<std::endl;
#endif // DEBUG_MODE_POS0
            if(balance <= -1)unbalanceFlag = false;
            else if(balance >= 1)leftRotation(root, unbalanceFlag);
        }
    }
    else if(keyValue > root->Getkey()){
        bool unbalanceFlag = false;
        /*
        if(root->GetrightChild() == 0)root->SetrightChild(new TreeNode(keyValue));
        else avlInsert(root->GetrightChild(), keyValue, unbalanceFlag);
        */
        avlInsert(root->rightChild, keyValue, unbalanceFlag);
        int balance = Depth(root->GetleftChild()) - Depth(root->GetrightChild());
        if(balance < -1 || balance > 1)unbalanceFlag = true;
        if(unbalanceFlag){
#ifdef DEBUG_MODE_POS0
            std::cout << "Unbalance happened in right tree.Key valve: " << keyValue <<std::endl;
#endif // DEBUG_MODE_POS0
            if(balance >= 1)unbalanceFlag = false;
            else if(balance <= -1)rightRotation(root, unbalanceFlag);
        }
    }
    else{
        std::cout << "Node exists." << std::endl;
    }
}

void BSTree::avlInsert(TreeNode* &ptr, int keyValue, bool& unbalanceFlag){
    if(ptr == 0){
        ptr = new TreeNode(keyValue);
    }
    else if(keyValue < ptr->Getkey()){
        /*
        if(ptr->GetleftChild() == 0)ptr->SetleftChild(new TreeNode(keyValue));
        else avlInsert(ptr->GetleftChild(), keyValue, unbalanceFlag);
        */
        avlInsert(ptr->leftChild, keyValue, unbalanceFlag);
        int balance = Depth(ptr->GetleftChild()) - Depth(ptr->GetrightChild());
        if(balance < -1 || balance > 1)unbalanceFlag = true;
        if(unbalanceFlag){
#ifdef DEBUG_MODE_POS0
            std::cout << "Unbalance happened in left tree.Key valve: " << keyValue <<std::endl;
#endif // DEBUG_MODE_POS0
            if(balance <= -1)unbalanceFlag = false;
            else if(balance >= 1)leftRotation(ptr, unbalanceFlag);
        }
    }
    else if(keyValue > ptr->Getkey()){
        /*
        if(ptr->GetrightChild() == 0)ptr->SetrightChild(new TreeNode(keyValue));
        else avlInsert(ptr->GetrightChild(), keyValue, unbalanceFlag);
        */
        avlInsert(ptr->rightChild, keyValue, unbalanceFlag);
        int balance = Depth(ptr->GetleftChild()) - Depth(ptr->GetrightChild());
        if(balance < -1 || balance > 1)unbalanceFlag = true;
        if(unbalanceFlag){
#ifdef DEBUG_MODE_POS0
            std::cout << "Unbalance happened in right tree.Key valve: " << keyValue <<std::endl;
#endif // DEBUG_MODE_POS0
            if(balance >= 1)unbalanceFlag = false;
            else if(balance <= -1)rightRotation(ptr, unbalanceFlag);
        }
    }
    else{
        std::cout << "Node exists." << std::endl;
    }
}

void BSTree::leftRotation(TreeNode* &ptr, bool& unbalanceFlag){
    TreeNode* grandChild, *child;
    child = ptr->GetleftChild();
    if((Depth(child->GetleftChild()) - Depth(child->GetrightChild())) == 1){
        ptr->SetleftChild(child->GetrightChild());
        child->SetrightChild(ptr);
        ptr = child;
    }
    else{
        grandChild = child->GetrightChild();
        child->SetrightChild(grandChild->GetleftChild());
        grandChild->SetleftChild(child);
        ptr->SetleftChild(grandChild->GetrightChild());
        grandChild->SetrightChild(ptr);
        ptr = grandChild;
    }
}

void BSTree::rightRotation(TreeNode* &ptr, bool& unbalanceFlag){
#ifdef DEBUG_MODE_POS1
        std::cout << "Use Right Rotation." << std::endl;
#endif // DEBUG_MODE_POS1
    TreeNode* grandChild, *child;
    child = ptr->GetrightChild();
    if((Depth(child->GetleftChild()) - Depth(child->GetrightChild())) == -1){
#ifdef DEBUG_MODE_POS1
        std::cout << "RR Rotation." << std::endl;
#endif // DEBUG_MODE_POS1
        ptr->SetrightChild(child->GetleftChild());
        child->SetleftChild(ptr);
        ptr = child;
    }
    else{
#ifdef DEBUG_MODE_POS1
        std::cout << "RL Rotation." << std::endl;
#endif // DEBUG_MODE_POS1
        grandChild = child->GetleftChild();
        child->SetleftChild(grandChild->GetrightChild());
        grandChild->SetrightChild(child);
        ptr->SetrightChild(grandChild->GetleftChild());
        grandChild->SetleftChild(ptr);
        ptr = grandChild;
    }
}
