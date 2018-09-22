void constructZ(vll s) {
	ll n = s.size();
	ll l,r,k;
	l = r = 0;
	for(ll i=1;i<n;i++) {
		if(i>r) {
			l = r = i;
			while((r < n) && (s[r-l] == s[r])) r++;
			z[i] = (r - l);
			r--;
		}
		else {
			k = (i - l);
			if(z[k] < (r - i + 1)) z[i] = z[k];
			else {
				l = i;
				while(r < n && (s[r - l] == s[r])) r++;
				z[i] = (r - l);
				r--;
			}
		}
	}
}