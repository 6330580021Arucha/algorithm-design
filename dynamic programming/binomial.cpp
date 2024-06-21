#include <iostream>
#include <vector>

using namespace std;

int binomial_recursion(int n, int r)
{
    if (r == 0 || r == n)
        return 1;
    return binomial_recursion(n - 1, r) + binomial_recursion(n - 1, r - 1);
}

vector<vector<int>> table_1(50, vector<int>(50, 0));
int binomial_DP_top_down(int n, int r)
{
    if (r == 0 || r == n)
        return table_1[n][r] = 1;
    if (table_1[n][r] != 0)
        return table_1[n][r];
    return table_1[n][r] = binomial_DP_top_down(n - 1, r) + binomial_DP_top_down(n - 1, r - 1);
}

vector<vector<int>> table_2(50, vector<int>(50, 0));
int binomial_DP_bottom_up(int n, int r)
{
    if (r == 0 || r == n)
        return 1;

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            if (j == 0 || j == i)
                table_2[i][j] = 1;
            else
                table_2[i][j] = table_2[i - 1][j] + table_2[i - 1][j - 1];
        }
    }
    return table_2[n][r];
}

int main()
{
    int n = 5;
    int r = 2;
    printf("recursion binomial : %d\n", binomial_recursion(n, r));
    printf("dynamic top down binomial : %d\n", binomial_DP_top_down(n, r));
    printf("dynamic bottom up binomial : %d\n", binomial_DP_bottom_up(n, r));
}