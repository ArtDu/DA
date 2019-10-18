this code to solve the problem:  
[https://practice.geeksforgeeks.org/problems/longest-common-increasing-subsequence/0]  
docs:  
[https://www.geeksforgeeks.org/longest-common-increasing-subsequence-lcs-lis/]  

### Given:  
T - test cases  
a - size of fst subsequence 
b - size of snd subsequence
A - fst subsequence of nums
B - sn dsubsequence of nums  

#### Complexity
Time Complexity: O(n * m)  
Auxiliary Space: O(n)  
 
##### Longest Common Increasing Subsequence

    Iterative algo:
    
    for i to n:
        for j to m:
            if a1[i] == a2[j]:
                table[j] = max{a2[k]: where k < j and a2[k] < a2[j] 
                                        and Exist p: a1[p] == a2[k] and p < i } + 1
                
    we can achieve k, when we go on a2 array, because a2[j] == a1[i]
    then the final algo:
    for i to n:
        cur = 0 // LCIS in subsequence before a1[i]
                // x[1] < x[2] < ... x[cur] < a1[i] == a2[j]
        for j to m:
            if a1[i] == a2[j]:
                table[j] = cur + 1
                
            if a1[i] > a2[j] and table[j] > cur:
                cur = table[j]
                
    
    
    table[j] = length of LCIS ending with arr2[j]
    
                 
