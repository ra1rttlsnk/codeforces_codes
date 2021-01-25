#include <bits/stdc++.h>
using namespace std;
struct Segtree {
    int size;
    vector<long long> sums;
    
    void init(int n) {
        size = 1;
        while (size < n) {
            size *= 2;
        }
        sums.assign(size*2, 0LL);
    }
    void build(vector<long long> &leaves, int x, int lx, int rx) {
        
        if (rx - lx == 1) {
            if (lx < leaves.size()) sums[x] = leaves[lx];
            return;
        }
        int m = (lx+rx)/2;
        build(leaves, 2*x+1, lx, m);
        build(leaves, 2*x+2, m, rx);
        sums[x] = sums[2*x+1] + sums[2*x+2];
    }
    void build(vector<long long> &leaves) {
        build(leaves, 0, 0, size);
    }
    
    void print_segtree(){
        for(int i = 0; i < log2(sums.size()); i++) {
            for (int j = int(pow(2,i)-1); j < int(pow(2,i))+int(pow(2,i))-1; j++)
                cout << sums[j] << " ";
            cout << endl;
        }
    }
    void set(int i, int x, int lx, int rx, long long v) {
        if (i >= rx || i < lx) return;
        if (rx - lx == 1) {
            sums[x] = v;
            return;
        }
        int m = (lx+rx)/2;
        if (i < m)
            set(i, 2*x+1, lx, m, v);
        else
            set(i, 2*x+2, m, rx, v);
        sums[x] = sums[2*x+1] + sums[2*x+2];
    }
    void set(int i, long long v) {
        set(i, 0, 0, size, v);
    }
    
    long long sum(int x, int lx, int rx, int l, int r) {
        if (r <= lx || rx <= l) return 0;
        if (l <= lx && r >= rx) return sums[x];
        int m = (lx+rx)/2;
        return sum(2*x+1, lx, m, l, r)+sum(2*x+2, m, rx, l, r);
    }
    
    long long sum(int l, int r) {
        return sum(0, 0, size, l, r);
    }
};

int main() {
    
}