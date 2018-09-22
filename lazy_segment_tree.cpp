vll lazy;
vll segTree;

inline ll getVal(ll index, ll l, ll r, ll findex) {
	if(lazy[index] != 0) {
		segTree[index] += (r-l+1)*lazy[index];
		if(l!=r) {
			lazy[2*index+1] += lazy[index];
			lazy[2*index+2] += lazy[index];
		}
		lazy[index] = 0;
	}
	if(l == r) return segTree[index];
	ll mid = ((l+r)/2);
	if(findex <= mid) return getVal(2*index+1,l,mid,findex);
	else return getVal(2*index+2,mid+1,r,findex);
}

inline void updateVal(ll index, ll l, ll r, ll fl, ll fr) {
	if(lazy[index] != 0) {
		segTree[index] += (r-l+1)*lazy[index];
		if(l!=r) {
			lazy[2*index+1] += lazy[index];
			lazy[2*index+2] += lazy[index];
		}
		lazy[index] = 0;
	}
	if(l >= fl && r <= fr) {
		segTree[index] += (r-l+1);
		if(l!=r) {
			lazy[2*index+1]++;
			lazy[2*index+2]++;
		}
		return;
	}
	if (r < fl || l > fr) {
		return;
	}
	ll mid = ((l+r)/2);
	updateVal(2*index+1,l,mid,fl,fr);
	updateVal(2*index+2,mid+1,r,fl,fr);
}