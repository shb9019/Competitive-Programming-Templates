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
	ll d,c;
	struct less_than{
    	bool operator()(const flow &a, const flow &b){
       		return a.d < b.d;
 		}
 	};
};
vector<vector<flow> > graph;
vll level;

bool comp(flow a, flow b) {
	return a.d < b.d;
}

bool bfs(ll start, ll end, ll n) {
	vector<bool> visited(n+1,false);
	ll i;
	fo(i,1,n+1) level[i] = -1;

	queue<ll> q;
	q.push(start);
	level[start] = 0;
	visited[start] = true;
	
	while(!q.empty()) {
		ll top = q.front();
		q.pop();
		fo(j,0,sz(graph[top])) {
			flow t = graph[top][j];
			if(!visited[t.d] && t.c > 0) {
				visited[t.d] = true;
				level[t.d] = level[top] + 1;
				q.push(t.d);
			}
		}
	}
	return visited[end];
}

ll sendFlow(ll s, ll flow, ll t, vll& start) {
	if(s == t) return min(flow,INFLL);
	for(;start[s]<sz(graph[s]);start[s]++) {
		if(level[graph[s][start[s]].d] == level[s]+1 && graph[s][start[s]].c > 0) { 
			ll curr_flow = min(flow,graph[s][start[s]].c);
			ll temp_flow = sendFlow(graph[s][start[s]].d,curr_flow,t,start);
			if(temp_flow > 0) {
				graph[s][start[s]].c -= temp_flow;
				struct flow temp;
				temp.d = s;
				ll index = (lower_bound(all(graph[graph[s][start[s]].d]), temp, flow::less_than()) - graph[graph[s][start[s]].d].begin());	
				graph[graph[s][start[s]].d][index].c -= temp_flow;
				return temp_flow;
			}
		}
	}

	return 0;
}

ll dinic(ll st, ll end, ll n) {
	if(st == end) return -1;

	ll total_flow = 0;

	while(bfs(st,end,n)) {
		vll start(n+1,0);
		while(ll flow = sendFlow(st, INFLL, end, start)) {
			total_flow += flow;
		}
	}

	return total_flow;
}

int main() {
	ll n,m;
	cin>>n>>m;
	graph.resize(n+1);
	level.resize(n+1,-1);
	fo(i,0,m) {
		ll a,b,c;
		cin>>a>>b>>c;
		flow tmp;
		tmp.d = b; tmp.c = c;
		graph[a].pb(tmp);
		tmp.d = a; tmp.c = 0;
		graph[b].pb(tmp);
	}
	fo(i,0,n+1) sort(all(graph[i]),comp);
	cout << dinic(1,n,n) << endl;
	return 0;
}