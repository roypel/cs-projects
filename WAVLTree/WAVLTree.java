package WAVLTree;

/**
 *
 * WAVLTree
 *
 * An implementation of a WAVL Tree with distinct integer keys and info
 * 
 * @author Roy Peleg - ID 203218185 - username roypeleg
 * @author Ron David Cogan - ID 205671787 - username rondavidc
 * 
 * throughout the complexity analysis n will represent
 * the number of nodes in the current tree, unless otherwise stated
 * 
 */

public class WAVLTree {

	private WAVLNode ext; //used as sentinel
	private WAVLNode root;
	private WAVLNode minNode;
	private WAVLNode maxNode;

	/**
	 * initializing a new WAVL Tree
	 * post: root == sentinel
	 */
	
	public WAVLTree(){ 
		this.ext = new WAVLNode();
		this.root = ext;
		this.maxNode = ext;
		this.minNode = ext;
	}
	
	/**
	 * public boolean empty()
	 *
	 * returns true if and only if the tree is empty
	 * Complexity: O(1)
	 */
	public boolean empty() {
		return this.root == ext;
	}

	/**
	 * public String search(int k)
	 *
	 * returns the info of an item with key k if it exists in the tree
	 * otherwise, returns null
	 * 
	 * helper functions: - search (int key ,int add)
	 * 
	 * Complexity: O(log(n))
	 */
	public String search(int k) {
		WAVLNode currNode = search(k,0);
		if(currNode.key != k){ // key is not found
			return null; }
		return currNode.getValue();
		}
	
	
	/**
	 * public WAVLNode search(int k, int add)
	 *
	 * returns the WAVNode of an item with key k if it exists in the tree
	 * otherwise, returns his parent ( or ext if tree is empty )
	 * 
	 * param add is an indicator of which function uses it and change size as needed:
	 *  add = 0 --> search()
	 *      = 1 --> insert()
	 *      = -1 --> delete()
	 * 
	 * Complexity: O(log(n))
	 */
	
	public WAVLNode search(int k, int add) {
		WAVLNode currNode = this.root;
		WAVLNode parent = ext;
		while (currNode != ext && currNode.getKey() != k) {
			currNode.size += add;
			parent = currNode;
			if (currNode.getKey() > k) // key may be found on left Sub-Tree
				currNode = currNode.left;
			else // key may be found on right Sub-Tree
				currNode = currNode.right;
		}
		if(currNode == this.ext){ // key not found - returns parent for further use 
			return parent; }
		return currNode;
		}
	
	
	/**
	 * public int insert(int k, String i)
	 *
	 * inserts an item with key k and info i to the WAVL tree. the tree must
	 * remain valid (keep its invariants). returns the number of rebalancing
	 * operations, or 0 if no rebalancing operations were necessary. returns -1
	 * if an item with key k already exists in the tree.
	 * 
	 * helper functions: - search(int key ,int add)
	 * 					 - rebalance ()
	 * 
	 * Complexity: O(log(n))
	 */
	public int insert(int k, String i) {
		WAVLNode nodeToInsert = new WAVLNode(k,i);
		if(this.root == ext){ // inserting into an empty tree
			this.root = nodeToInsert;
			this.minNode = nodeToInsert;
			this.maxNode = nodeToInsert;
			return 0;
		}
		WAVLNode currNode = search(k, 1); // tree is not empty

		if (currNode.getKey() == k){ // node with key = k already exists
			search(k, -1);// Reverse size changes if key exists 
			return -1;
		}
		// node with key k doesn't exist, should be added as the child of currNode
		if (currNode.getKey() > k){  // nodeToInsert is the left child of his parent
			currNode.left = nodeToInsert;
			if ( k < minNode.getKey())
				this.minNode = nodeToInsert;}
		else{// nodeToInsert is the right child of his parent
			currNode.right = nodeToInsert;
			if ( k > this.maxNode.getKey())
				this.maxNode = nodeToInsert; }
		nodeToInsert.parent = currNode;
		return rebalance(currNode); // rebalance the tree as needed 
	}
	
