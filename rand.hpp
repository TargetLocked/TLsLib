/*
TLsLib - version WIP 0.1
random auxiliary library
*/
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <random>

std::mt19937 gen;
std::mt19937_64 gen64;

void randinit(size_t seed=std::time(0)) {
	std::srand(seed);
	gen.seed(seed),gen64.seed(seed);
}

int randint(int l,int r) {
	std::uniform_int_distribution<> dis(l,r);
	return dis(gen);
}

long long randll(long long l,long long r) {
	std::uniform_int_distribution<long long> dis(l,r);
	return dis(gen64);
}

double randreal(double l=0,double r=1) {
	std::uniform_real_distribution<> dis(l,r);
	return dis(gen);
}

void randtree(int n,bool beginwith=1) {
	int p[n];
	for(int i=0;i<n;++i) p[i]=beginwith+i;
	std::random_shuffle(p,p+n);
	for(int i=1;i<n;++i) printf("%d %d\n",p[i],p[randint(0,i-1)]);
}

void randweightedtree(int n,int wl,int wr,bool beginwith=1) {
	int p[n];
	for(int i=0;i<n;++i) p[i]=beginwith+i;
	std::random_shuffle(p,p+n);
	for(int i=1;i<n;++i) printf("%d %d %d\n",p[i],p[randint(0,i-1)],randint(wl,wr));
}
