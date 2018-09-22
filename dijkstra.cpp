vll dijkstra(vector<vector<pll> > graph, ll s) {
	ll n = sz(graph);
	vll ans(n+1,INFLL);
	priority_queue<pll, vector<pll>, greater<pll> > q;
	vector<bool> visited(n+1,false);
	q.push(mp(0,s));
	ans[s] = 0;
	while(!q.empty()) {
		pll u = q.top();
		q.pop();
		if(visited[u.S]) continue;
		visited[u.S] = true;
		foreach(i,graph[u.S]) {
			pll v = *i;
			if(ans[v.F] > ans[u.S] + v.S) {
				ans[v.F] = ans[u.S] + v.S;
				q.push(mp(ans[v.F],v.F));
			}
		}
	}
	return ans;
}