	/**
	 * public int delete(int k)
	 *
	 * deletes an item with key k from the binary tree, if it is there; the tree
	 * must remain valid (keep its invariants). returns the number of
	 * rebalancing operations, or 0 if no rebalancing operations were needed.
	 * returns -1 if an item with key k was not found in the tree.
	 * 
	 * helper functions: - search(int key ,int add)
	 * 					 - rebalance ()
	 * 					 - switchLeft(nodeToDelete.left, parent)
	 * 					 - switchRight(nodeToDelete.right, parent)
	 * 
	 * Complexity: O(log(n))
	 */
	public int delete(int k) {
		if (this.root == ext) // trying to delete from an empty tree
			return -1;
		WAVLNode nodeToDelete = search(k, -1);
		if (nodeToDelete.key != k){// Node isn't in the tree, reverse the size changes
			search (k,1);
			return -1;
		}
		if (this.root.rank == 0){// Delete root and empty the tree
			this.root = ext;
			this.maxNode = ext;
			this.minNode = ext;
			return 0;
		}
		if ((nodeToDelete.right != ext) && (nodeToDelete.left != ext)){// Deleting a node with 2 childs,
			WAVLNode successor = nodeToDelete.right;						// change with successor
			while (successor.left != ext){
				successor.size--;
				successor = successor.left;
				}
			nodeToDelete.size--;
			nodeToDelete.key = successor.key;
			nodeToDelete.value = successor.value;
			if (successor == this.maxNode)
				this.maxNode = nodeToDelete;
			if (successor == this.minNode)
				this.minNode = nodeToDelete;
			nodeToDelete = successor;
			}
		WAVLNode parent = nodeToDelete.parent;
		if (parent == null){// Deleting a root with one child only
			WAVLNode son;
			if (nodeToDelete.left != ext)
				son = nodeToDelete.left;
			else
				son = nodeToDelete.right;
			this.root = son;// son becomes a root, already has size = 1 and rank = 0
			this.maxNode = son;
			this.minNode = son;
			son.parent = null;
			return 0;
		}
		if (nodeToDelete.rank == 0){// Deleting a leaf
			if (nodeToDelete == this.maxNode)// In a max leaf node, the new max is the parent
				this.maxNode = nodeToDelete.parent;
			if (nodeToDelete == this.minNode)// In a min leaf node, the new min is the praent
				this.minNode = nodeToDelete.parent;
			if (parent.right == nodeToDelete)
				parent.right = ext;
			else
				parent.left = ext;
			if (parent.size == 1){// Parent turns into a leaf
				demote(parent);
				if (parent.parent != null)
					return rebalance(parent.parent) + 1; // +1 for the demote
				return 1; // Parent is root, and is the only node in the tree + demote
			}
			return rebalance(parent); // If parent.rank == 1, nothing changes,
								// else case 3,1 or 3,2, or symmetrical cases
			}
		// Deleting an unary node - son is a leaf
		if (nodeToDelete == this.maxNode)// In a max unary node, the new max is the left child
			this.maxNode = nodeToDelete.left;
		if (nodeToDelete == this.minNode)// In a min unary node, the new min is the right child
			this.minNode = nodeToDelete.right;
		if (parent.left == nodeToDelete){ // deleting a left node
			if (nodeToDelete.left != ext){
				switchLeft(nodeToDelete.left, parent);
			}
			else{
				switchLeft(nodeToDelete.right, parent);
			}
		}
		else{ // deleting a right node
			if (nodeToDelete.left != ext){
				switchRight(nodeToDelete.left, parent);
			}
			else{
				switchRight(nodeToDelete.right, parent);
			}
		}
		return rebalance(parent);
	}
	
	/**
	 * private void rotateRight(WAVLNode son, WAVLNode parent)
	 * 
	 * rotates the sub tree of parent right, switching it with son (the left 
	 * child of parent). maintains the tree invariants of size and rank.
	 * 
	 * pre: son is the left child of parent
	 * 
	 * Complexity: O(1)
	 */
	
