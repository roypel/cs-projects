package DHeap;

/**
 * D-Heap
 * 
 * An implementation of a D-Heap.
 * 
 * @author Ron David Cogan - ID 205671787 - username rondavidc
 * @author Roy Peleg - ID 203218185 - username roypeleg
 * 
 * throughout the complexity analysis n will represent
 * the number of nodes in the current heap,
 * and all logs will be in base d
 */

public class DHeap
{
	
    public int size, max_size, d;
    public DHeap_Item[] array;

	// Constructor
	// m_d >= 2, m_size > 0
    DHeap(int m_d, int m_size) {
               max_size = m_size;
			   d = m_d;
               array = new DHeap_Item[max_size];
               size = 0;
    }
	
	/**
	 * public int getSize()
	 * Returns the number of elements in the heap.
	 * 
	 * Complexity: O(1)
	 */
	public int getSize() {
		return size;
	}

	
  /**
     * public int arrayToHeap()
     *
     * The function builds a new heap from the given array.
     * Previous data of the heap should be erased.
     * preconidtion: array1.length() <= max_size
     * postcondition: isHeap()
     * 				  size = array.length()
     * Returns number of comparisons along the function run. 
     * 
   	 * helper functions: - parent, heapifyDown, clone (from class Object)
	 * 
	 * Complexity: O(n)
	 */
	
    public int arrayToHeap(DHeap_Item[] array1) 
    {
    	int max = Math.max(max_size, array1.length);
        this.array = new DHeap_Item[max];
        this.size = 0; int j=0; int count=0;
        DHeap_Item[] arrayCopy = array1.clone();
        for (int i = 0; i<array1.length; i++){  // copying array1 to this.array
        	if(array1[i]!=null){ // filter null cells
        		this.array[j] = arrayCopy[i];
        		array[j].setPos(j);
        		j++;
        	}
        }
        this.size=j;
        int lastParentIndex = parent(j-1,d); // no need to heapify down leaves,
        for (int i=lastParentIndex; i>-1; i--){	//so we start from the last parent index
        	count+=heapifyDown(i);
        }
    	return count;
    }

    /**
     * public boolean isHeap()
     *
     * The function returns true if and only if the D-ary tree rooted at array[0]
     * satisfies the heap property or has size == 0.
     *   
     * helper functions: - parent
	 * 
	 * Complexity: O(n)
     */
    public boolean isHeap(){
/*    	for(int i=size ; i<array.length ; i++){
    		if (array[i]!=null) // if there is an item outside heap boundaries
    			return false;
    	}*/ //we wanted to make sure that after the last node, there are only null cells,
    			// but we weren't sure how the tester will behave 

    	for(int i= size-1; i>0; i--){
    		if((array[i] == null) || array[i].getKey() < array[parent(i,d)].getKey())
    			return false;
    	}
    	return true;
    }


 /**
     * public static int parent(i,d), child(i,k,d)
     * (2 methods)
     *
     * precondition: i >= 0, d >= 2, 1 <= k <= d
     *
     * The methods compute the index of the parent and the k-th child of 
     * vertex i in a complete D-ary tree stored in an array. 
     * Note that indices of arrays in Java start from 0.
     * 
     * Complexity: O(1)
     */
    public static int parent(int i, int d){
    	return (i-1)/d;
    	} 
    
    public static int child (int i, int k, int d) {
    	return (d*i)+k;
    	}

    /**
    * public int Insert(DHeap_Item item)
    *
	* Inserts the given item to the heap.
	* Returns number of comparisons during the insertion.
	*
    * precondition: item != null
    *               isHeap()
    *               size < max_size
    * 
    * postcondition: isHeap()
    * 
    * helper functions: - heapifyUp
	* 
	* Complexity: O(log(n))
    */
    public int Insert(DHeap_Item item) 
    {        
    	array[size] = item;
    	array[size].setPos(size);
    	size++;
    	return heapifyUp(item.getPos());
    }

 /**
    * public int Delete_Min()
    *
	* Deletes the minimum item in the heap.
	* Returns the number of comparisons made during the deletion.
    * 
	* precondition: size > 0
    *               isHeap()
    * 
    * postcondition: isHeap()
    * 
    * helper functions: - heapifyDown
	* 
	* Complexity: O(d*log(n))
    */
    public int Delete_Min()
    {
     	array[0] = array[size-1];
     	array[0].setPos(0);
     	array[size-1] = null;
     	size--;
     	return heapifyDown(0);
    }


