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
//int a[25]= { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
//int dw[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
//int dw[8][2]={{0,1},{1,0},{0,-1},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}};
//ll fibonacci[2][2] = {{0,1},{1,1}};
//ll identity[2][2] = {{1,0},{0,1}};
ll i,j,k;
struct flow {
	ll d, c, f;
	struct less_than{
    	bool operator()(const flow &a, const flow &b){
       		return a.d < b.d;
 		}
 	};
};
vector<vector<flow> > graph;

bool comp(flow a, flow b) {
	return a.d < b.d;
}

bool comp2(const flow &a, const ll b) {
	return a.d < b;
}

ll ford_fulkerson(ll start, ll end, ll n) {
	ll max_flow = 0;
	while(true) {
		vll parent(n+1,-1);
		vector<bool> visited(n+1,false);
		queue<pll> q;
		q.push(mp(start,INFLL));
		visited[start] = true;
		ll min_flow = -1;
		while(!q.empty()) {
			pll top = q.front();
			if(top.F == end) {
				min_flow = top.S;
				break;
			}
			q.pop();
			fo(i,0,sz(graph[top.F])) {
				flow t = graph[top.F][i];
				if(!visited[t.d] && t.c > 0) {
					parent[t.d] = top.F;
					visited[t.d] = true;
					q.push(mp(t.d,min(top.S,t.c)));
				}
			}
		}
		if(parent[end] == -1) break;
		ll curr = end;
		ll pf = INFLL;
		while(curr != start) {
			ll prev = parent[curr];
			flow temp;
			temp.d = curr; 
			ll index = (lower_bound(all(graph[prev]), temp, flow::less_than()) - graph[prev].begin());
			graph[prev][index].c -= min_flow;
			temp.d = prev;
			index = (lower_bound(all(graph[curr]), temp, flow::less_than()) - graph[curr].begin());
			graph[curr][index].c += min_flow;
			curr = prev;
		}
		max_flow += min_flow; 
	}
	return max_flow;
}

int main() {
	ll n,m;
	cin>>n>>m;
	graph.resize(n+1);
	fo(i,0,m) {
		ll a,b,c;
		cin>>a>>b>>c;
		flow tmp;
		tmp.d = b; tmp.c = c; tmp.f = 0;
		graph[a].pb(tmp);
		tmp.d = a; tmp.c = 0; tmp.f = 0;
		graph[b].pb(tmp);
	}
	fo(i,0,n+1) sort(all(graph[i]),comp);
	cout << ford_fulkerson(1,n,n) << endl;
	return 0;
}