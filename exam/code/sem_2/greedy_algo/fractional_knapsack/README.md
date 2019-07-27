### fractional knapsack problem

Дано: N, W, C

    sort weight-val-cost by cost(unit cost) = val/weight
    and take maximum by unit cost
    
    if W - curW >= 0:
        W -= i.weight
        ans += i.value
    else:
        ans += W * i.cost
        break



### 0-1 knapsack problem

Дано: N, W, C

##### unbound 0-1 knapsack problem
    
    dp[i] = 0
    dp[i] = max(dp[i], dp[i-wt[j]] + val[j] 
                       where j varies from 0 
                       to n-1 such that:
                       wt[j] <= i
    
    result = d[W]
    
##### normal 0-1 knapsack problem
    
    Берем и уменьшаем вес или не берем
    dp(i, w)
    
    dp(0, w) = 0
    dp(i, w) = 0
    dp(i, w) = max(dp(i - 1, w), dp(i - 1, w - wi) + pi)
    
    
    Рекурентная формула:
        dp(i, w) = 0                            , i = 0 or w = 0 
        dp(i, w) = max( dp(i - 1, w),
                        dp(i - 1, w - wi) + pi) , i != 0 and w != 0
    
    Восстановление:
        ничего дополнительного для восстановление не нужно
    
        recovery(mem, w, c, N, W):
            if mem [N][W] == 0:
                return
             
            if mem [N][W] == mem[N - 1][W]:
                recovery(mem, w, c, N - 1, W)
                
            else:
                recovery(mem, w, c, N - 1, W - wi)
                print( N )