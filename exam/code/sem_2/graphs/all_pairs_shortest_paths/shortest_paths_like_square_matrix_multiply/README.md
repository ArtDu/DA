### Given:  
G = (V, E)

n - size of matrix
W - matrix of adjacency (n x n - size)
where w(i)(j) = INF if (i,j) not in E
      w(i)(j) = Const if (i,j) in E
      w(i)(j) = 0
        
#### Complexity
Time Complexity: O(V^4)
Time Complexity: O(V^3 * logV)

  
##### Proble Shortest Paths like matrix multiplication problem

The structure of a shortest path:  
1. For the all-pairs shortest-paths that all subpaths of a shortest path are shortest paths.
2. Consider a shortest path p from vertex i to vertex j , and suppose that p contains at most m edges
      p'
3. i -> k -> j
4. p' contains at most m - 1 edges
5. => b(i,j) = b(i,k) + w(k)(j)
    
extend_shortest_paths(L, W):

    n = len(L)
    l = [[0] * n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            l[i][j] = sys.maxsize
            for k in range(n):
                l[i][j] = min(l[i][j], L[i][k] + W[k][j])
     
slow_all_pairs_shortest_paths(W):
    
    n = len(W)
    L_last = W
    print(L_last)
    for m in range(1, n - 1):
        L_last = extend_shortest_paths(L_last, W)
        print(L_last)
        
fast_all_pairs_shortest_paths(W):

L(1) = L(0) * W = W
L(2) = L(1) * W = W^2
L(3) = L(2) * W = W^3
L(4) = L(3) * W = W^4
...
L(n - 1) = L(n - 2) * W = W^(n - 1)

b(i, j) = lij ^ (n-1) = lij ^ (n) = lij ^ (n + 1) = ...

L(1) = W
L(2) = W * W = W^2
L(3) = W^2 * W^2 = W^4
L(4) = W^4 * W^4 = W^8
...
L(2(log(n - 1))) = W^2(log(n - 1)) = W^(2(log(n - 1)) - 1) * W^(2(log(n - 1)) - 1)