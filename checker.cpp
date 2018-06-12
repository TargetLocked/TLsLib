#include <bits/stdc++.h>
#define inline inline __attribute__((always_inline))
using namespace std;

const int N=1e5+5,M=N<<1;
int To[M],Ne[M],St[N],d[N],en,n;

inline void addedge(int u,int v) {
	To[++en]=v,Ne[en]=St[u],St[u]=en;
	To[++en]=u,Ne[en]=St[v],St[v]=en;
}

bool dfs(int u,int fa) {
	bool l=0,r=0;
	for(int i=St[u];i;i=Ne[i]) {
		if(To[i]!=fa) {
			if(d[u]>d[To[i]]) {
				if(l) return 0;
				l=1;
			}
			if(d[u]<d[To[i]]) {
				if(r) return 0;
				r=1;
			}
			if(!dfs(To[i],u)) return 0;
		}
	}
	return 1;
}

int main() {
	freopen("in.txt","r",stdin);
	
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&d[i]);
	for(int i=1,a,b;i<n;++i) scanf("%d%d",&a,&b),addedge(a,b);
	
	fclose(stdin);
	
	freopen("out.txt","r",stdin);
	freopen("result.txt","w",stdout);
	
	int rt;
	scanf("%d",&rt);
	if(rt<1||rt>n) printf("wrong answer Answer illegal");
	else if(dfs(rt,rt)) printf("okay");
	else printf("wrong answer Not a BST");
	
	fclose(stdin);
	fclose(stdout);
	
	return 0;
}

