Дано:  
 S1, S2

##### LCS - longest common subsequence
    
    dp[i][j]
    
    Рекурентная формула:
        dp[i][j] = 0                   , i = 0 or j = 0
        dp[i][j] = dp[i - 1][j - 1] + 1, s1[i] == s2[j]
        dp[i][j] = max ( dp[i - 1][j],
                         dp[i][j - 1] ), s1[i] != s2[j]
  
    
    Восстановление:
        prev[i][j] = pair(i - 1, j - 1) or
                     pair(i - 1, j)     or
                     pair(i, j - 1)
                   
                     
        recovery(prev, i, j):
            if i == 0 or j == 0:
                return
             
            if prev[i][j] == pair (i - 1, j - 1):
                recovery(prev, i - 1, j - 1)
                print( s1[i] )
                
            elif prev[i][j] == pair (i - 1, j):
                recovery(prev, i - 1, j)
            else:
                recovery(prev, i, j - 1)