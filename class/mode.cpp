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
        if (a.second >= n_mode)
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

        int mode = (m_left.second > m_right.second) ? m_left.first : m_right.first;
        int n_mode = (m_left.second > m_right.second) ? m_left.second : m_right.second;

        if (A[m] == A[m + 1])
        {
            int m_mode = A[m];
            int left = m;
            int right = m + 1;

            while (A[left] == A[m])
                left--;
            left++;
            while (A[right] == A[m + 1])
                right++;
            right--;

            int m_n_mode = right - left + 1;

            mode = (n_mode >= m_n_mode) ? mode : m_mode;
            n_mode = (n_mode >= m_n_mode) ? n_mode : m_n_mode;
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

            int mode = (ans1.second > ans2.second) ? ans1.first : ans2.first;
            int n_mode = (ans1.second > ans2.second) ? ans1.second : ans2.second;

            return make_pair(mode, n_mode);
        }
        else
        {
            int tmp = A[m];
            int m_left = m;
            int m_right = m;

            while (tmp == A[m_left])
                m_left--;
            if (m_left < left)
            {
                while (tmp == A[m_right])
                    m_right++;
                m_right--;
                if (m_right == right)
                    return make_pair(A[right], right - left + 1);
                m = m_right;
            }
            else
            {
                m = m_left;
            }

            pair<int, int> ans1 = mode_with_half_2(A, left, m);
            pair<int, int> ans2 = mode_with_half_2(A, m + 1, right);

            int mode = (ans1.second > ans2.second) ? ans1.first : ans2.first;
            int n_mode = (ans1.second > ans2.second) ? ans1.second : ans2.second;

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

        int mode = (ans_left.second > ans_right.second) ? ans_left.first : ans_right.first;
        int n_mode = (ans_left.second > ans_right.second) ? ans_left.second : ans_right.second;

        return make_pair(mode, n_mode);
    }
}

int main()
{
    // vector<int> A;
    // vector<int> A = {1};
    // vector<int> A = {1, 1};
    // vector<int> A = {1, 1, 1};
    // vector<int> A = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    // vector<int> A = {0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8};
    // vector<int> A = {0, 1, 2, 3, 4, 4, 4, 5, 6, 7, 8};
    // vector<int> A = {0, 1, 2, 3, 4, 5, 6, 7, 8, 8, 8};
    // vector<int> A = {-2, -1, 0, 1, 2};
    // vector<int> A = {-2, -2, -1, 0, 1, 2};
    // vector<int> A = {-2, -1, 0, 0, 1, 2};
    vector<int> A = {1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3};

    pair<int, int> m = find_mode(A, 0, A.size() - 1);
    pair<int, int> my_mode = mode_with_half(A, 0, A.size() - 1);
    pair<int, int> mode_half = mode_with_half_2(A, 0, A.size() - 1);
    pair<int, int> mode_jump = mode_with_jump(A, 0, A.size() - 1);

    printf("mode_brute force = %d, frequently = %d\n", m.first, m.second);
    printf("================================================\n\n");

    printf("mode_divide = %d, frequently = %d\n", my_mode.first, my_mode.second);
    printf("================================================\n\n");

    printf("mode_divide_2 = %d, frequently = %d\n", mode_half.first, mode_half.second);
    printf("================================================\n\n");

    printf("mode_jump = %d, frequently = %d\n", mode_jump.first, mode_jump.second);
    printf("================================================\n\n");
}