	private void rotateRight(WAVLNode son, WAVLNode parent ){
		if (this.root != parent){
			if (parent.getKey() < parent.parent.getKey())
				parent.parent.left = son;
			else
				parent.parent.right = son;
			}
		else
			this.root = son;
		parent.left = son.right;
		if (parent.left != ext)
			parent.left.parent = parent;
		son.right = parent;
		son.parent = parent.parent;
		parent.parent = son;
		parent.size = parent.left.size + parent.right.size + 1;
		son.size = son.left.size + son.right.size +1;
		if (parent.size == 1)
			parent.rank = 0;
	}

	/**
	 * private void rotateLeft(WAVLNode son, WAVLNode parent)
	 * 
	 * rotates the sub tree of parent left, switching it with son (the right 
	 * child of parent). maintains the tree invariants of size and rank.
	 * 
	 * pre: son is the right child of parent
	 * 
	 * Complexity: O(1)
	 */
	private void rotateLeft(WAVLNode son, WAVLNode parent ){
		if (this.root != parent){
			if (parent.getKey() < parent.parent.getKey())
				parent.parent.left = son;
			else
				parent.parent.right = son;
			}
		else
			this.root = son;
		parent.right = son.left;
		if (parent.right != ext)
			parent.right.parent = parent;
		son.left = parent;
		son.parent = parent.parent;
		parent.parent = son;
		parent.size = parent.left.size + parent.right.size + 1;
		son.size = son.left.size + son.right.size +1;
		if (parent.size == 1)
			parent.rank = 0;
	}
	
