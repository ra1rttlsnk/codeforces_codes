#include <bits/stdc++.h>
using namespace std;
 
void radix_sort(vector<pair<char, int>> &a) {
    int R = 256;
    int n = a.size();
    int count[R+1] = {0};
    vector<pair<char, int>> a_new(n);
    for (int i = 0; i < n; i++) {
        count[(int)a[i].first+1]++;
    }
    for (int i = 1; i < R+1; i++) {
        count[i] += count[i-1];
    }
    for (int i = 0; i < n; i++) {
        a_new[count[(int)a[i].first]++] = a[i]; 
    }
    a = a_new;
}
 
void count_sort(vector<pair<pair<int, int>, int>> &p) {
    int n = p.size();
    int count[n+1] = {0};
    
    for (int i = 0; i < n; i++) {
        count[p[i].first.first+1]++;
    }
    for (int i = 1; i < n; i++) {
        count[i] += count[i-1];
    }
    vector<pair<pair<int, int>, int>> p_new(n);
    for (int i = 0; i < n; i++) {
        p_new[count[p[i].first.first]++] = p[i];
    }
    
    p = p_new;
}
 
int upper_bound_finder(string &original, 
						string &query, 
						vector<pair<pair<int, int>, int>> &p, 
						int mid, 
						int last) 
{
    int upper_bound = mid;
	int first = mid+1;
	mid = (first+last)/2;
	while (first <= last) {
		int comp = original.compare(p[mid].second, query.size(), query);
		if (comp == 0){
			upper_bound = mid;
			first = mid+1;
			mid = (first+last)/2;
		}
		else if(comp > 0) {
			last = mid-1;
			mid = (first+last)/2;
		}
	}
	return upper_bound;
}
 
int lower_bound_finder(string &original, 
						string &query, 
						vector<pair<pair<int, int>, int>> &p, 
						int mid, 
						int first) 
{
    int lower_bound = mid;
	int last = mid-1;
	mid = (first+last)/2;
	while (first <= last) {
		int comp = original.compare(p[mid].second, query.size(), query);
		if (comp == 0){
			lower_bound = mid;
			last = mid-1;
			mid = (first+last)/2;
		}
		else if(comp < 0) {
			first = mid+1;
			mid = (first+last)/2;
		}
	}
	return lower_bound;
}
 
int substring_search(string &original, string &query, vector<pair<pair<int, int>, int>> &p) {
    int query_length = query.size();
    int first = 0;
    int last = original.size()-1;
    int mid = (first+last)/2;
    while (first <= last) {
        int comp = original.compare(p[mid].second, query_length, query);
        if (comp == 0){
            int upper_bound = upper_bound_finder(original, query, p, mid, last);
			int lower_bound = lower_bound_finder(original, query, p, mid, first);
			return upper_bound-lower_bound+1;
        }
        else if(comp > 0) {
            last = mid-1;
            mid = (first+last)/2;
        }
        else {
            first = mid+1;
            mid = (first+last)/2;
        }
        
    }
    return 0;
}
 
vector<int> LCP(string &s, vector<pair<pair<int, int>, int>> &p, int* c) {
    int k = 0;
    int n = s.length();
    vector<int> lcp(n);
    for (int i = 0; i < n-1; i++) {
	    int pi = c[i];
	    int j = p[pi-1].second;
	    while(s[i+k] == s[j+k])k++;
	    lcp[pi] = k;
	    k = max(k-1, 0);
    }
    return lcp;
}
 
long long number_of_different_substrings(string &s, vector<pair<pair<int, int>, int>> &p, vector<int> &lcp) {
    long long sum = 0;
    long long n = s.length()-1;
    for (int i = 1; i < n+1; i++) {
        sum += n-lcp[i]-p[i].second;
    }
    return sum;
}
 
string LCS(string &s, string &s1, string &s2, vector<pair<pair<int, int>, int>> &p, vector<int> &lcp) {
    int margin = s1.length();
    int max = 0;
    int max_index = 0;
    for (int i=3; i < s.length(); i++) {
		if (lcp[i] > max) {
		   int c1 = p[i-1].second < margin? 0 : 1;
		   int c2 = p[i].second < margin? 0 : 1;
		   if (c1 != c2){
		       max = lcp[i];
		       max_index = i;
		   }
			
		}
    }
    string lcs = "";//+s.substr(p[max_index].second, lcp[max_index]);
    int a = p[max_index-1].second;//+lcp[max_index];
    int b = p[max_index].second;//+lcp[max_index];
    while(s[a] == s[b] && a < s.length() && b < s.length()){
		lcs += s[a];
		a++; b++;
    }
    return lcs;
}
 
