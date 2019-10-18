checker:  
[https://practice.geeksforgeeks.org/problems/depth-first-traversal-for-a-graph/1]
docs:  
[https://www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph/]

### Given:  
T - test cases  
N - count of vertices  
E - count of edges  
(<u1, v1>, ..., <uE, vE>) - Adjacency list of edges   

#### Complexity
Time Complexity: O(V + E)
V for initialization
E for traverse all edges    

  
##### DFS

    1. visited = [False] * V // V for initialization
    2. dfs(visited, adjList, start vertex)
    
    
    dfs(visited, adjList, u):
        visited[u] = True
        for v in adjList[u]:
            if not visited[v]:
                dfs(visited, adjList, v)
     
    