#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
test nums

3 6
2 1
5 4
4 2

 */


long long
knapsack(vector<vector<long long>> &mem, vector<long long> &massOfItems, vector<long long> &priceOfItems,
         long long numberOfItems, long long massOfKnapSack, long long &items_power) {

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

    long long fst_items_power = items_power;
    long long snd_items_power = items_power;

    // take an item in knapsack
    if (massOfKnapSack - massOfItems[numberOfItems] >= 0) {

        fst = knapsack(mem, massOfItems, priceOfItems, numberOfItems - 1,
                       massOfKnapSack - massOfItems[numberOfItems], fst_items_power)
              + priceOfItems[numberOfItems];
        fst_items_power++;
    } else // we can't take this item
        fst = 0;

    // don't take
    snd = knapsack(mem, massOfItems, priceOfItems, numberOfItems - 1, massOfKnapSack, snd_items_power);

    if(fst * fst_items_power > snd * snd_items_power) {
        mem[numberOfItems][massOfKnapSack] = fst * fst_items_power;
        items_power = fst_items_power;
    }
    else {
        mem[numberOfItems][massOfKnapSack] = snd * snd_items_power;
        items_power = snd_items_power;
    }
    return mem[numberOfItems][massOfKnapSack];

}

void recovery(vector<vector<long long>> &mem, vector<long long> &massOfItems, vector<long long> &priceOfItems,
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
    long long items_power = 0;

    knapsack(mem, massOfItems, priceOfItems, numberOfItems, massOfKnapSack, items_power);

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
        cin >> massOfItems[i];
        cin >> priceOfItems[i];
    }

    knapsack(massOfItems, priceOfItems, numberOfItems, massOfKnapSack);

    return 0;


}