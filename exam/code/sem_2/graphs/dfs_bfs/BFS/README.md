checker:  
[https://practice.geeksforgeeks.org/problems/bfs-traversal-of-graph/1]
docs:  
[https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/]

### Given:  
T - test cases  
N - count of vertices  
E - count of edges  
(<u1, v1>, ..., <uE, vE>) - Adjacency list of edges   

#### Complexity
Time Complexity: O(V + E)
V for initialization
E for traverse all edges    

  
##### BFS

    1. take queue
    2. visited = [false] * V // V for initialization
    3. q.push(start vertex), visited[start vertex] = true
    4. while !q.empty():
        a. u = q.pop()
        b. for v in AdjacencyList[u]: // E for traverse
            if !visited[v]:
                visited[v] = true
                q.push(v)
     
    