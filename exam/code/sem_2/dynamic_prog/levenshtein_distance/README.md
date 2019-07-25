Дано:  
T - test cases  
l1, l2 - lengths of str1, str2  
s1, s2

##### Edit distance

    mem[ i of str1 ][ i of str2 ] = min operations transform str1[:i] to str2[:j]
    
    mem[0][j] = len2 // insert symbols
    mem[i][0] = len1 // delete symbols 
    
    mem[i][j] = mem[i - 1][j - 1]                          , s1[i] == s2[j]
    mem[i][j] = 1 + min( mem[i - 1][j]     // delete sym   , s1[i] != s2[j]
                         mem[i][j - 1]     // insert sym
                         mem[i - 1][j - 1] // replace sym
                   )                     
