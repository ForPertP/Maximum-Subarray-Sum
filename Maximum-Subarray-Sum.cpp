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
    set<long> sums;
    long sum = 0;
    long max_modular_sum = 0;

    for (long num : a)
    {
        sum = (sum + num) % m;
        auto it = sums.upper_bound(sum);
    
        if (it != sums.end())
        {
            max_modular_sum = max(max_modular_sum, (sum - *it + m) % m);
        }
        
        sums.insert(sum);
        max_modular_sum = max(max_modular_sum, sum);
    }

    return max_modular_sum;
}


long maximumSum2(vector<long> a, long m)
{
    std::vector<std::pair<long, long>> sums(a.size());
    sums[0].first = a[0] % m;
    sums[0].second = 1;
    
    for (size_t i = 1; i < a.size(); ++i)
    {
        sums[i].first = (sums[i - 1].first + a[i] % m) % m;
        sums[i].second = i + 1;
    }
    
    std::sort(sums.begin(), sums.end());
    long max_modular_sum = sums[sums.size() - 1].first;
    long min_diff = LONG_MAX;

    for (size_t i = 0; i < a.size() - 1; ++i)
    {
        if (sums[i].second > sums[i + 1].second)
        {
            if ((sums[i+1].first - sums[i].first) < min_diff)
            {
                min_diff = sums[i + 1].first - sums[i].first;
            }
        }
    }

    return std::max(max_modular_sum, m - min_diff);
}


int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        long m = stol(first_multiple_input[1]);

        string a_temp_temp;
        getline(cin, a_temp_temp);

        vector<string> a_temp = split(rtrim(a_temp_temp));

        vector<long> a(n);

        for (int i = 0; i < n; i++) {
            long a_item = stol(a_temp[i]);

            a[i] = a_item;
        }

        long result = maximumSum(a, m);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
