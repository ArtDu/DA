Дано: N, W, C
##### С повторениями
    
    pass
    
##### Без повторении
    
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