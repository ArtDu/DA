checker:  
[https://practice.geeksforgeeks.org/problems/edit-distance/0](https://practice.geeksforgeeks.org/problems/edit-distance/0)  
docs:  
[https://www.geeksforgeeks.org/edit-distance-dp-5/](https://www.geeksforgeeks.org/edit-distance-dp-5/)  

### Given:  
T - test cases  
l1, l2 - lengths of str1, str2  
s1, s2

#### Complexity
Time Complexity: O(l1 x l2)  
Auxiliary Space: O(l1 x l2)  
  
  
##### Edit distance
Levenshtein distance - minimum number of single-character edits (insertions, deletions or replace)

    mem[ i of str1 ][ i of str2 ] = min operations transform str1[:i] to str2[:j]
    
    Iterative algo:
    
    for i in range(l1):
        for j in range(l2):
    
            mem[0][j] = len2 , i == 0      // insert symbols 
            mem[i][0] = len1 , j == 0      // delete symbols 
            
            mem[i][j] = mem[i - 1][j - 1]                        , s1[i] == s2[j]
            mem[i][j] = 1 + min( mem[i - 1][j]      //Delete     , s1[i] != s2[j]
                                 mem[i][j - 1]      //Insert 
                                 mem[i - 1][j - 1]  //Replace 
                           )                     
