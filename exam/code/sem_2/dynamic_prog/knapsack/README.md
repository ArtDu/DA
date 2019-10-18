### 0-1 knapsack problem

#### Complexity
Time Complexity: O(N x W)  
Auxiliary Space: O(N x W)  

#### Given:  
N - nums of items,  
W - weight of knapsack,  
{(v,w)} - array of (value, weight) pairs
    
    Берем и уменьшаем вес или не берем
    dp(i, w)
    
    Iterrative:
    dp(i, w) = 0 , i == 0 or w == 0
    dp(i, w) = max(dp(i - 1, w), dp(i - 1, w - w[i - 1]) + vi) 
                                                , w - w[i - 1] >= 0
    dp(i, w) = dp(i - 1, w)                     , else
    
    
    Рекурентная формула:
        dp(i, w) = 0                          , i == 0 or w == 0 
        dp(i, w) = max( dp(i - 1, w),
                        dp(i - 1, w - wi) + vi) 
                                              , i != 0 and w != 0 and w - wi > 0
        dp(i, w) = dp(i - 1, w)               , else
    
    Восстановление:
        ничего дополнительного для восстановление не нужно
    
        recovery(mem, w, N, W):
            if mem [N][W] == 0:
                return
             
            if mem [N][W] == mem[N - 1][W]:
                recovery(mem, w, N - 1, W)
                
            else:
                recovery(mem, w, N - 1, W - wi)
                print( N )