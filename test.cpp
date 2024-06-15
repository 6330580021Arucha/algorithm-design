#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>

using namespace std;

pair<int, int> find_mode(vector<int> A, int left, int right)
{
    if (A.size() == 0)
        return {-1, -1};
    if (A.size() == 1)
        return {A[0], 1};
    if (left > right)
        return {-1, -1};

    int mode = A[left];
    int fre = 1;

    int tmp = A[left];
    int n = 1;
    for (int i = 1; i < A.size(); i++)
    {
        if (tmp == A[i])
        {
            n++;
            if (n > fre)
            {
                mode = tmp;
                fre = n;
            }
        }
        else
        {
            if (n > fre)
            {
                mode = tmp;
                fre = n;
            }
            tmp = A[i];
            n = 1;
        }
    }
    return {mode, fre};
}

pair<int, int> mode_divide(vector<int> A, int left, int right)
{
    if (A.size() == 0)
        return {-1, -1};
    if (left == right)
        return {A[left], 1};
    else
    {
        int m = (left + right) >> 1;

        pair<int, int> m_left = mode_divide(A, 0, m);
        pair<int, int> m_right = mode_divide(A, m + 1, right);

        int mode = (m_left.second >= m_right.second) ? m_left.first : m_right.first;
        int n_mode = (m_left.second >= m_right.second) ? m_left.second : m_right.second;

        if (A[m] != A[m + 1])
            return {mode, n_mode};
        else
        {
            int m_mode =A[m];
            int m_left = m;
        }
    }
}

bool test_function()
{
    vector<vector<int>> test_cases = {
        {},                                // 0 Empty vector
        {1},                               // 1 Single element
        {1, 1, 1, 1, 1},                   // 2 All elements the same
        {1, 1, 1, 1, 1, 1},                // 3 All elements the same(even)
        {1, 2},                            // 4 Two different elements
        {2, 2, 2, 2, 2, 3, 3, 3, 3},       // 5 Two different elements with more duplicates
        {1, 2, 3, 4, 5},                   // 6 Increasing sequence
        {1, 1, 2, 5, 5},                   // 7 NEW
        {1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3}, // 8 Mixed elements
        {-3, -2, -1, 0, 1, 2, 3},          // 9 Vector with negative numbers
        {1, 1, 2, 3, 3, 4, 5, 5, 6}        // 10 Vector with duplicates and unique elements
    };

    vector<pair<int, int>> expected_results = {
        {-1, -1}, // 0 Empty vector
        {1, 1},   // 1 Single element
        {1, 5},   // 2 All elements the same
        {1, 6},   // 3 All elements the same(even)
        {1, 1},   // 4 Two different elements
        {2, 5},   // 5 Two different elements with more duplicates
        {1, 1},   // 6 Increasing sequence
        {1, 2},   // 7 NEW
        {2, 4},   // 8 Mixed elements
        {-3, 1},  // 9 Vector with negative numbers
        {1, 2}    // 10 Vector with duplicates and unique elements
    };

    for (int i = 0; i < test_cases.size(); i++)
    {
        if (find_mode(test_cases[i], 0, test_cases[i].size() - 1) != expected_results[i])
        {
            // pair<int, int> A = find_mode(test_cases[i], 0, test_cases[i].size() - 1);
            // pair<int, int> B = expected_results[i];
            // cout << "testcase: " << i << endl;
            // printf("{%d, %d}\n", A.first, A.second);
            // printf("{%d, %d}\n", B.first, B.second);
            return false;
        }
    }
    return true;
}

int main()
{
    bool result = test_function();

    if (result)
        cout << "TRUE" << endl;
    else
        cout << "FALSE" << endl;
}

// printf("first: %d, second: %d", a.first, a.second);
