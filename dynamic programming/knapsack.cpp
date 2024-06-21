#include <iostream>
#include <vector>

using namespace std;

int knapsack(int W, vector<int> w, vector<int> p, int pos, int price)
{
    if (pos < 0)
        return price;
    if (w[pos] <= W)
    {
        int price1 = knapsack(W, w, p, pos - 1, price);
        int price2 = knapsack(W - w[pos], w, p, pos - 1, price + p[pos]);
        return max(price1, price2);
    }
    else
        return knapsack(W, w, p, pos - 1, price);
}

vector<vector<int>> table(5, vector<int>(21, 0));
int knapsack_bottom_up(int W, vector<int> w, vector<int> p, int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= W; j++)
        {
            if (w[i - 1] > j)
                table[i][j] = table[i - 1][j];
            else
                table[i][j] = max(table[i - 1][j - w[i - 1]] + p[i - 1], table[i - 1][j]);
        }
    }
    return table[n][W];
}

int main()
{
    int W = 20;
    vector<int> w = {10, 5, 10, 20};
    vector<int> p = {10, 20, 30, 40};
    int n = w.size();

    printf("recursion : %d\n", knapsack(W, w, p, w.size() - 1, 0));
    printf("bottom up : %d\n", knapsack_bottom_up(W, w, p, n));
}