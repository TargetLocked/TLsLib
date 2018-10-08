#include <bits/stdc++.h>

std::mt19937 gen;
std::mt19937_64 gen64;

inline void randinit() {
	std::srand(std::time(0));
	gen.seed(std::time(0)),gen64.seed(std::time(0));
}

inline int randint(int l,int r) {
	std::uniform_int_distribution<> dis(l,r);
	return dis(gen);
}

inline long long randll(long long l,long long r) {
	std::uniform_int_distribution<long long> dis(l,r);
	return dis(gen64);
}

inline double randreal(double l=0,double r=1) {
	std::uniform_real_distribution<> dis(l,r);
	return dis(gen);
}

inline void randtree(int n,bool beginwith=1) {
	int p[n];
	for(int i=0;i<n;++i) p[i]=beginwith+i;
	std::random_shuffle(p,p+n);
	for(int i=1;i<n;++i) printf("%d %d\n",p[i],p[randint(0,i-1)]);
}

inline void randweightedtree(int n,int wl,int wr,bool beginwith=1) {
	int p[n];
	for(int i=0;i<n;++i) p[i]=beginwith+i;
	std::random_shuffle(p,p+n);
	for(int i=1;i<n;++i) printf("%d %d %d\n",p[i],p[randint(0,i-1)],randint(wl,wr));
}
