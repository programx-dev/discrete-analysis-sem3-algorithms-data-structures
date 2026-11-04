#include <vector>

using namespace std;

class SegmentTree {
    vector<int> T;
    int N;

    int get_sum(int idx, int L, int R, int l, int r) const {
        if (r < L || R < l) {
            return 0;
        }

        if (L <= l && r <= R) {
            return T[idx];
        }

        int m = l + (r - l) / 2;

        return get_sum(2 * idx + 1, L, R, l, m) + get_sum(2 * idx + 2, L, R, m + 1, r);
    }

  public:
    SegmentTree(int n) {
        N = 1;
        while (N < n) {
            N *= 2;
        }

        T.assign(2 * N - 1, 0);
    }

    void set_value(int pos, int value) {
        int idx = N - 1 + pos - 1;
        T[idx] = value;

        while (idx > 0) {
            idx = (idx - 1) / 2;
            T[idx] = T[2 * idx + 1] + T[2 * idx + 2];
        }
    }

    int range_sum(int L, int R) const {
        return get_sum(0, L, R, 1, N);
    }
};