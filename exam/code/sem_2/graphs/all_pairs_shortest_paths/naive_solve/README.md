|V| execute single-source shortest-paths algorithm for each v

If all edge weights are nonnegative we can use Djkstra algo:  
1. If we use the linear-array = O(V * V^2)
2. Binary min-heap = O(V * E * logV)
3. Fibonacci heap = O(V * V * logV)

If the graph has negative-weight edges we can use Bellman-Ford algo:
1. O(V * V * E)