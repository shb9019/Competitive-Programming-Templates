void bfs(vector<vll> graph) {
	vector<bool> visited(n,false);
	fo(i,0,n) {
		if(!visited[i]) {
			visited[i] = true;
			count++;
			queue<ll> q;
			q.push(i);
			while(!q.empty()) {
				ll top = q.front();
				q.pop(); 
				fo(j,0,graph[top].size()) {
					if(!visited[graph[top][j]]) {
						visited[graph[top][j]] = true;
						q.push(graph[top][j]);
					}
				}
			}
		}
	}
}