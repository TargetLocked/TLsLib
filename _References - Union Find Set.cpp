
namespace ufs {
	int fa[N],rk[N];
	int Find(int u) {return fa[u]==0 ? u : fa[u]=Find(fa[u]);}
	inline void Union(int u,int v) {
		u=Find(u),v=Find(v);
		if(u==v) return;
		if(rk[u]<=rk[v]) {
			fa[u]=v;
			if(rk[u]==rk[v]) ++rk[v];
		}
		else fa[v]=u;
	}
	inline void clear() {memset(fa,0,sizeof(fa)),memset(rk,0,sizeof(rk));}
}
