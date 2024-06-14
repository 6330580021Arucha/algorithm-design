#include <iostream>
#include <map>
#include <vector>

using namespace std;
typedef vector<int> Vector;
typedef map<int, Vector> Map;

int n; // days to cover
int m; // nisit count

Map nisit_map; // info of free days per nisit

Vector days_to_cov;
int least_ppl = 99999999;

int check_all_days_cov()
{
    for (auto x : days_to_cov)
    {
        if (x == 0)
            return 0;
    }
    return 1;
}

void brute(Vector &nisit_selection, int nisit_count, int nisit_id)
{
    if (check_all_days_cov() == 1)
        least_ppl = min(least_ppl, nisit_count);
    if (nisit_count >= least_ppl)
        return;
    if (nisit_id == nisit_selection.size())
        return;

    brute(nisit_selection, nisit_count, nisit_id + 1);

    for (int x : nisit_map[nisit_id])
    {
        days_to_cov[x - 1] += 1;
    }
    nisit_selection[nisit_id] = 1;
    brute(nisit_selection, nisit_count + 1, nisit_id + 1);
    nisit_selection[nisit_id] = 0;
    for (int x : nisit_map[nisit_id])
    {
        days_to_cov[x - 1] -= 1;
    }
}

void get_inputs()
{
    cin >> n >> m;
    days_to_cov.resize(n, 0); // Initialize with zeros
    for (int i = 0; i < m; ++i)
    {
        int day;
        cin >> day;
        for (int k = 0; k < day; ++k)
        {
            int free_day;
            cin >> free_day;
            nisit_map[i].push_back(free_day);
        }
    }
}

int main()
{
    get_inputs();
    Vector nisit_selection(m);
    brute(nisit_selection, 0, 0);
    cout << least_ppl << endl;
    return 0;
}