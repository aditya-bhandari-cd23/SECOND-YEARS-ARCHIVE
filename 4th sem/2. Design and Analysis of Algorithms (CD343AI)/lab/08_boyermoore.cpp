#include<iostream>
#include<vector>
using namespace std;

void boyerMoore(string txt, string pat)
{
    int n = txt.size();
    int m = pat.size();
    int i;
    vector<int> table(256, m);
    for (i = 0; i < m - 1; i++)
        table[pat[i]] = m - i - 1;

    while (i < n) {
        int k = 0;
        while (k < m && txt[i - k] == pat[m - k - 1])
            k++;

        if (k == m) {
            cout << "occurrence found at index: " << (i - m + 1) << '\n';
            i += m;
        }
        else
            i += max(table[txt[i - k]], 1);
    }
}
