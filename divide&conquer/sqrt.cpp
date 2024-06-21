#include <iostream>
#include <cmath>

using namespace std;

double sqrt(int n, double start, double stop)
{
    double x = (start + stop) / 2;
    double e = x * x - n;
    if (abs(e) < 0.00001)
        return x;
    else
    {
        if (e < 0)
            return sqrt(n, x, stop);
        else
            return sqrt(n, start, x);
    }
}

int main()
{
    int n = 36;
    cout << "my sqrt : " << sqrt(n, 0, n) << endl;
    cout << "sqrt : " << sqrt(n) << endl;
}