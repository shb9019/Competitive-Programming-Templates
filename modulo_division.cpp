ll modInverse(ll b) {
	ll x,y;
	ll g = gcde(b,m,&x,&y);
	return (x%m + m)%m;
}

ll modDivide(ll a, ll b) {
	a = a%mod;
	return (modInverse(b,m)*a)%mod;
}