	/**
	 * private int rebalance(WAVLNode subTreeRoot)
	 * 
	 * performs rebalancing operations such as promote, demote and rotations
	 * as necessary, to return a WAVL tree after an insert or a delete operation
	 * to a valid WAVL tree. returns the number of operations as needed, every 
	 * operation costs 1 except double rotation which costs 2.
	 * 
	 * post: this.root is a valid WAVL tree with all it's invariants
	 * such as size and rank corrected.
	 * 
	 *  helper functions: - rankDiffLeft()
	 * 					  - rankDiffRight()
	 * 					  - promote()
	 * 					  - demote()
	 * 					  - rotateLeft()
	 * 					  - rotateRight()
	 * 
	 * Complexity: O(log(n))
	 */
	private int rebalance (WAVLNode subTreeRoot){
		int counter = 0; // counter for all rebalancing operations
		int leftDiff;
		int rightDiff;
		while (subTreeRoot != null){// Stop condition: root has passed the rebalancing operation
			leftDiff = rankDiffLeft(subTreeRoot);
			rightDiff = rankDiffRight(subTreeRoot);
			if ((leftDiff == 1 || leftDiff == 2) && (rightDiff == 1 || rightDiff == 2)) //Sub tree is balanced
				return counter;
			if (leftDiff == 0){
				if (rightDiff == 1){// case 0,1
					promote(subTreeRoot);
					counter++;
					subTreeRoot = subTreeRoot.parent;
				}
				else{// case 0,2
					if (rankDiffLeft(subTreeRoot.left) == 1){
						if(rankDiffRight(subTreeRoot.left) == 1){// left child is 1,1
							promote(subTreeRoot.left);
							rotateRight(subTreeRoot.left, subTreeRoot);
							return counter + 1;
						}
						demote(subTreeRoot);// left child is 1,2
						rotateRight(subTreeRoot.left, subTreeRoot);
						return counter + 1;
					}
					if(rankDiffRight(subTreeRoot.left) == 1){// left child is 2,1
						promote(subTreeRoot.left.right);
						demote(subTreeRoot.left);
						demote(subTreeRoot);
						rotateLeft(subTreeRoot.left.right, subTreeRoot.left);
						rotateRight(subTreeRoot.left, subTreeRoot);
						return counter + 2;
					}
					// left child is 2,2
					demote(subTreeRoot.left);
					return counter + 1;
				}
			}
				else{if (leftDiff == 1){
					if (rightDiff == 0){// case 1,0
						promote (subTreeRoot);
						counter++;
						subTreeRoot = subTreeRoot.parent;
					}
					else{// case 1,3
						if (rankDiffLeft(subTreeRoot.left) == 1){// left child is 1,1 or 1,2
								promote(subTreeRoot.left);
								demote(subTreeRoot);
								rotateRight(subTreeRoot.left, subTreeRoot);
								return counter + 1;
						}
						if (rankDiffRight(subTreeRoot.left) == 1){// left child is 2,1
							promote(subTreeRoot.left.right);
							promote(subTreeRoot.left.right);
							demote(subTreeRoot.left);
							demote(subTreeRoot);
							demote(subTreeRoot);
							rotateLeft(subTreeRoot.left.right, subTreeRoot.left);
							rotateRight(subTreeRoot.left, subTreeRoot);
							return counter + 2;
						}
						// left child is 2,2
						demote(subTreeRoot.left);
						demote(subTreeRoot);
						counter += 2;
						subTreeRoot = subTreeRoot.parent;
					}
				}
				else{if (leftDiff == 2){
					if (rightDiff == 0){// case 2,0
						if (rankDiffRight(subTreeRoot.right) == 1){
							if(rankDiffLeft(subTreeRoot.right) == 1){// right child is 1,1
								promote(subTreeRoot.right);
								rotateLeft(subTreeRoot.right, subTreeRoot);
								return counter + 1;
							}
							demote(subTreeRoot);// right child is 2,1
							rotateLeft(subTreeRoot.right, subTreeRoot);
							return counter + 1;
						}
						if(rankDiffLeft(subTreeRoot.right) == 1){// right child is 1,2
							promote(subTreeRoot.right.left);
							demote(subTreeRoot.right);
							demote(subTreeRoot);
							rotateRight(subTreeRoot.right.left, subTreeRoot.right);
							rotateLeft(subTreeRoot.right, subTreeRoot);
							return counter + 2;
						}
						// left child is 2,2
						demote(subTreeRoot.right);
						return counter + 1;
					}
					// case 2,3
					demote(subTreeRoot);
					counter++;
					subTreeRoot = subTreeRoot.parent;
					}
				else{if (leftDiff == 3){
					if (rightDiff == 1){// case 3,1
						if (rankDiffRight(subTreeRoot.right) == 1){// right child is 1,1 or 1,2
							promote(subTreeRoot.right);
							demote(subTreeRoot);
							rotateLeft(subTreeRoot.right, subTreeRoot);
							return counter + 1;
					}
					if (rankDiffLeft(subTreeRoot.right) == 1){// right child is 2,1
						promote(subTreeRoot.right.left);
						promote(subTreeRoot.right.left);
						demote(subTreeRoot.right);
						demote(subTreeRoot);
						demote(subTreeRoot);
						rotateRight(subTreeRoot.right.left, subTreeRoot.right);
						rotateLeft(subTreeRoot.right, subTreeRoot);
						return counter + 2;
					}
					// left child is 2,2
					demote(subTreeRoot.right);
					demote(subTreeRoot);
					counter += 2;
					subTreeRoot = subTreeRoot.parent;
					}
					else{// case 3,2
						demote(subTreeRoot);
						counter++;
						subTreeRoot = subTreeRoot.parent;
					}
					}
				}
				}
			}
		}
		return counter;
	}
	
	/**
	 * private void promote (WAVLNode node)
	 * 
	 * increase the rank of node by 1
	 * 
	 * Complexity: O(1)
	 */
	private void promote (WAVLNode node){
		node.rank++;
	}
	
	/**
	 * private void demote (WAVLNode node)
	 * 
	 * decrease the rank of node by 1
	 * 
	 * Complexity: O(1)
	 */
	private void demote (WAVLNode node){
		node.rank--;
	}
	
	/**
	 * private int rankDiffLeft (WAVLNode node)
	 * 
	 * returns the difference between node and his left child ranks
	 * 
	 * pre: node has a left child
	 * 
	 * Complexity: O(1)
	 */
	private int rankDiffLeft (WAVLNode node){
		return node.rank - node.left.rank;
	}

