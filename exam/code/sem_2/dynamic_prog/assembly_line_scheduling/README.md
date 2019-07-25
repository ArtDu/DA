Дано:  
begin1, begin2, end1, end2,  
S1, S2  - stations
T1 - transition from 1 line to 2 line with [station]  
T2

##### Конвейер

    f1[station] = min Operation
    f2[station] = min Operation


    start from 1:
    
    f1[ 1 ] = begin1 + S1[1]
    f2[ 1 ] = begin2 + S2[1]
    
    i = 2 ... n -1
    f1[ i ] = min(f1[i - 1] + S1[i],
                  f2[i - 1] + S1[i] + T2[i])
    f2[ i ] = min(f2[i - 1] + S2[i],
                  f1[i - 1] + S2[i] + T1[i])
    
    f1[ n ] = f1[n - 1] + end1
    f2[ n ] = f2[n - 1] + end2

    Восстановление ответа:
        l1[ s ] = which line from 1 or 2
        l2[ s ] = which line from 1 or 2
        l* = finish line

    

    