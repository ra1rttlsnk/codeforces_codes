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
struct MinSegtree {
    int size;
    vector<long long> mins;
    
    void init(int n) {
        size = 1;
        while (size < n) {
            size *= 2;
        }
        mins.assign(size*2, 0LL);
    }
    
    void build(vector<long long> &leaves, int x, int lx, int rx) {
        if (lx >= leaves.size()) { 
            mins[x] = INT_MAX;
            return;
        }
        if (rx - lx == 1) { 
            if (lx < leaves.size()) mins[x] = leaves[lx]; 
            return;
        }
        int m = (lx+rx)/2;
        build(leaves, 2*x+1, lx, m); 
        build(leaves, 2*x+2, m, rx);
        mins[x] = min(mins[2*x+1], mins[2*x+2]);
        
    }
    void build(vector<long long> &leaves) {
        build(leaves, 0, 0, size);
    }
    
    void set(int i, int x, int lx, int rx, long long v) {
        if (i >= rx || i < lx) return;
        if (rx - lx == 1) {
            mins[x] = v;
            return;
        }
        int m = (lx+rx)/2;
        if (i < m)
            set(i, 2*x+1, lx, m, v);
        else
            set(i, 2*x+2, m, rx, v);
        mins[x] = min(mins[2*x+1], mins[2*x+2]);
    }
    void set(int i, long long v) {
        set(i, 0, 0, size, v);
    }
    
    long long minimum(int x, int lx, int rx, int l, int r) {
        if (r <= lx || rx <= l) return INT_MAX;
        if (l <= lx && r >= rx) return mins[x];
        int m = (lx+rx)/2;
        return min(minimum(2*x+1, lx, m, l, r),minimum(2*x+2, m, rx, l, r));
    }
    long long minimum(int l, int r) {
        return minimum(0, 0, size, l, r);
    }
    
    void print_min_segtree(){
        for(int i = 0; i < log2(mins.size()); i++) {
            for (int j = int(pow(2,i)-1); j < int(pow(2,i))+int(pow(2,i))-1; j++)
                cout << mins[j] << " ";
            cout << endl;
        }
    }
};
struct MinCountSegtree {
    struct item{
        long long m;
        int c;
        void print() {
            cout << m << " " <<c;
        }
    };
    int size;
    vector<item> mins;
    
    void init(int n) {
        size = 1;
        while (size < n) {
            size *= 2;
        }
        mins.resize(size*2);
    }
    
    item merge(item a, item b) {
        if (a.m < b.m) return a;
        if (a.m > b.m) return b;
        return {a.m, a.c+b.c};
        
    }
    
    void build(vector<long long> &leaves, int x, int lx, int rx) {
        if (lx >= leaves.size()) { 
            mins[x] = {INT_MAX, 1};
            return;
        }
        if (rx - lx == 1) { 
            if (lx < leaves.size()) mins[x] = {leaves[lx], 1}; 
            return;
        }
        int m = (lx+rx)/2;
        build(leaves, 2*x+1, lx, m); 
        build(leaves, 2*x+2, m, rx);
        mins[x] = merge(mins[2*x+1], mins[2*x+2]);
        
    }
    void build(vector<long long> &leaves) {
        build(leaves, 0, 0, size);
    }
    
    void set(int i, int x, int lx, int rx, long long v) {
        if (i >= rx || i < lx) return;
        if (rx - lx == 1) {
            mins[x] = {v, 1};
            return;
        }
        int m = (lx+rx)/2;
        if (i < m)
            set(i, 2*x+1, lx, m, v);
        else
            set(i, 2*x+2, m, rx, v);
        mins[x] = merge(mins[2*x+1], mins[2*x+2]);
    }
    void set(int i, long long v) {
        set(i, 0, 0, size, v);
    }
    
    item minimum(int x, int lx, int rx, int l, int r) {
        if (r <= lx || rx <= l) return {INT_MAX, 1};
        if (l <= lx && r >= rx) return mins[x];
        int m = (lx+rx)/2;
        return merge(minimum(2*x+1, lx, m, l, r),minimum(2*x+2, m, rx, l, r));
    }
    item minimum(int l, int r) {
        return minimum(0, 0, size, l, r);
    }
    
    void print_segtree(){
        for(int i = 0; i < log2(mins.size()); i++) {
            for (int j = int(pow(2,i)-1); j < int(pow(2,i))+int(pow(2,i))-1; j++){
                mins[j].print();
                cout << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<long long> leaves(n);
    for (int i = 0; i < n; i++) {
        cin >> leaves[i];
    }
    MinCountSegtree st;
    st.init(n);
    st.build(leaves);
    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        if (k == 1) {
            int l;
            long long v;
            cin >> l;
            cin >> v;
            st.set(l, v);
        }
        else {
            int l, r;
            cin >> l >> r;
            st.minimum(l, r).print();
            cout << endl;
        }
    }
}