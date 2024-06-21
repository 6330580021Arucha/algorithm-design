#include <iostream>
#include <vector>

using namespace std;

//=======================================
int max_suffix(vector<int> A, int stop)
{
    if (stop == 0)
        return A[0];
    return max(A[stop], max_suffix(A, stop - 1) + A[stop]);
}

int mss(vector<int> A, int stop)
{
    if (stop == 0)
        return A[0];
    int max1 = A[stop];
    int max2 = max_suffix(A, stop - 1) + A[stop];
    int max3 = mss(A, stop - 1);

    return max(max1, max(max2, max3));
}

//=======================================
int max_suffix_DP(vector<int> A, int stop, vector<int> &table, vector<bool> &done)
{
    if (stop == 0)
    {
        done[0] = true;
        table[0] = A[stop];
        return table[0];
    }
    if (done[stop])
        return table[stop];
    done[stop] = true;
    return table[stop] = max(A[stop], max_suffix_DP(A, stop - 1, table, done) + A[stop]);
}

int mss_1(vector<int> A, int stop, vector<int> &table, vector<bool> &done)
{
    if (stop == 0)
        return A[0];
    int max1 = A[stop];
    int max2 = max_suffix_DP(A, stop - 1, table, done) + A[stop];
    int max3 = mss_1(A, stop - 1, table, done);

    return max(max1, max(max2, max3));
}

//=======================================
int mss_bottom_up(vector<int> A)
{
    vector<int> max_suf(A.size());
    max_suf[0] = A[0];
    for (int i = 1; i < A.size(); i++)
        max_suf[i] = max(A[i], max_suf[i - 1] + A[i]);
    int mss = A[0];
    for (int i = 1; i < A.size(); i++)
        mss = max(max_suf[i - 1] + A[i], max(A[i], max_suf[i - 1]));
    return mss;
}

int main()
{
    vector<int> A = {1, -2, 4, 5, -1, 7, -3};
    vector<int> table(A.size());
    vector<bool> done(A.size());
    printf("recursive : %d\n", mss(A, A.size() - 1));
    printf("DP top down : %d\n", mss_1(A, A.size() - 1, table, done));
    printf("DP bottom up : %d\n", mss_bottom_up(A));
}