	/**
	 * private int rankDiffRight (WAVLNode node)
	 * 
	 * returns the difference between node and his right child ranks
	 * 
	 * pre: node has a right child
	 * 
	 * Complexity: O(1)
	 */
	private int rankDiffRight (WAVLNode node){
		return node.rank - node.right.rank;
	}
	
	/**
	 * private void switchLeft (WAVLNode son, WAVLNode parent)
	 * 
	 * links son as the left child of parent
	 * 
	 * pre: the node son is the child of the left child of the node parent
	 * 
	 * Complexity: O(1)
	 */
	private void switchLeft (WAVLNode son, WAVLNode parent){
		son.parent = parent;
		parent.left = son;
	}
	
	/**
	 * private void switchRight (WAVLNode son, WAVLNode parent)
	 * 
	 * links son as the right child of parent
	 * 
	 * pre: the node son is the child of the right child of the node parent
	 * 
	 * Complexity: O(1)
	 */	
	private void switchRight (WAVLNode son, WAVLNode parent){
		son.parent = parent;
		parent.right = son;
	}

	/**
	 * public String min()
	 *
	 * Returns the info of the item with the smallest key in the tree, or null
	 * if the tree is empty
	 * 
	 * Complexity: O(1)
	 */
	public String min() {
		if (this.empty())
			return null;
		return minNode.getValue();
	}

	/**
	 * public String max()
	 *
	 * Returns the info of the item with the largest key in the tree, or null if
	 * the tree is empty
	 * 
	 * Complexity: O(1)
	 */
	public String max() {
		if (this.empty())
			return null;
		return maxNode.getValue();
	}


	/**
	 * private WAVLNode successor(WAVLNode currNode)
	 * 
	 * Returns the node that has the next key in order in the tree.
	 * if there is no node with this condition (currNode == maxNode) return null.
	 * 
	 * helper functions: - minSubTree()
	 * 
	 * Complexity: O(log(n))
	 */
	private WAVLNode successor(WAVLNode currNode) {
		if(currNode == null)
			return null;
		if (currNode.right != ext)// Search for minimum node in right child sub-tree
			return minSubTree(currNode.right);
		WAVLNode parent = currNode.parent;
		while (parent != null && currNode == parent.right) {// successor is the first node that 
			currNode = parent;								// this sub-tree is his left child
			parent = currNode.parent;
		}
		return parent; // if there is no Successor (max node as input) return null
	}


	/**
	 * private WAVLNode minSubTree(WAVLNode subRoot)
	 * 
	 * Returns the node with the minimum key on the sub-tree of subRoot.
	 * 
	 * pre: subRoot != this.ext
	 * 
	 * Complexity: O(log(n))
	 */
	private WAVLNode minSubTree(WAVLNode subRoot) {
		while (subRoot.left != ext)
			subRoot = subRoot.left;
		return subRoot;
	}

	/**
	 * public int[] keysToArray()
	 *
	 * Returns a sorted array which contains all keys in the tree, or an empty
	 * array if the tree is empty.
	 * 
	 * helper functions: - successor()
	 * 
	 * Complexity: O(n)
	 */
	
	public int[] keysToArray() {
		int[] arr = new int[this.root.size];
		WAVLNode temp = this.minNode;
		for (int i = 0; i < this.root.size; i++) {
			arr[i] = temp.getKey();
			temp = successor(temp);
		}
		return arr;
	}

	/**
	 * public String[] infoToArray()
	 *
	 * Returns an array which contains all info in the tree, sorted by their
	 * respective keys, or an empty array if the tree is empty.
	 *
	 * helper functions: - successor()
	 * 
	 * Complexity: O(n)
	 */
	public String[] infoToArray() {
		WAVLNode currRoot = this.root;
		String[] arr = new String[currRoot.size];
		WAVLNode temp = this.minNode;
		for (int i = 0; i < currRoot.size; i++) {
			arr[i] = temp.getValue();
			temp = successor(temp);
		}
		return arr;
	}
		

	/**
	 * public int size()
	 *
	 * Returns the number of nodes in the tree.
	 *
	 * precondition: none postcondition: none
	 * 
	 * Complexity: O(1)
	 */
	public int size() {
		return root.size;
	}

