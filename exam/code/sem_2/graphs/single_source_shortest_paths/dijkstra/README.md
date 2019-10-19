docs:
https://www.geeksforgeeks.org/dijkstras-algorithm-for-adjacency-list-representation-greedy-algo-8/
problem:
https://practice.geeksforgeeks.org/problems/shortest-path-from-1-to-n/0

#### Complexity
Time Complexity: O(V^2) = O((V * V) + E) 
If we use linear array for find min in dist array.
For each V we find minimum in dist list by linear search = V * V.
Cause we look each edge = E.

Time complexity: O(E * logV)
If we binary heap
E - we look each edge in graph and execute decrease_key
LogV - decrease_key operation in binary heap

Time complexity: O(V * logV)
If we use fibonacci heap

  
##### Dijkstra

    1. take queue
    2. visited = [false] * V // V for initialization
    3. q.push(start vertex), visited[start vertex] = true
    4. while !q.empty():
        a. u = q.pop()
        b. for v in AdjacencyList[u]: // E for traverse
            if !visited[v]:
                visited[v] = true
                q.push(v)
     
    