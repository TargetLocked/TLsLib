//miller-rabin
//luogu P1835

#include <bits/stdc++.h>
#define inline inline __attribute__((always_inline))
using namespace std;

typedef unsigned ui;

inline ui qp(ui base,ui exp,ui zqm) {
	ui ret=1;
	for(;exp;exp/=2,base=(base*1ll*base)%zqm) if(exp&1) ret=(ret*1ll*base)%zqm;
	return ret;
}

inline bool millerrabin(ui x) {
	static const ui pr[]={2,7,61};
	if(x<2) return 0;
	ui y=x-1; while(!(y&1)) y/=2;
	for(ui base:pr) {
		if(x==base) return 1;
		else if(x%base==0) return 0;
		ui i=qp(base,y,x),j=y;
		for(;j<x;i=(i*1ll*i)%x,j*=2) if((i*1ll*i)%x==1&&i!=1&&i!=x-1) return 0;
		if(i!=1) return 0;
	}
	return 1;
}

int main() {
	//freopen("1.in","r",stdin);
	//freopen("1.ans","w",stdout);
	
	ui l,r,ans=0;
	scanf("%u%u",&l,&r);
	for(ui i=l+!(l&1);i<=r;i+=2) {
		ans+=millerrabin(i);
		//if(millerrabin(i)) printf("%u\n",i);
	}
	//puts("");
	printf("%u\n",ans+(l<=2&&2<=r));
	
	return 0;
}
