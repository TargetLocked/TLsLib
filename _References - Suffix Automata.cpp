#include <bits/stdc++.h>
#define inline inline __attribute__((always_inline))
using namespace std;

//后缀自动机

constexpr int N=1e6+5,C=26;
struct samnode {
	//cnt表示|end-pos|
	int suf,ne[C],max,cnt;
}t[N*2];
char str[N];
int nn,last,n;

inline void expand(int c) {
	int u=++nn,v=last;
	t[u].max=t[v].max+1,t[u].cnt=1;
	for(;v&&t[v].ne[c]==0;v=t[v].suf) t[v].ne[c]=u;
	int w=t[v].ne[c];
	if(v==0) t[u].suf=1;
	else if(t[w].max==t[v].max+1) t[u].suf=w;
	else {
		int r=++nn; t[r]=t[w];
		t[r].max=t[v].max+1,t[r].cnt=0;
		t[u].suf=t[w].suf=r;
		for(;v&&t[v].ne[c]==w;v=t[v].suf) t[v].ne[c]=r;
	}
	last=u;
}

int p[N*2];
inline void topsort() {
	static int cnt[N*2];
	for(int u=1;u<=nn;++u) ++cnt[t[u].max];
	for(int i=1;i<=n;++i) cnt[i]+=cnt[i-1];
	for(int u=1;u<=nn;++u) p[cnt[t[u].max]--]=u;
}

int main() {
	//freopen("1.in","r",stdin);
	//freopen("1.ans","w",stdout);
	
	scanf("%s",str+1);
	n=strlen(str+1),nn=last=1;
	for(int i=1;i<=n;++i) expand(str[i]-'a');
	topsort();
	for(int i=nn;i>=1;--i) t[t[p[i]].suf].cnt+=t[p[i]].cnt;
	long long ans=0;
	for(int u=1;u<=nn;++u) if(t[u].cnt!=1) {
		ans=max(ans,t[u].cnt*1ll*t[u].max);
	}
	printf("%lld\n",ans);
	
	return 0;
}
