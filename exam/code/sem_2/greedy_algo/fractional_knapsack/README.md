### fractional knapsack problem

checker:  
[https://practice.geeksforgeeks.org/problems/fractional-knapsack/0](https://practice.geeksforgeeks.org/problems/fractional-knapsack/0)  
docs:  
[https://www.geeksforgeeks.org/fractional-knapsack-problem/](https://www.geeksforgeeks.org/fractional-knapsack-problem/)  

#### Complexity
Time Complexity: O(N * LogN)    

#### Given: 
N - nums of items,  
W - weight of knapsack,  
{(v,w)} - array of (value, weight) pairs

    sort weight-val-cost by cost(unit cost) = val/weight
    and take maximum by unit cost
    
    items.sort(reverse=True)
    
    ans = 0
    for i in items:
        if W - i.w >= 0:
            W -= i.w
            ans += i.val
        else:
            ans += W * i.cost
            break
    return ans

