//线性基 最大异或和子集 loj113

#include <bits/stdc++.h>
#define inline inline __attribute__((always_inline))
using namespace std;

typedef long long ll;
const int N=55;
namespace lb {
	ll a[N];
	inline void insert(ll x) {
		for(int i=50;i>=0;--i) {
			if(x&(1ll<<i)) {
				if(a[i]) x^=a[i];
				else {
					for(int j=0;j<i;++j) if(x&(1ll<<j)) x^=a[j];
					for(int j=i+1;j<=50;++j) if(a[j]&(1ll<<i)) a[j]^=x;
					a[i]=x;
					return;
				}
			}
		}
	}
	inline ll query() {
		ll ret=0;
		for(int i=0;i<=50;++i) ret^=a[i];
		return ret;
	}
}

int main() {
	//freopen("1.in","r",stdin);
	//freopen("1.ans","w",stdout);
	
	int n; scanf("%d",&n);
	while(n--) {
		ll tmp; scanf("%lld",&tmp);
		lb::insert(tmp);
	}
	printf("%lld\n",lb::query());
	
	return 0;
}

