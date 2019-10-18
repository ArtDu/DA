this code to solve the problem:  
[https://practice.geeksforgeeks.org/problems/longest-increasing-subsequence/0]  
docs:  
[https://www.geeksforgeeks.org/longest-increasing-subsequence-dp-3/]  

### Given:  
T - test cases  
S - subsequence of nums  

#### Complexity
Time Complexity: O(n ^ 2)  
Auxiliary Space: O(n)  
 
##### Longest Increasing Subsequence


    d[index] = max size of increasing subsequence with last element of S[index]
    
    d[i] = max{ d[j] : where S[j] < S[i] } + 1
               j < i 
    
    maximum = 0
    for i in range(len(S)):
        d[i] = 1
        for j in range(i):
            if S[j] < S[i] and d[j] + 1 > d[i]:
                d[i] = d[j] + 1
                if d[i] > maximum:
                    maximum = d[i]
    return maximum              
