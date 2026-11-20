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

vector<int> computeSP(const string &P) {
    vector<int> Z = computeZ(P);
    int n = Z.size();
    vector<int> SP(n, 0);

    for (int j = n - 1; j > 0; --j) {
        if (Z[j] == 0) {
            continue;
        }

        int i = j + Z[j] - 1;
        SP[i] = Z[j];
    }

    return SP;
}

vector<int> KMP(const string &T, const string &P) {
    vector<int> SP = computeSP(P);
    vector<int> ans;
    int n = T.size();
    int m = P.size();

    int i = 0, j = 0;
    while (i < n) {
        while (i < n && j < m && T[i] == P[j]) {
            ++i;
            ++j;
        }

        if (j == m) {
            ans.push_back(i - m);
            j = SP[j - 1];
        } else if (j == 0) {
            ++i;
        } else {
            j = SP[j - 1];
        }
    }

    return ans;
}

int main() {
    string T = "ABACABACABADABADABACABADABA";
    string P = "ABACABADABA";

    vector<int> Z = computeZ(P);
    vector<int> SP = computeSP(P);
    vector<int> ans = KMP(T, P);

    int m = P.size();

    cout << "T: " << T << '\n';
    cout << "P: " << P << '\n';

    cout << "Z(P): ";
    for (int i = 0; i < m; ++i) {
        cout << Z[i] << ' ';
    }
    cout << '\n';

    cout << "Strong SP(P): ";
    for (int i = 0; i < m; ++i) {
        cout << SP[i] << ' ';
    }
    cout << '\n';

    cout << "KMP: ";
    int count = ans.size();
    for (int i = 0; i < count; ++i) {
        cout << ans[i] << ' ';
    }
    cout << '\n';

    return 0;
}