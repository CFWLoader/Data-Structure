# This file is the specification of red black tree(RB-Tree).

### Traits of RB-Tree
1. Every nodes in the RB-Tree is red or black.
1. The root node is black.
1. Leaf nodes(Null Node) are black.
1. Both left child node and right child node is black if the parent is red.
1. The number of black node is equals in the path from specific node to its son and grandson nodes.

PS: 
The `<<Introduce of algorithm>>` suggests that we should use a special node
(Its color is black and other values of it are arbitrary.) to replace Null(Nil)
nodes(Leaf nodes).But I set the the leaf node value is NULL and it works.
The "special node" will render my algorithm to infinite recursion(unknown bug).

