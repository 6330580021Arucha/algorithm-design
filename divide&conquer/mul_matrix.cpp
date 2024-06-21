#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> normal_mul_matrix(vector<vector<int>> A, vector<vector<int>> B)
{
    vector<vector<int>> result(A.size(), vector<int>(B[0].size(), 0));
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < B[0].size(); j++)
        {
            int sum = 0;
            for (int k = 0; k < A[0].size(); k++)
                sum += A[i][k] * B[k][j];
            result[i][j] = sum;
        }
    }
    return result;
}

vector<vector<int>> result;

void mul_matrix(vector<vector<int>> A, vector<vector<int>> B, int start, int stop)
{
    if (start + 1 == stop)
    {
        int m1 = (A[start][start] + A[stop][stop]) * (B[start][start] + B[stop][stop]);
        int m2 = (A[stop][start] + A[stop][stop]) * B[start][start];
        int m3 = A[start][start] * (B[start][stop] - B[stop][stop]);
        int m4 = A[stop][stop] * (B[stop][start] - B[start][start]);
        int m5 = (A[start][start] * A[start][stop]) * B[stop][stop];
        int m6 = (A[stop][start] - A[start][start]) * (B[start][start] + B[start][stop]);
        int m7 = (A[start][stop] - A[stop][stop]) * (B[stop][start] + B[stop][stop]);

        result[start][start] = m1 + m4 - m5 + m7;
        result[start][stop] = m3 + m5;
        result[stop][start] = m2 + m4;
        result[stop][stop] = m1 + m2 + m3 + m6;
        return;
    }

    int m = (start + stop) >> 1;
    mul_matrix(A, B, start, m);
    mul_matrix(A, B, m + 1, stop);
}

int main()
{
    vector<vector<int>> A = {
        {1, 2, 3},
        {5, 6, 7},
        {9, 10, 11}};

    vector<vector<int>> B = {
        {1, 0, 1},
        {1, 0, 1},
        {1, 0, 1}};

    for (auto a : A)
    {
        for (auto b : a)
            cout << b << " ";
        cout << endl;
    }
    cout << endl;

    for (auto a : B)
    {
        for (auto b : a)
            cout << b << " ";
        cout << endl;
    }
    cout << endl;

    vector<vector<int>> result = normal_mul_matrix(A, B);
    for (auto a : result)
    {
        for (auto b : a)
            cout << b << " ";
        cout << endl;
    }

    mul_matrix(A, B, 0, A.size() - 1);
    for (auto a : result)
    {
        for (auto b : a)
            cout << b << " ";
        cout << endl;
    }
}
