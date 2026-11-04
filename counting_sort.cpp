#include <vector>

using namespace std;

int max(const vector<int> &arr) {
    int n = static_cast<int>(arr.size());
    int mx = arr[0];
    for (int i = 1; i < n; ++i) {
        mx = max(mx, arr[i]);
    }
    return mx;
}

vector<int> counting_sort(const vector<int> &arr) {
    int n = static_cast<int>(arr.size());

    if (n == 0) {
        return vector<int>();
    }

    int mx = arr[0];
    for (int i = 1; i < n; ++i) {
        mx = max(mx, arr[i]);
    }

    vector<int> sorted(n);
    vector<int> cnt(mx + 1, 0);

    for (int i = 0; i < n; ++i) {
        ++cnt[arr[i]];
    }

    for (int i = 1; i < mx + 1; ++i) {
        cnt[i] += cnt[i - 1];
    }

    for (int i = n - 1; i >= 0; --i) {
        sorted[--cnt[arr[i]]] = arr[i];
    }

    return sorted;
}