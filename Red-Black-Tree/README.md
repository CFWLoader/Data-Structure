# Red Black Tree

Start challenge. -- 2015.03.27

You can read the the file `Theory-of-Red-Black-Tree.md` to know details.

## Implement list:
+ Node constructor and destructor.
+ Tree cascade deleter for tree destructor.
+ The Red Black insert and the insert fixer seem working correctly.
+ Constructed method : RedBlackTree::treeSuccessor(args),  RedBlackTree::redBlackDelete(args),  RedBlackTree::deleteFixer(args)

## Fixed problems
+ The insert fixer works incorrectly though it can modify children of a node correctly.Insert fixer can't modify parent of a node correctly.
+ Reason: The rotation codes lacks right logical codes.(Fixed code is line 124 and 140 in RedBlackTree.cpp)

## Events and problems
+ It's to busy to debug this program, maybe the process will proceed slower.
