#include <utility>
#include <vector>

using namespace std;

int part(vector<int> &arr, int lo, int hi);

// arr = [lo...hi]
void quick_sort(vector<int> &arr, int lo, int hi) {
    if (lo < hi) {
        int p = part(arr, lo, hi);
        quick_sort(arr, lo, p);
        quick_sort(arr, p + 1, hi);
    }
}

// arr = [lo.. <= p ..i)[i.. ? ..j](j.. >= p ..hi]
int part(vector<int> &arr, int lo, int hi) {
    int pivot = arr[lo + (hi - lo) / 2];
    int i = lo - 1;
    int j = hi + 1;
    while (true) {
        do
            ++i;
        while (arr[i] < pivot);
        do
            --j;
        while (arr[j] > pivot);
        if (i >= j)
            return j;
        swap(arr[i], arr[j]);
    }
}
