#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'maximumSum' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. LONG_INTEGER_ARRAY a
 *  2. LONG_INTEGER m
 */

long maximumSum(vector<long> a, long m)
{
    std::vector<pair<long, long>> sum(a.size());
    sum[0].first = a[0] % m;
    sum[0].second = 1;
    
    for (size_t i = 1; i < a.size(); ++i)
    {
        sum[i].first = (sum[i - 1].first + a[i] % m) % m;
        sum[i].second = i + 1;
    }
    
    std::sort(sum.begin(), sum.end());
    long max = sum[sum.size() - 1].first;
    long min = LONG_MAX;

    for (size_t i = 0; i < a.size() - 1; ++i)
    {
        if (sum[i].second > sum[i + 1].second)
        {
            if ((sum[i+1].first - sum[i].first) < min)
            {
                min = sum[i + 1].first - sum[i].first;
            }
        }
    }

    return std::max(max, m - min);
}