class Substring_comparer {
    private:
    vector<int> lcp;
    int* c;
    //vector<vector<int>> C;
    string s;
    
    public:
    Substring_comparer(vector<int> &lcp, int* c,
    //vector<vector<int>> &C,
    string &s) {
        this->lcp = lcp;
        this->c = c;
        //this->C = C;
        this->s = s;
    }
    
    int lcp_of_two_distant_suffixes(int l_a, int l_b) {
        int p_a = c[l_a];
        int p_b = c[l_b];
        int low = min(p_a, p_b)+1;
        int high = max(p_a, p_b);
        int minimum = lcp[low];
        for (int i = low+1; i < high+1; i++) {
            if (minimum == 0) return minimum;
            if (lcp[i] < minimum){
                minimum = lcp[i];
            }
        }
        return minimum;
    }
    
    bool operator()(pair<int, int> a, pair<int, int> b) {
        int len_a = a.second - a.first+1;
        int len_b = b.second - b.first+1;
        
        // when first position is equal
        if (a.first == b.first) {
            return a.second < b.second;
        }
        
        // when first position is not equal
        // and both are of same length
        else if (len_a == len_b) {
            int l = lcp_of_two_distant_suffixes(a.first, b.first);
            if (l >= len_a) {
                //means both substrings are equal
                return a < b;//? -1 : 1;
            }
            else {
                // same length, but different substrings
                return s[a.first+l] < s[b.first+l];
            }
        }
        
        //now, let's deal with the case where,
        //starting positions are different as well as
        //the length of both substrings are different
        else {
            int min_len = min(len_a, len_b);
            int l = lcp_of_two_distant_suffixes(a.first, b.first);
            if (l >= min_len)
                return len_a < len_b;//? -1 : 1;
            else {
                return s[a.first+l] < s[b.first+l];
            }
        }
        
    }
};
 
int main() {
    string s;
    string s1;
    cin >> s1;
    s = s1+"$";
    int n = s.size();
    vector<pair<char, int>> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = {s[i], i};
    }
    
    //sort(a.begin(), a.end());
    radix_sort(a);
    vector<pair<pair<int, int>, int>> p(n);
    p[0].second = a[0].second;
    int c[n];
    int C[int(log2(n))+1][n];
    
    c[a[0].second] = 0;
    C[0][a[0].second] = 0;
    for (int i = 1; i < n; i++) {
        if (a[i].first == a[i-1].first){
            c[a[i].second] = c[a[i-1].second];
            C[0][a[i].second] = c[a[i-1].second];
        }
        else{
            c[a[i].second] = c[a[i-1].second] + 1;
            C[0][a[i].second] = c[a[i-1].second] + 1;
        }
        p[i].second = a[i].second;
    }
    int k = 1;
    while(k < n) {
        for (int i = 0; i < n; i++) {
            p[i].first.second = c[p[i].second];
            if (p[i].second-k < 0){
                p[i].first.first = c[n + p[i].second-k];
                p[i].second = n+p[i].second-k;
            }
            else {
                p[i].first.first = c[p[i].second-k];
                p[i].second = p[i].second-k;
                
            }
        }
        
        count_sort(p);
        c[p[0].second] = 0;
        C[int(log2(k))+1][p[0].second] = 0;
        for (int i = 1; i < n; i++) {
            if (p[i].first == p[i-1].first){
                c[p[i].second] = c[p[i-1].second];
                C[int(log2(k))+1][p[i].second] = c[p[i-1].second];
            }
            else {
                c[p[i].second] = c[p[i-1].second]+1;
                C[int(log2(k))+1][p[i].second] = c[p[i-1].second] + 1;
            }
        }
        k *= 2;
    }
    int number_of_pairs;
    cin >> number_of_pairs;
    vector<pair<int, int>> substring_container(number_of_pairs);
    for (int i = 0; i < number_of_pairs; i++) {
        int l;
        int r;
        cin >> l;
        cin >> r;
        substring_container[i].first = l-1;
        substring_container[i].second = r-1;
    }
    vector<int> lcp = LCP(s, p, c);
    Substring_comparer SC = Substring_comparer(lcp, c, s);
    sort(substring_container.begin(), substring_container.end(), SC);
    for (auto i : substring_container) {
        cout << i.first+1 << " " << i.second+1 << endl;
    }
    /*for (int i = 0; i < int(log2(n))+1; i++) {
        for (int j = 0; j < n; j++) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }*/
}