//exBSGS
//bzoj2480

#include <bits/stdc++.h>
#define inline inline __attribute__((always_inline))
using namespace std;

void exgcd(int a,int b,int &x,int &y) {
	if(b==0) {
		x=1,y=0;
		return;
	}
	exgcd(b,a%b,y,x);
	y-=(a/b)*x;
}

inline int gcd(int a,int b) {
	int ret=1;
	while(a&&b) {
		if(a<b) swap(a,b);
		if((a&1)==(b&1)) {
			if(a&1) a=(a-b)/2; //odd odd
			else ret*=2,a/=2,b/=2; //even even
		}
		else if(a&1) b/=2; //odd even
		else a/=2; //even odd
	}
	return ret*max(a,b);
}

//a^x = b (mod p)
inline int bsgs(int a,int b,int p) {
	a%=p,b%=p;
	if(b==1) return 0;
	static unordered_map<int,int> m;
	int t=ceil(sqrt(p)),val=1,at;
	//x = ut - v
	//a^ut = b * a^v
	//u in (0,t] v in [0,t)
	m.clear();
	for(int v=0;v<t;++v,val=(val*1ll*a)%p) m[(val*1ll*b)%p]=v;
	at=val;
	for(int u=1;u<=t;++u,val=(val*1ll*at)%p) if(m.count(val)) return u*t-m[val];
	return -1;
}

//a^x = b (mod p)
inline int exbsgs(int a,int b,int p) {
	if(b==1) return 0;
	int cnt=0,rx=1,ry,c=1;
	//a^x = b (mod p) <-> a/d * a^(x-1) = b/d (mod p/d)
	for(int d=gcd(a,p);d!=1;d=gcd(a,p)) {
		if(b%d) return -1;
		b/=d,p/=d,++cnt;
		c=(c*1ll*(a/d))%p;
		if(c==b) return cnt;
	}
	//(a^cnt)/D * a^(x-cnt) = b/D (mod p/D)
	exgcd(c,p,rx,ry);
	return bsgs(a,(b*1ll*rx)%p+p,p)+cnt;
}

int main() {
	//freopen("1.in","r",stdin);
	//freopen("1.ans","w",stdout);
	
	int a,b,p,x;
	while(scanf("%d%d%d",&a,&p,&b)) {
		if(p==0) return 0;
		x=exbsgs(a,b,p);
		if(x==-1) puts("No Solution");
		else printf("%d\n",x);
	}
	
	return 0;
}

