#include <iostream>
#include <vector>

using namespace std;

int partition(vector<int> &A, int start, int stop)
{
    int pivot = A[start];
    int left = start + 1;
    int right = stop;
    while (left <= right)
    {
        while (left <= right && A[left] <= pivot)
            left++;
        while (left <= right && A[right] >= pivot)
            right--;
        if (left < right)
            swap(A[left], A[right]);
    }
    swap(A[start], A[right]);
    return right;
}

void quick_sort(vector<int> &A, int start, int stop)
{
    if (start < stop)
    {
        int p = partition(A, start, stop);
        quick_sort(A, start, p - 1);
        quick_sort(A, p + 1, stop);
    }
}

int main()
{
    vector<int> A = {3, 100, 3, 11, 4, 76, 3, 122};
    quick_sort(A, 0, A.size() - 1);
    for (auto a : A)
        cout << a << " ";
    cout << endl;
}