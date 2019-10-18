checker:  
[https://practice.geeksforgeeks.org/problems/huffman-encoding/0]  
docs:  
[https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/]  

### Given:  
T - test cases  
L - letters
F - frequency for each letter

#### Complexity
Time Complexity: O(nlogn) using heap    

or 

for sorted by frequncy input
Time Complexity: O(nlogn) using 2 queue

  
##### Huffman encoding 

    O(nlogn):
    1. Take all input in heap by frequency
    2. while heap.size() != 1:
        a. m1 = heap.get(), m2 = heap.get()
        b. new_node = heap_item('$', m1.f + m2.f, m1, m2)
        c. heap.insert(new_node)
    3. in heap is stored root of huffman tree
       traverse tree in order and accumulate string by:
            if we go in left subtree push '0' in string
            if we go in right subtree push '1' in string
       if we met the leaf print accumulating string
       
       
    O(n):
    1. take 2 queue
    2. push all input in q1
    // we need first condition for first iteration case where we take 2 elements
    // from q1, merge them and push into q2
    3. while !q1.empty() and q2.size != 1:
        a. m1 = get_min(q1, q2), m2 = get_min(q1, q2)
        b. new_node = heap_item('$', m1.f + m2.f, m1, m2)
        c. q2.push(new_node)
    4. in q2 is stored root of huffman tree
       traverse tree in order and accumulate string by:
            if we go in left subtree push '0' in string
            if we go in right subtree push '1' in string
       if we met the leaf print accumulating string
    