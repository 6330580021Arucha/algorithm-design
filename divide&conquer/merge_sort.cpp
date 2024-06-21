#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int> &A, int start, int m, int stop)
{
    vector<int> tmp(A.size());
    int left = start;
    int right = m + 1;
    for (int i = start; i <= stop; i++)
    {
        if (left > m)
        {
            tmp[i] = A[right++];
            continue;
        }
        if (right > stop)
        {
            tmp[i] = A[left++];
            continue;
        }
        tmp[i] = (A[left] < A[right]) ? A[left++] : A[right++];
    }
    for (int i = start; i <= stop; i++)
        A[i] = tmp[i];
}

void merge_sort(vector<int> &A, int start, int stop)
{
    if (start < stop)
    {
        int m = (start + stop) >> 1;
        merge_sort(A, start, m);
        merge_sort(A, m + 1, stop);
        merge(A, start, m, stop);
    }
}

int main()
{
    // vector<int> A = {100, 3, 11, 4, 76, 3, 122};
    // merge_sort(A, 0, A.size() - 1);
    // for (auto a : A)
    //     cout << a << " ";
    // cout << endl;

    vector<vector<int>> test_case = {
        {},
        {0},
        {1, 0},
        {2, 0, 1},
        {2, 3, 0, 1},
    };

    for (int i = 0; i < test_case.size(); i++)
        merge_sort(test_case[i], 0, test_case[i].size() - 1);

    for (auto a : test_case)
    {
        for (auto b : a)
            cout << b << " ";
        cout << endl;
    }
}