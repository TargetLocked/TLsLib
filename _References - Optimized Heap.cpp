//begin: 小根堆

typedef long long LL;
LL h[23333];
int sz;
inline void hpush(LL k) {
	int i=(++sz);
	for(int f=i>>1;f&&h[f]>k;i=f,f>>=1) h[i]=h[f];
	h[i]=k;
}

inline LL hpoptop() {
	int i=1;
	LL ret=h[1],k=h[sz--];
	for(int s=2;s<=sz;i=s,s=i<<1) {
		if((s|1)<=sz&&h[s|1]<h[s]) s|=1;
		if(h[s]>=k) break;
		h[i]=h[s];
	}
	h[i]=k;
	return ret;
}

//end: 小根堆
