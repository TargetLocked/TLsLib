#include <bits/stdc++.h>
#include "rand.hpp"
#define inline inline __attribute__((always_inline))
using namespace std;

const int N=1e5+5;
int nL,nR,bstP,n,lson[N],rson[N],fa[N],d[N],cnt,p[N];

void insert(int u,int t) {
	if(d[t]<=d[u]) {
		if(lson[u]==0) {
			lson[u]=t,fa[t]=u;
		}
		else insert(lson[u],t);
	}
	else {
		if(rson[u]==0) {
			rson[u]=t,fa[t]=u;
		}
		else insert(rson[u],t);
	}
}

int main() {
	freopen("config.txt","r",stdin);
	scanf("%d%d%d",&nL,&nR,&bstP);
	fclose(stdin);
	
	freopen("in.txt","w",stdout);
	
	srand(time(0));
	n=randint(nL,nR);
	printf("%d\n",n);
	memset(d,255,sizeof(d));
	for(int i=1;i<=n;++i) d[i]=rand(),printf("%d ",d[i]);
	puts("");
	if(randint(1,100)<=bstP) {
		for(int i=1;i<=n;++i) p[i]=i;
		random_shuffle(p+1,p+1+n);
		for(int i=2;i<=n;++i) insert(p[1],p[i]),printf("%d %d\n",p[i],fa[p[i]]);
	}
	else randtree(n);
	
	return 0;
}

