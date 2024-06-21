#include <iostream>
#include <vector>

using namespace std;

int fibonacci_recursion(int n)
{
    if (n == 0 || n == 1)
        return n;
    return fibonacci_recursion(n - 1) + fibonacci_recursion(n - 2);
}

vector<int> table(50);
int fibonacci_DP_top_down(int n)
{
    if (n == 0 || n == 1)
    {
        table[n] = n;
        return table[n];
    }
    if (table[n] > 0)
        return table[n];

    return table[n] = fibonacci_DP_top_down(n - 1) + fibonacci_DP_top_down(n - 2);
}

int fibonacci_DP_bottom_up(int n)
{
    if (n == 0 || n == 1)
        return n;
    int f1 = 0;
    int f2 = 1;
    int f;

    for (int i = 2; i <= n; i++)
    {
        f = f1 + f2;
        f1 = f2;
        f2 = f;
    }
    return f;
}

int main()
{
    int n = 6;
    printf("recursion fibonacci : %d\n", fibonacci_recursion(n));
    printf("dynamic top down fibonacci : %d\n", fibonacci_DP_top_down(n));
    printf("dynamic bottom up fibonacci : %d\n", fibonacci_DP_bottom_up(n));
}