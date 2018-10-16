//NTT 多项式乘法

#include <bits/stdc++.h>
#define inline inline __attribute__((always_inline))
using namespace std;

typedef long long LL;
const int N=4e6+5;
const LL zqm=(17ll<<27ll)+1,g=3;

inline LL qp(LL base,LL exp) {
	LL ret=1;
	for(;exp;base=(base*base)%zqm,exp>>=1) if(exp&1) ret=(ret*base)%zqm;
	return ret;
}
inline LL inv(LL x) {return qp(x,zqm-2);}

int n;
LL u[N];
inline void getomega(int exp) {
	u[0]=1,u[1]=qp(g,(zqm-1)/(LL)n);
	for(int i=2;i<n;++i) u[i]=(u[i-1]*1ll*u[1])%zqm;
	if(exp==-1) {
		for(int i=1;i<n;++i) u[i]=inv(u[i]);
	}
}

inline void ntt(LL* a) {
	int k=__builtin_ctz(n);
	//bit inverse
	for(int i=0;i<n;++i) {
		int t=0;
		for(int j=0;j<k;++j) if(i&(1<<j)) t|=(1<<(k-j-1));
		if(i<t) swap(a[i],a[t]);
	}
	//main procedure
	for(int l=2;l<=n;l<<=1) {
		int h=l>>1;
		for(LL* p=a;p!=a+n;p+=l) {
			for(int i=0;i<h;++i) {
				LL t=(u[n/l*i]*p[h+i])%zqm;
				p[h+i]=(p[i]-t+zqm)%zqm;
				p[i]=(p[i]+t)%zqm;
			}
		}
	}
}

LL a[N],b[N],r[N];

int main() {
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	
	int n1,n2;
	scanf("%d%d",&n1,&n2);
	++n1,++n2;
	for(int i=0;i<n1;++i) scanf("%lld",&a[i]);
	for(int i=0;i<n2;++i) scanf("%lld",&b[i]);
	n=1;
	while(n<n1+n2) n<<=1;
	getomega(1);
	ntt(a); ntt(b);
	for(int i=0;i<n;++i) r[i]=a[i]*b[i]%zqm;
	getomega(-1);
	ntt(r);
	LL in=inv(n);
	for(int i=0;i<n1+n2-1;++i) printf("%lld ",r[i]*in%zqm);
	
	return 0;
}

//NTT 多项式乘法
