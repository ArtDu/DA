##### Правую часть режем, левую оставляем

    Рекурентная формула:  
        dp[size] = 0                            , size == 0  
        dp[size] = i=1...n max(p[i] + dp[n - i]), size != 0

    mem = [-1] * (n+1)
    def dp(p, mem, n)
        if mem[n] == -1:
            if n == 0:  
                q = 0
       
            else n > 0:
                q = -1
                for i = 1 ... n:
                    q = max(q, p[i] + dp(p, mem, n - i))  
         
        mem[n] = q  
        return q


    Восстановление ответа:
        s[size] = i which was choosen cut
        while n > 0:
            print ( s[n] )
            n = n - s[n]

    

    