//网络流 最小费用最大流
const int inf=1061109567,ninf=-1061109568,N=500,M=1000;
int n,To[M],Ne[M],St[N],Cf[M],Re[M],dis[N],Co[M],en,cans,Ae[N];
bool inq[N];

#define source (0)
#define sink (::n+1)

inline void addarc(int u,int v,int cf,int co) {To[++en]=v,Ne[en]=St[u],St[u]=en,Cf[en]=cf,Co[en]=co;}
inline void addedge(int u,int v,int c,int co) {
	addarc(u,v,c,co); addarc(v,u,0,-co);
	Re[en-1]=en; Re[en]=en-1;
}

#define loopinc(x) ((x)==qsize ? 0 : (x)+1)
#define loopdec(x) ((x)==0 ? qsize : (x)-1)

//begin: 类dinic 最短路径增广
//dis初值为inf

int q[N<<1],Head,Tail;
const int qsize=(N<<1)-1;

inline bool spfa() {
	memset(dis,63,sizeof(dis)); memset(inq,0,sizeof(inq));
	dis[source]=0,inq[source]=1,Head=0,Tail=1; q[0]=source;
	while(Head!=Tail) {
		int u=q[Head]; Head=loopinc(Head);
		for(int i=St[u];i;i=Ne[i]) {
			if(Cf[i]>0&&dis[u]+Co[i]<dis[To[i]]) {
				dis[To[i]]=dis[u]+Co[i]; Ae[To[i]]=Re[i];
				if(inq[To[i]]) continue;
				inq[To[i]]=1;
				if(Head!=Tail&&dis[To[i]]<dis[q[Head]]) q[Head=loopdec(Head)]=To[i];
				else q[Tail]=To[i],Tail=loopinc(Tail);
			}
		}
		inq[u]=0;
	}
	return dis[sink]!=inf;
}

inline int sendflow() {
	int p=sink,f=inf;
	for(;p!=source;p=To[Ae[p]]) f=min(f,Cf[Re[Ae[p]]]);
	cans+=f*dis[sink];
	for(p=sink;p!=source;p=To[Ae[p]]) Cf[Ae[p]]+=f,Cf[Re[Ae[p]]]-=f;
	return f;
}

//ans为流量，cans为费用
inline int costflow() {
	int ans=0; cans=0;
	while(spfa()) ans+=sendflow();
	return cans;
}

//end: 类dinic 最短路径增广

//begin: zkw 最短路径增广
//dis初值为0

const int inf_=19260817<<1;
int cnt[N];

int dfs(int u,int fmax) { 
	if(u==sink) return fmax;
	int fsum=0,res; inq[u]=1;
	for(int i=St[u];i;i=Ne[i]) {
		if(Cf[i]>0&&dis[To[i]]+Co[i]==dis[u]&&!inq[To[i]]) {
			res=dfs(To[i],min(fmax-fsum,Cf[i]));
			fsum+=res,cans+=res*Co[i];
			Cf[i]-=res,Cf[Re[i]]+=res;
			if(fsum==fmax) return fsum;
		}
	}
	return fsum;
}

inline void upd(int u,int& dmin) {
	for(int i=St[u];i;i=Ne[i])
		if(Cf[i]>0&&!inq[To[i]]) dmin=min(dmin,dis[To[i]]+Co[i]-dis[u]);
}

inline bool relabel() {
	int dmin=inf_;
	upd(source,dmin); for(int i=1;i<=n;++i) if(inq[i]) upd(i,dmin);
	if(dmin==inf_) return 0;
	dis[source]+=dmin; for(int i=1;i<=n;++i) if(inq[i]) dis[i]+=dmin;
	return 1;
}

inline int costflow_zkw() {
	int ans=0,res;
	do
		do {
			memset(inq,0,sizeof(inq));
			ans+=(res=dfs(source,inf));
		} while(res);
	while(relabel());
	return ans;
}

//end: zkw 最短路径增广
