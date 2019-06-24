//网络流 最大流

const int inf=1061109567,N=500,M=1000;
int n,To[M],Ne[M],St[N],Cf[M],Re[M],dis[N],cnt[N],en;
int q[N<<1],Head,Tail;

#define source (0)
#define sink (n+1)

inline void addarc(int u,int v,int cf) {To[++en]=v,Ne[en]=St[u],St[u]=en,Cf[en]=cf;}
inline void addedge(int u,int v,int c) {
	addarc(u,v,c); addarc(v,u,0);
	Re[en-1]=en; Re[en]=en-1;
}

//begin: sap最大流
//dis初值为0

//先bfs标号可以提速
inline void bfs() {
	Head=0,Tail=1;
	q[Tail]=sink;
	while(Head!=Tail) {
		int sou=q[++Head];
		for(int i=St[sou];i;i=Ne[i]) {
			if(Cf[Re[i]]>0&&dis[To[i]]==0&&To[i]!=sink) {
				++cnt[dis[To[i]]=dis[sou]+1]; --cnt[0];
				q[++Tail]=To[i];
			}
		}
	}
}

int sap(int u,int fmax) { 
	if(u==sink) return fmax;
	int dmin=n,fsum=0,res;
	for(int i=St[u];i;i=Ne[i]) {
		if(Cf[i]>0&&dis[To[i]]+1==dis[u]) {
			res=sap(To[i],min(fmax-fsum,Cf[i]));
			fsum+=res;
			Cf[i]-=res,Cf[Re[i]]+=res;
			if(dis[source]>=n||fsum==fmax) return fsum;
		}
		if(Cf[i]>0) dmin=min(dmin,dis[To[i]]);
	}
	if(fsum==0) {
		if((--cnt[dis[u]])==0) dis[source]=n;
		else ++cnt[(dis[u]=dmin+1)];
	}
	return fsum;
}

inline int maxFlow_sap() {
	int ans=0;
	while(dis[source]<n) ans+=sap(source,inf);
	return ans;
}

//end: sap最大流

//begin: dinic最大流
//dis初值为-1

inline bool bfs() {
	Head=0,Tail=1;
	memset(dis,255,sizeof(dis));
	q[Tail]=sink; dis[sink]=0;
	while(Head!=Tail) {
		int sou=q[++Head];
		for(int i=St[sou];i;i=Ne[i]) {
			if(Cf[Re[i]]>0&&dis[To[i]]==-1) {
				dis[To[i]]=dis[sou]+1;
				q[++Tail]=To[i];
			}
		}
	}
	return dis[source]!=-1;
}

int Cu[N];

int dfs(int u,int fmax) {
	if(u==sink) return fmax;
	int fsum=0,res;
	for(int &i=Cu[u];i;i=Ne[i]) {
		if(Cf[i]>0&&dis[To[i]]+1==dis[u]) {
			res=dfs(To[i],min(fmax-fsum,Cf[i]));
			fsum+=res;
			Cf[i]-=res,Cf[Re[i]]+=res;
			if(fsum==fmax) return fsum;
		}
	}
	return fsum;
}

inline int maxFlow_dinic() {
	int ans=0;
	while(bfs()) {
		memcpy(Cu,St,sizeof(Cu));
		for(int res=233;res;ans+=(res=dfs(source,inf)));
	}
	return ans;
}

//end: dinic最大流
