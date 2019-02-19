//BSGS
//POJ 2417

#include <bits/stdc++.h>
#define inline inline __attribute__((always_inline))
using namespace std;

typedef long long ll;
int p,b,n;
unordered_map<int,int> m;

int main() {
	//freopen("1.in","r",stdin);
	//freopen("1.ans","w",stdout);
	
	//b ^ x = n (mod p)
	while(scanf("%d%d%d",&p,&b,&n)==3) {
		if(n==1) {
			puts("0");
			continue;
		}
		/*
		assume x = u*sp - v (0 < u <= sp,0 <= v < sp)
		b ^ (u*sp) = n * b^v
		to minimize u*sp - v just enumerate all u increasingly and find corresponding maximum v
		*/
		int sp=ceil(sqrt(p)),val,t;
		//insert all n * b^v
		//it is obvious that m storages maximum v corresponding to subscript
		val=1; m.clear();
		for(int v=0;v<sp;++v,val=(val*1ll*b)%p) m[(val*1ll*n)%p]=v;
		//enumerate all u
		t=val;
		for(int u=1;u<=sp;++u,val=(val*1ll*t)%p) if(m.count(val)) {
			printf("%d\n",u*sp-m[val]);
			goto nextloop;
		}
		puts("no solution");
		nextloop:;
	}
	
	return 0;
}

