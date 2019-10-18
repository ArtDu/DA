#include <iostream>
#include <vector>

using namespace std;

/*
test nums from https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/

3 50
60 10
100 20
120 30

 */


long long
knapsack(vector<vector<long long>> &mem, vector<long long> &massOfItems,
         vector<long long> &priceOfItems,
         long long numberOfItems, long long massOfKnapSack) {

    // ran out of items
    if (numberOfItems == 0) {
        mem[numberOfItems][massOfKnapSack] = 0;
        return 0;
    }

    // already counted
    if (mem[numberOfItems][massOfKnapSack] >= 0) {
        return mem[numberOfItems][massOfKnapSack];
    }

    long long fst;
    long long snd;

    // take an item in knapsack
    if (massOfKnapSack - massOfItems[numberOfItems] >= 0) {

        fst = knapsack(mem, massOfItems, priceOfItems, numberOfItems - 1,
                       massOfKnapSack - massOfItems[numberOfItems])
              + priceOfItems[numberOfItems];

    } else // we can't take this item
        fst = 0;

    // don't take
    snd = knapsack(mem, massOfItems, priceOfItems, numberOfItems - 1, massOfKnapSack);

    mem[numberOfItems][massOfKnapSack] = max(fst, snd);

    return mem[numberOfItems][massOfKnapSack];

}

void recovery(vector<vector<long long>> &mem, vector<long long> &massOfItems,
              vector<long long> &priceOfItems,
              long long numberOfItems, long long massOfKnapSack) {

    if (mem[numberOfItems][massOfKnapSack] == 0) {
        return;
    }

    // didn't take
    if (mem[numberOfItems - 1][massOfKnapSack] == mem[numberOfItems][massOfKnapSack])
        recovery(mem, massOfItems, priceOfItems, numberOfItems - 1, massOfKnapSack);
        // take item
    else {
        recovery(mem, massOfItems, priceOfItems, numberOfItems - 1, massOfKnapSack - massOfItems[numberOfItems]);
        cout << numberOfItems << " ";
    }
}

void
knapsack(vector<long long> &massOfItems, vector<long long> &priceOfItems, long long numberOfItems,
         long long massOfKnapSack) {

    vector<vector<long long>> mem(numberOfItems + 1, vector<long long>(massOfKnapSack + 1, -1));

    knapsack(mem, massOfItems, priceOfItems, numberOfItems, massOfKnapSack);

    cout << mem[numberOfItems][massOfKnapSack] << "\n";
    recovery(mem, massOfItems, priceOfItems, numberOfItems, massOfKnapSack);
    cout << "\n";

}


int main() {

    long long numberOfItems, massOfKnapSack;
    cin >> numberOfItems >> massOfKnapSack;

    vector<long long> massOfItems(numberOfItems + 1);
    vector<long long> priceOfItems(numberOfItems + 1);

    for (int i = 1; i <= numberOfItems; ++i) {
        cin >> priceOfItems[i];
        cin >> massOfItems[i];
    }

    knapsack(massOfItems, priceOfItems, numberOfItems, massOfKnapSack);

    return 0;


}