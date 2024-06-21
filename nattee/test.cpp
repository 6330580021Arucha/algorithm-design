#include <iostream>
#include <vector>
#include <map>

using namespace std;

bool is_day_cover(vector<int> day_vector)
{
    for (auto a : day_vector)
    {
        if (a == 0)
            return false;
    }
    return true;
}

int min_number = 99999999;

void min_student(map<int, vector<int>> student_map, vector<int> &day_vector, int student_count, int student_id, int m)
{
    if (is_day_cover(day_vector))
    {
        min_number = min(min_number, student_count);
        return;
    }
    if (student_count >= min_number)
        return;
    if (student_id == m)
        return;

    min_student(student_map, day_vector, student_count, student_id + 1, m);
    for (auto a : student_map[student_id])
        day_vector[a - 1] += 1;

    min_student(student_map, day_vector, student_count + 1, student_id + 1, m);
    for (auto a : student_map[student_id])
        day_vector[a - 1] -= 1;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> day_vector(n);
    map<int, vector<int>> student_map;

    for (int student_id = 0; student_id < m; student_id++)
    {
        int student_days;
        cin >> student_days;
        for (int j = 0; j < student_days; j++)
        {
            int day;
            cin >> day;
            student_map[student_id].push_back(day);
        }
    }

    min_student(student_map, day_vector, 0, 0, m);
    cout << min_number << endl;
}