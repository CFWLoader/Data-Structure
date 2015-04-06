# Red Black Tree

Start challenge. -- 2015.03.27

You can read the the file `Theory-of-Red-Black-Tree.md` to know details.

### Note: The sentinel is important in RB-Tree.I tried not using it but failed.

## Implement list:
+ Node constructor and destructor.
+ Tree cascade deleter for tree destructor.
+ The Red Black insert and the insert fixer seem working correctly.
+ Constructed method : RedBlackTree::treeSuccessor(args),  RedBlackTree::redBlackDelete(args),  RedBlackTree::deleteFixer(args)
+ The deletion and delete fixed seem working correctly after fix of rotation but have a little bug.

## Problems
+ It will generate a weird node in deletion.
