#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>

using namespace std;

// ========================== normal mode(half) ==========================
pair<int, int> find_mode(vector<int> A, int left, int right)
{
    if (A.size() == 0)
        return make_pair(0, 0);
    if (left > right)
        return make_pair(0, 0);
    map<int, int> map;
    for (int i = left; i <= right; i++)
    {
        if (map.find(A[i]) == map.end())
            map[A[i]] = 1;
        else
            map[A[i]]++;
    }

    int mode = 0;
    int n_mode = 0;
    for (auto a : map)
    {
        if (a.second > n_mode)
        {
            mode = a.first;
            n_mode = a.second;
        }
    }

    return make_pair(mode, n_mode);
}

pair<int, int> mode_with_half(vector<int> A, int left, int right)
{
    if (A.size() == 0)
        return make_pair(0, 0);
    if (left == right)
        return find_mode(A, left, right);
    else
    {
        int m = (left + right) >> 1;

        pair<int, int> m_left = mode_with_half(A, left, m);
        pair<int, int> m_right = mode_with_half(A, m + 1, right);

        int mode = (m_left.second >= m_right.second) ? m_left.first : m_right.first;
        int n_mode = (m_left.second >= m_right.second) ? m_left.second : m_right.second;
        bool left = (m_left.second > m_right.second) ? true : false;

        if (A[m] == A[m + 1])
        {
            int m_mode = A[m];
            int m_left = m;
            int m_right = m + 1;

            while (m_left >= left && A[m_left] == A[m])
                m_left--;
            m_left++;
            while (m_right <= right && A[m_right] == A[m + 1])
                m_right++;
            m_right--;

            int m_n_mode = m_right - m_left + 1;

            mode = (n_mode > m_n_mode) ? mode : m_mode;
            n_mode = (n_mode > m_n_mode) ? n_mode : m_n_mode;
        }
        return make_pair(mode, n_mode);
    }
}

// ========================== half mode 2 ==========================
pair<int, int> mode_with_half_2(vector<int> A, int left, int right)
{
    if (A.size() == 0)
        return make_pair(0, 0);
    if (left == right)
        return find_mode(A, left, right);
    else
    {
        int m = (left + right) >> 1;
        if (A[m] != A[m + 1])
        {
            pair<int, int> ans1 = mode_with_half_2(A, left, m);
            pair<int, int> ans2 = mode_with_half_2(A, m + 1, right);

            int mode = (ans1.second >= ans2.second) ? ans1.first : ans2.first;
            int n_mode = (ans1.second >= ans2.second) ? ans1.second : ans2.second;

            return make_pair(mode, n_mode);
        }
        else
        {
            int tmp = A[m];
            int m_left = m;
            int m_right = m;

            while (m_left >= left && tmp == A[m_left])
                m_left--;
            if (m_left < left)
            {
                while (m_right <= right && tmp == A[m_right])
                    m_right++;
                if (m_right > right)
                    return make_pair(A[right], right - left + 1);
                m = m_right - 1;
            }
            else
            {
                m = m_left;
            }

            pair<int, int> ans1 = mode_with_half_2(A, left, m);
            pair<int, int> ans2 = mode_with_half_2(A, m + 1, right);

            int mode = (ans1.second >= ans2.second) ? ans1.first : ans2.first;
            int n_mode = (ans1.second >= ans2.second) ? ans1.second : ans2.second;

            return make_pair(mode, n_mode);
        }
    }
}

// ========================== jump mode ==========================
pair<int, int> find_mode2(vector<int> A, int left, int right)
{
    return make_pair(A[left], right - left + 1);
}

pair<int, int> mode_with_jump(vector<int> A, int left, int right)
{
    if (A.size() == 0)
        return make_pair(0, 0);
    if (left == right)
        return find_mode2(A, left, right);
    else
    {
        int tmp = A[left];
        int m = left;
        while (m <= right && A[m] == tmp)
            m++;
        m--;

        if (m == right)
            return find_mode2(A, left, right);

        pair<int, int> ans_left = find_mode2(A, left, m);
        pair<int, int> ans_right = mode_with_jump(A, m + 1, right);

        int mode = (ans_left.second >= ans_right.second) ? ans_left.first : ans_right.first;
        int n_mode = (ans_left.second >= ans_right.second) ? ans_left.second : ans_right.second;

        return make_pair(mode, n_mode);
    }
}

vector<bool> test_function()
{
    vector<bool> result(4, true);
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
        {0, 0},  // 0 Empty vector
        {1, 1},  // 1 Single element
        {1, 5},  // 2 All elements the same
        {1, 6},  // 3 All elements the same(even)
        {1, 1},  // 4 Two different elements
        {2, 5},  // 5 Two different elements with more duplicates
        {1, 1},  // 6 Increasing sequence
        {1, 2},  // 7 NEW
        {2, 4},  // 8 Mixed elements
        {-3, 1}, // 9 Vector with negative numbers
        {1, 2}   // 10 Vector with duplicates and unique elements
    };

    for (int i = 0; i < test_cases.size(); i++)
    {
        if (find_mode(test_cases[i], 0, test_cases[i].size() - 1) != expected_results[i])
        {
            pair<int, int> A = find_mode(test_cases[i], 0, test_cases[i].size() - 1);
            printf("brute force : {%d, %d} (testcase: %d)\n", A.first, A.second, i);
            result[0] = false;
        }
        if (mode_with_half(test_cases[i], 0, test_cases[i].size() - 1) != expected_results[i])
        {
            pair<int, int> A = mode_with_half(test_cases[i], 0, test_cases[i].size() - 1);
            printf("divide : {%d, %d} (testcase: %d)\n", A.first, A.second, i);
            result[1] = false;
        }
        if (mode_with_half_2(test_cases[i], 0, test_cases[i].size() - 1) != expected_results[i])
        {
            pair<int, int> A = mode_with_half_2(test_cases[i], 0, test_cases[i].size() - 1);
            printf("divide2 : {%d, %d} (testcase: %d)\n", A.first, A.second, i);
            result[2] = false;
        }
        if (mode_with_jump(test_cases[i], 0, test_cases[i].size() - 1) != expected_results[i])
        {
            pair<int, int> A = mode_with_jump(test_cases[i], 0, test_cases[i].size() - 1);
            printf("divide_jump : {%d, %d} (testcase: %d)\n", A.first, A.second, i);
            result[3] = false;
        }
    }

    return result;
}

int main()
{
    vector<bool> result = test_function();

    for (auto a : result)
    {
        if (a)
            cout << "TRUE ";
        else
            cout << "FALSE ";
    }
}