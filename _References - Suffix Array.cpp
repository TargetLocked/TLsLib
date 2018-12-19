#include <bits/stdc++.h>
#define inline inline __attribute__((always_inline))
using namespace std;

//后缀数组

const int N=4e4+5,lgN=15,inf=1061109567;
int n,str[N],sa[N],cnt[N],h[N],st[N][lgN],_d[2][N],*rk,*tmp;

inline void getsa() {
	rk=&_d[0][0],tmp=&_d[1][0];
	for(int i=1;i<=n;++i) sa[i]=i;
	for(int i=n;i<=n*2;++i) rk[i]=tmp[i]=0;
	sort(sa+1,sa+1+n,[](const int &a,const int &b) {return str[a]<str[b];});
	for(int i=1,j=1;i<=n;++i) {
		if(str[sa[i]]!=str[sa[i-1]]) j=i;
		rk[sa[i]]=j;
	}
	for(int k=1,p=0;k<n&&p<n;k*=2) {
		p=0;
		for(int i=n-k+1;i<=n;++i) tmp[++p]=i;
		for(int i=1;i<=n;++i) if(sa[i]-k>0) tmp[++p]=sa[i]-k;
		
		memset(cnt,0,sizeof(int)*(n+5));
		for(int i=1;i<=n;++i) ++cnt[rk[i]];
		for(int i=1;i<=n;++i) cnt[i]+=cnt[i-1];
		for(int i=n;i>=1;--i) sa[cnt[rk[tmp[i]]]--]=tmp[i];
		
		swap(rk,tmp);
		//p counts different rank types
		//the sa[] is sorted iff p==n
		p=0;
		for(int i=1,j=1;i<=n;++i) {
			if(tmp[sa[i-1]]!=tmp[sa[i]]||tmp[sa[i-1]+k]!=tmp[sa[i]+k]) j=i,++p;
			rk[sa[i]]=j;
		}
	}
}
	
inline void getheight() {
	memset(h,0,sizeof(int)*(n+5));
	for(int i=1;i<=n;++i) {
		int p=h[rk[i-1]]-!!(h[rk[i-1]]);
		while(str[i+p]==str[sa[rk[i]-1]+p]) ++p;
		h[rk[i]]=p;
	}
	for(int i=1;i<=n;++i) st[i][0]=h[i];
	for(int k=1;k<lgN;++k) {
		for(int i=1;i<=n;++i)
			st[i][k]=min(st[i][k-1],(i+(1<<(k-1))<=n ? st[i+(1<<(k-1))][k-1] : inf));
	}
}
	
inline int lcp(int x,int y) {
	if(x==y) return n-x+1;
	if(rk[x]>rk[y]) swap(x,y);
	x=rk[x]+1,y=rk[y]; int k=log2(y-x+1);
	return min(st[x][k],st[y-(1<<k)+1][k]);
}
