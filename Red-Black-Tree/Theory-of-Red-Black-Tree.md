# This file is the specification of red black tree(RB-Tree).

### Traits of RB-Tree
1. Every nodes in the RB-Tree is red or black.
1. The root node is black.
1. Leaf nodes(Null Node) are black.
1. Both left child node and right child node is black when the parent is red.
1. The number of black node is equals in the path from specific node to its son and grandson nodes.

PS: 
The `<<Introduce of algorithm>>` suggests that we should use a special node
(Its color is black and other values of it are arbitrary.) to replace Null(Nil)
nodes(Leaf nodes).But I set the the leaf node value is NULL and it works.
The "special node" will render my algorithm to infinite recursion(unknown bug).


## Case discussion
### Which traits of RB-Tree will be broken in insertion.
1. First we should know trait 1 and 3 won't be broken.
1. Trait 5 won't be broken because the inserted node is red.
1. Trait 2 or 4 may be broken and no more than one trait will be broken.

### Cases happens in insertion
(The total number of cases is 6,but we discuss 3 cases because left situations are symmetrical with rights.)

1. The inserted node's uncle is red.
* Solution: Paints its father and uncle red and its grandpa black.
Set its grandpa as current node and turn to next iteration. 

1. Current node's uncle is black and it is right child of its parent.
* Solution: Because the case 2 is not mutual with case 3,we set current node's parent the next iterative node and do a left rotation.
 Then the next operation is in case 3.
 
1. Current node's uncle is black and it is left child of its parent.
* Solution: After the operation of case 2,the broken trait must be 4. We paint current node's parent black and its grandpa red and
 do a right rotation to fix it.
 
### Analysis of insertion
1. After the occurrences of case 2,3,5 or 6, the iteration end because no nodes break the traits.
1. According to the analysis above, it will happen no more than twice rotations in insertion.

### Which traits of RB-Tree will be broken in deletion.
