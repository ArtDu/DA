##### Задача о процессах

Дано:  
T - nums of test cases
n - count of nums
S - start nums
F - finish nums


    Динамическое программирование:
        L[i] = stores maximus of non-conflicting jobs ending at i'th job
        L[i] = jobs[i] + { max(L[j]) where j < i and jobs[j].end < jobs[i].start }
             = jobs[i], if there is no such j
        
        example:
        
        input:
        
        {1, 4}, {3, 5}, {0, 6}, {5, 7}, {3, 8}, {5, 9},
        {6, 10}, {8, 11}, {8, 12}, {2, 13}, {12, 14}
        output:
        
        {1, 4}, {5, 7}, {8, 11}, {12, 14}
        
        L[0]: {0, 6}
        L[1]: {1, 4}
        L[2]: {2, 13}
        L[3]: {3, 5}
        L[4]: {3, 8}
        L[5]: {1, 4} {5, 7}
        L[6]: {1, 4} {5, 9}
        L[7]: {1, 4} {6, 10}
        L[8]: {1, 4} {5, 7} {8, 11}
        L[9]: {1, 4} {5, 7} {8, 12}
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
    
    

    