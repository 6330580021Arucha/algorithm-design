#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> A = {1, 2, 3, 4, 5};
    for (auto a : A)
        cout << a << " ";
    cout << endl;

    A.resize(2);
    for (auto a : A)
        cout << a << " ";
    cout << endl;

    A.resize(5);
    for (auto a : A)
        cout << a << " ";
    cout << endl;
}