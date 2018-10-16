//动态开点线段树

#include <bits/stdc++.h>
#define inline inline __attribute__((always_inline))
using namespace std;

typedef long long LL;
const int maxn=1e5+5;
struct segnode {
	int ls,rs;
	LL sum,tag;
}t[maxn<<2];
int nn=1,n;

#define lson t[Node].ls
#define rson t[Node].rs

//Build with read
void Build(int& Node,int l,int r) {
	if(Node==0) Node=++nn;
	if(l==r) {
		scanf("%lld",&t[Node].sum);
		return;
	}
	int mid=(l+r)>>1;
	Build(lson,l,mid);
	Build(rson,mid+1,r);
	t[Node].sum=t[lson].sum+t[rson].sum;
}

inline void updlzy(int Node,int l,int r) {
	if(t[Node].tag==0||l==r) return;
	int mid=(l+r)>>1;
	if(lson==0) lson=++nn;
	t[lson].tag+=t[Node].tag,t[lson].sum+=t[Node].tag*(mid-l+1);
	if(rson==0) rson=++nn;
	t[rson].tag+=t[Node].tag,t[rson].sum+=t[Node].tag*(r-mid);
	t[Node].tag=0;
}

void Modify(int& Node,int l,int r,int L,int R,LL val) {
	if(Node==0) Node=+nn;
	updlzy(Node,l,r);
	if(L<=l&&r<=R) {
		t[Node].sum+=val*(r-l+1);
		t[Node].tag+=val;
		return;
	}
	int mid=(l+r)>>1;
	if(L<=mid) Modify(lson,l,mid,L,R,val);
	if(mid+1<=R) Modify(rson,mid+1,r,L,R,val);
	t[Node].sum=t[lson].sum+t[rson].sum;
}

LL Query(int Node,int l,int r,int L,int R) {
	if(Node==0) return 0;
	updlzy(Node,l,r);
	if(L<=l&&r<=R) return t[Node].sum;
	int mid=(l+r)>>1; LL ret=0;
	if(L<=mid) ret=Query(lson,l,mid,L,R);
	if(mid+1<=R) ret+=Query(rson,mid+1,r,L,R);
	return ret;
}

int main() {
	freopen("1.in","r",stdin);
	//freopen(".ans","w",stdout);
	
	int q;
	scanf("%d%d",&n,&q);
	LL tmp; int k=1;
	Build(k,1,n);
	int a,b,opt;
	while(q--) {
		scanf("%d%d%d",&opt,&a,&b);
		if(opt==1) {
			scanf("%lld",&tmp);
			Modify(k,1,n,a,b,tmp);
		}
		else {
			printf("%lld\n",Query(1,1,n,a,b));
		}
	}
	
	return 0;
}

