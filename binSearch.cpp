ll getLastVal(vll v, ll val) {
	auto it = upper_bound(all(v),val);
	if(it == v.end()) return -1;
	return (it - v.begin() - 1);
}

ll getFirstVal(vll v, ll val) {
	auto it = lower_bound(all(v),val);
	if(it == v.end()) return -1;
	return (it - v.begin());
}