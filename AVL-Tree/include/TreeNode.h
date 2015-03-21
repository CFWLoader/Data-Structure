#ifndef TREENODE_H
#define TREENODE_H

//Note: destructor use self-delete,so we must use new to dynamic allocate TreeNode.
class TreeNode
{
    public:
        TreeNode();
        TreeNode(int);
        virtual ~TreeNode();
        int Getkey() const { return key; }
        void Setkey(int val) { key = val; }
        TreeNode* GetleftChild() const { return leftChild; }
        void SetleftChild(TreeNode* val) { leftChild = val; }
        TreeNode* GetrightChild() const { return rightChild; }
        void SetrightChild(TreeNode* val) { rightChild = val; }

        friend class BSTree;
    protected:
    private:
        int key;
        TreeNode* leftChild;
        TreeNode* rightChild;
};

#endif // TREENODE_H