	/**
	 * public int getRoot()
	 *
	 * Returns the root WAVL node, or null if the tree is empty
	 *
	 * precondition: none postcondition: none
	 * 
	 * Complexity: O(1)
	 */
	public IWAVLNode getRoot() {
		if (this.empty())
			return null;
		return root;
	}

	/**
	 * public int select(int i)
	 *
	 * Returns the value of the i'th smallest key (return -1 if tree is empty)
	 * Example 1: select(1) returns the value of the node with minimal key
	 * Example 2: select(size()) returns the value of the node with maximal key
	 * Example 3: select(2) returns the value 2nd smallest minimal node, i.e the
	 * value of the node minimal node's successor
	 *
	 * precondition: size() >= i > 0 postcondition: none
	 * 
	 * helper functions: - select(int i, WAVLNode currNode)
	 * 
	 * Complexity: O(log(n))
	 */
	public String select(int i) {
		if ((this.root.size < i) || (this.root == ext))
			return "-1";
		return select(i, this.root).getValue();
	}
	
	/**
	 * 
	 * Returns the value of the i'th smallest key in the sub tree of currNode.
	 * pre: i < currNode.size.
	 * 
	 * Complexity: O(log(n))
	 */
	private WAVLNode select(int i, WAVLNode currNode){
		int posInTree;
		posInTree = currNode.left.size + 1;// get the position in the tree (in an In-order scan)
		if (posInTree == i)// current position is the i'th element as needed
			return currNode;
		if (i < posInTree)// current position is bigger than i, search for i in left sub tree
			return select(i, currNode.left);
		return select(i - posInTree, currNode.right);// current position is smaller than i,
														//find (i-current position) in right subtree
	}

	/**
	 * public interface IWAVLNode ! Do not delete or modify this - otherwise all
	 * tests will fail !
	 */
	public interface IWAVLNode{	
		public int getKey(); //returns node's key (for virtual node return -1)
		public String getValue(); //returns node's value [info] (for virtual node return null)
		public IWAVLNode getLeft(); //returns left child (if there is no left child return null)
		public IWAVLNode getRight(); //returns right child (if there is no right child return null)
		public boolean isRealNode(); // Returns True if this is a non-virtual WAVL node (i.e not a virtual leaf or a sentinal)
		public int getSubtreeSize(); // Returns the number of real nodes in this node's subtree (Should be implemented in O(1))
	}

	/**
	 * public class WAVLNode
	 *
	 * If you wish to implement classes other than WAVLTree (for example
	 * WAVLNode), do it in this file, not in another file. This class can and
	 * must be modified. (It must implement IWAVLNode)
	 */
	public class WAVLNode implements IWAVLNode {

		public WAVLNode left;
		public WAVLNode right;
		public WAVLNode parent;
		public int rank;
		public int key;
		public String value;
		public int size;

		/**
		 * initializing a new real WAVLNode
		 */
		
		public WAVLNode(int key, String value) {
			this.key = key;
			this.value = value;
			this.size = 1;
			this.right = ext;
			this.left = ext;
			this.parent = null;
			this.rank = 0;
		}
		
		/**
		 * initializing a new external WAVLNode
		 * should run only once
		 */
		public WAVLNode(){
			this.size = 0;
			this.value = null;
			this.rank = -1;
			this.left = null;
			this.parent = null;
			this.right = null;
			this.key = -1;
		}

		
		public int getKey() {
			return this.key;
		}

		public String getValue() {
			return this.value;
		}

		public IWAVLNode getLeft() {
			if (this.left == ext)
				return null;
			return this.left;
		}

		public IWAVLNode getRight() {
			if (this.right == ext)
				return null;
			return this.right;
		}

		// Returns True if this is a non-virtual WAVL node (i.e not a virtual
		// leaf or a sentinel)
		public boolean isRealNode() {
			return this.rank != -1;
		}

		public int getSubtreeSize() {
			return size;
		}
		
		public int getRank(){
			return this.rank;
		}

	}
}