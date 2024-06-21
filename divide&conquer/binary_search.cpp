#include <iostream>
#include <vector>

using namespace std;

int binary_search(vector<int> A, int k, int left, int right)
{
    if (left == right)
        return (A[left] == k) ? left : -1;
    int m = (left + right) >> 1;
    if (A[m] >= k)
        return binary_search(A, k, left, m);
    else
        return binary_search(A, k, m + 1, right);
}

int my_binary_search(vector<int> A, int k, int left, int right)
{
    if (left == right)
        return (A[left] == k) ? left : -1;
    int m_1 = (left + right) / 3;
    int m_2 = m_1 * 2;
    if (A[m_1] >= k)
        return my_binary_search(A, k, left, m_1);
    else if (A[m_2] >= k)
        return my_binary_search(A, k, m_1 + 1, m_2);
    else
        return my_binary_search(A, k, m_2 + 1, right);
}

int main()
{
    vector<int> A = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int k = 4;

    int pos_1 = binary_search(A, k, 0, A.size() - 1);
    printf("position_1 of %d : %d\n", k, pos_1);

    int pos_2 = my_binary_search(A, k, 0, A.size() - 1);
    printf("position_2 of %d : %d\n", k, pos_2);
}