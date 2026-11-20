#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// [L..R]
vector<int> computeZ(const string &S) {
    int n = S.size();
    int L = 0;
    int R = -1;
    vector<int> Z(n, 0);

    for (int i = 1; i < n; ++i) {
        if (i <= R) {
            Z[i] = min(R - i + 1, Z[i - L]);
        }

        while (i + Z[i] < n && S[i + Z[i]] == S[Z[i]]) {
            ++Z[i];
        }

        if (i + Z[i] - 1 > R) {
            L = i;
            R = i + Z[i] - 1;
        }
    }

    return Z;
}

vector<vector<int>> computeStrongSPRealTime(const string &P) {
    int m = P.size();
    vector<int> Z = computeZ(P);
    vector<vector<int>> SP(m, vector<int>(256, 0));

    for (int j = m - 1; j > 0; --j) {
        if (Z[j] == 0) {
            continue;
        }

        int i = j + Z[j] - 1;
        int x = (unsigned char)P[Z[j]];

        SP[i][x] = Z[j];
    }

    return SP;
}

vector<int> searchKMPRealTime(const string &T, const string &P) {
    int n = T.size();
    int m = P.size();
    vector<int> ans;

    vector<vector<int>> SP = computeStrongSPRealTime(P);

    int i = 0, j = 0;
    while (i < n) {
        while (i < n && j < m && T[i] == P[j]) {
            ++i;
            ++j;
        }

        if (j == m) {
            ans.push_back(i - m);
        }

        if (i == n) {
            break;
        }

        if (j == 0) {
            ++i;
        } else {
            int x = (unsigned char)T[i];
            j = SP[j - 1][x];
        }
    }

    return ans;
}

int main() {
    string T = "ABACABACABADABADABACABADABA";
    string P = "ABACABADABA";

    vector<int> ansRealTime = searchKMPRealTime(T, P);

    cout << "KMP real time: ";
    int countRealTime = ansRealTime.size();
    for (int i = 0; i < countRealTime; ++i) {
        cout << ansRealTime[i] << ' ';
    }
    cout << '\n';

    return 0;
}
