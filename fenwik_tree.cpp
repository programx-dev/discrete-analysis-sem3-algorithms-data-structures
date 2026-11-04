#include <vector>

using namespace std;

class FenwickTree {
    vector<int> T;

  public:
    FenwickTree(int n) : T(n, 0) {
    }

    void add(int i, int delta_val = 1) {
        int n = T.size();
        while (i < n) {
            T[i] += delta_val;
            i = i | (i + 1);
        }
    }

    int prefix_sum(int i) const {
        int sum = 0;
        while (i >= 0) {
            sum += T[i];
            i = (i & (i + 1)) - 1;
        }
        return sum;
    }

    int range_sum(int l, int r) const {
        return prefix_sum(r) - prefix_sum(l - 1);
    }
};