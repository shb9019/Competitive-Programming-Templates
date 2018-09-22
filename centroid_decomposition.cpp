#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double
#define mod 1000000007LL
#define eps 1e-13
#define PI 3.141592653589793238L
#define INF 1000000011
#define INFLL 1000000000000000011LL
#define endl '\n'
#define vi vector<int>
#define vs vector<string>
#define vll vector<long long>
#define vc vector<char>
#define vs vector<string>
#define pii pair<int, int>
#define pll pair<long long, long long>
#define pil pair<int, long long>
#define pli pair<long long, int>
#define pcc pair<char, char>
#define pdd pair<double, double>
#define mp make_pair
#define F first
#define S second
#define pb(x) push_back(x)
#define fo(i,a,n) for(i = (a); i < (n); i++)
#define foi(i,a,n) for(i = (a); i <= (n); i++)
#define pd(x) cout<<x
#define sd(x) cin>>x
#define nl cout<<endl
#define gtl(x) getline(cin, (x))
#define flsh fflush(stdout)
#define sws ios_base::sync_with_stdio(false); cin.tie(0)
#define gcd __gcd
#define clr(x) memset(x,0,sizeof(x))
#define all(a) (a).begin(), (a).end()
#define foreach(i,a) for(__typeof((a).begin()) i = (a).begin(); i != (a).end(); ++i)
#define sz(a) (int)((a).size())
ll n;
vector<vll> graph;
vector<bool> centroidMarked;
vector<vll> centroidTree;

vector<ll> subtree_size;
ll n2;

void DFS(ll src, ll p) {
	n2 += 1;
	subtree_size[src] = 1;
	foreach(i,graph[src]) {
		if(*i != p && !centroidMarked[*i]) {
			DFS(*i,src);
			subtree_size[src] += subtree_size[*i];
		}
	}
}

inline ll getCentroid2(ll src, ll n2) {
	bool exist = true;
	ll prev = -1;

	while(exist) {
		exist = false;
		foreach(i,graph[src]) {
			if(subtree_size[*i] > (n2/2) && *i != prev && !centroidMarked[*i]) {
				exist = true;
				prev = src;
				src = *i;
				break;
			}
		}
	}

	return src;
}

inline ll getCentroid(ll src) {
	n2 = 0;
	DFS(src,-1);
	ll centroid = getCentroid2(src, n2);
	centroidMarked[centroid] = true;
	return centroid;
}

inline ll decomposeTree(ll root) {
	ll cend_tree = getCentroid(root);
	foreach(i,graph[cend_tree]) {
		if(!centroidMarked[*i]) {
			ll cend_subtree = decomposeTree(*i,lev+1);
		}
	}
	return cend_tree;
}


int main() {
	cin>>n;
	graph.resize(n);
	centroidMarked.resize(n);
	centroidTree.resize(n);
	ll i;
	fo(i,0,n-1) {
		ll x,y;
		cin>>x>>y;
		graph[x-1].pb(y-1);
		graph[y-1].pb(x-1);
	}
	decomposeTree(0);
	return 0;
}