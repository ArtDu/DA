docs:  
[https://www.geeksforgeeks.org/activity-selection-problem-greedy-algo-1/]  
this code to solve problem:  
[https://practice.geeksforgeeks.org/problems/n-meetings-in-one-room/0]  


##### Activity selection problem (Задача о процессах)

#### Complexity
dynamic:   
Time Complexity: O(n^2)  

greedy:
Time Complexity: O(n * logN)

#### Given:  
T - nums of test cases  
n - count of nums  
S - start nums  
F - finish nums  


    Динамическое программирование:
    
        Like Longest Increasing Subsequence 
    
        L[i] = stores maximus of non-conflicting jobs ending at i'th job
        L[i] = {jobs[i]} Union { max(L[j].size()) where j < i and
                            jobs[j].end < jobs[i].start }
             // = jobs[i], if there is no such j
        
        example:
        
        input:
        
        {1, 4}, {3, 5}, {0, 6}, {5, 7}, {3, 8}, {5, 9},
        {6, 10}, {8, 11}, {8, 12}, {2, 13}, {12, 14}
        output:
        
        {1, 4}, {5, 7}, {8, 11}, {12, 14}
        
        L[0]:  {1, 4}
        L[1]:  {3, 5}
        L[2]:  {0, 6}
        L[3]:  {1, 4} {5, 7}
        L[4]:  {3, 8}
        L[5]:  {1, 4} {5, 9}
        L[6]:  {1, 4} {6, 10}
        L[7]:  {1, 4} {5, 7} {8, 11}
        L[8]:  {1, 4} {5, 7} {8, 12}
        L[9]:  {2, 13}
        L[10]: {1, 4} {5, 7} {8, 11} {12, 14}
            
        
        code:
         
        for (int i = 0; i < jobs.size(); i++)
        {
            // consider each j less than i
            for (int j = 0; j < i; j++)
            {
                // L[i] = max(L[j]) where jobs[j].finish is less than jobs[i].start
                if (jobs[j].finish < jobs[i].start &&
                    L[i].size() < L[j].size())
                {
                    L[i] = L[j];
                }
            }
    
            // L[i] ends at i'th job
            L[i].push_back(jobs[i]);
        } 

    
    Жадный выбор: выбираем первый процесс am в отсортированных по времени окончания,
     у которого время начала меньше времени окончания Sk
    
    k = 0
    Sk = {ak}
    for m = 1 to n - 1:
        if s[m] > f[k]:
            Sk = Sk.append(am)
            k = m
    
    

    