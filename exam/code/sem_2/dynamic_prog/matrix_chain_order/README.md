Дано:  
 P - размеры матриц

##### Matrix chain order
    
    dp[i][j]
    
    Выбираем k и считаем внутри и перемножаем результат.
    
    Рекурентная формула:
        dp[i][j] = 0                                     , i == j 
        dp[i][j] =   min ( dp[i][k] + dp[k+1][j]
                                + P[i-1] * P[k] * P[j] ) , i < j
                  i <= k < j
  
    
    Восстановление:
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
            