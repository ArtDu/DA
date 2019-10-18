from CLRS(Introduction to algorithms)

### Given:  
 P - size of matrix

#### Complexity
Time Complexity: O(n^3)  
Auxiliary Space: O(n^2)


##### Matrix chain order
    
    dp[i][j]
    
    Выбираем k и считаем внутри и перемножаем результат.
    
    Recurrence (Рекурентная формула):
        dp[i][j] =   0                                 , i == j 
        dp[i][j] =   min { dp[i][k] + dp[k+1][j]       , i < j
                           + P[i-1] * P[k] * P[j] } 
                  i <= k < j
  
    
    Recovery:
        s[i][j] = k
                   
        recovery(s, l, r):
            if(l == r) {
                cout << " A " <<l << " ";
            }
            else {
                cout << "(";
                print_solution(s, l, s[l][r]);
                print_solution(s, s[l][r]+1, r);
                cout << ")";
            }
            