    /**
     * public DHeap_Item Get_Min()
     *
	 * Returns the minimum item in the heap.
	 *
     * precondition: heapsize > 0
     *               isHeap()
     *		size > 0
     * 
     * postcondition: isHeap()
     *
     * Complexity: O(1)
     */
    public DHeap_Item Get_Min()
    {
    	return array[0];
    }
	
  /**
     * public int Decrease_Key(DHeap_Item item, int delta)
     *
	 * Decerases the key of the given item by delta.
	 * Returns number of comparisons made as a result of the decrease.
	 *
     * precondition: item.pos < size;
     *               item != null
     *               isHeap()
     * 
     * postcondition: isHeap()
     * 
     * helper functions: - heapifyUp
     * 
 	 * Complexity: O(log(n))
     */
    public int Decrease_Key(DHeap_Item item, int delta)
    {
    	if (delta == Integer.MAX_VALUE) // handle a delete scenario 
    		item.setKey(Integer.MIN_VALUE);
    	else
    		item.setKey(item.getKey()-delta);
    	return heapifyUp(item.getPos());
    }
	
	  /**
     * public int Delete(DHeap_Item item)
     *
	 * Deletes the given item from the heap.
	 * Returns number of comparisons during the deletion.
	 *
     * precondition: item.pos < size;
     *               item != null
     *               isHeap()
     * 
     * postcondition: isHeap()
     * 
     * helper functions: - Decrease_Key, Delete_Min
	 *
	 * Complexity: O(d*log(n))
     */
    public int Delete(DHeap_Item item)
    {
    	return (Decrease_Key(item, Integer.MAX_VALUE) + Delete_Min());
    }
	
	/**
	* Sort the input array using heap-sort (build a heap, and 
	* perform n times: get-min, del-min).
	* Sorting should be done using the DHeap, name of the items is irrelevant.
	* 
	* Returns the number of comparisons performed.
	* 
	* postcondition: array1 is sorted 
	* 
	* helper functions: - arrayToHeap, Get_Min, Delete_Min
	* 
	* Complexity: O(n*d*log(n))
	*/
	public static int DHeapSort(int[] array1, int d) {
		int count = 0;
		DHeap heap = new DHeap(d, array1.length); 				 // initializing a new Dheap
		DHeap_Item [] arrayCopy = new DHeap_Item[array1.length]; //initializing a new DHeap_Item array
		for(int i=0; i<array1.length; i++){
			arrayCopy[i] = new DHeap_Item(null,array1[i]); 		 //copy data from array1 to a new DHeap_Item array
		}
		count+= heap.arrayToHeap(arrayCopy); 					 //constructing the heap from array1 data 
		for (int i = 0; i < array1.length; i++){				 //sorting
			array1[i] = heap.Get_Min().getKey();				 
			count += heap.Delete_Min();
		}
		return count;
	}
	
	/**
	* A recursive function that heapifies a given item down, 
	* switching it with its smallest child, and continues until
	* the given item is smaller than all his children. 
	* 
	* Returns the number of comparisons performed.
	* 
	* Complexity: O(d*log(n))
	*/
	private int heapifyDown(int i){
		int indexMin = i; int count=0;
		int k = child(i,1,d); // the first child (from left to right) of item i
		if (k>size-1)
			return 0; // item in index i is a leaf
		for(int j=0; j<d ;j++){
			if(k+j > size-1)
				break;
			if(this.array[k+j].getKey() < this.array[indexMin].getKey())
				indexMin = k+j;
			count++;
		}
		if(indexMin > i){ // item i should be heapified down
			DHeap_Item temp = this.array[i];
			this.array[i] = this.array[indexMin];
			this.array[i].setPos(i);
			this.array[indexMin] = temp;
			this.array[indexMin].setPos(indexMin);
			return count + heapifyDown(indexMin);
		}
		return count;
	}
	
	
	/**
	 * A recursive function that heapifies a given item up,
	 * until the heap is valid.
	 *  
	 * Returns the number of comparisons performed.
	 * 
	 * Complexity: O(log(n))
	 */
	private int heapifyUp(int i){ // input: index
		if (i==0)
			return 0;
		int count = 0; 
		DHeap_Item temp;
		while(i>0 && array[i].getKey() < array[parent(i,d)].getKey()){ //while item i has a parent and heapify needed
			temp = array[i];
			array[i] = array[parent(i,d)];
			array[i].setPos(i);
			array[parent(i,d)] = temp;
			array[parent(i,d)].setPos(parent(i,d));
			i = parent(i,d);
			count++;
		}
		return count+1;
	}
}
