//min25筛
//loj 6053
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N=1e5+5,zqm=1e9+7;
int id1[N],id2[N],pr[N],pn;
ll v[N*2],g[N*2],h[N*2],n,m,pre[N];
bool isp[N];

int sub(ll k) {return k<=m ? id1[k] : id2[n/k];}
void preproc() {
	int cnt=0;
	for(ll i=1,j=n;i<=n;++i,j=n/i) {
		if(j<=m) id1[j]=++cnt;
		else id2[n/j]=++cnt;
		v[cnt]=j;
		g[cnt]=(((j+2)%zqm)*1ll*((j-1)%zqm)%zqm*1ll*((zqm+1)/2))%zqm,h[cnt]=j-1;
		i=n/j;
	}
	for(int i=1;i<=pn&&pr[i]<=m;++i) {
		int t=sub(pr[i]-1);
		for(int j=1;j<=cnt&&pr[i]*1ll*pr[i]<=v[j];++j) {
			g[j]=(g[j]-((g[sub(v[j]/pr[i])]-g[t])%zqm*1ll*pr[i])%zqm+zqm)%zqm;
			h[j]-=h[sub(v[j]/pr[i])]-h[t];
		}
	}
}

ll sum(ll x,int k) {
	if(x<=1||pr[k]>x) return 0;
	ll res=(g[sub(x)]-h[sub(x)]-pre[k-1]+2ll*zqm)%zqm;
	if(k==1) res+=2;
	for(int i=k;i<=pn&&pr[i]*1ll*pr[i]<=x;++i) {
		ll p=pr[i];
		for(int e=1;p*pr[i]<=x;++e,p*=pr[i]) {
			(res+=sum(x/p,i+1)*(pr[i]^e)%zqm+(pr[i]^(e+1)))%=zqm;
		}
	}
	//cerr<<x<<' '<<k<<" = "<<res<<endl;
	return res;
}

int main() {
	//freopen("1.in","r",stdin);
	//freopen("1.ans","w",stdout);
	
	memset(isp,255,sizeof(isp));
	isp[0]=isp[1]=0;
	for(int i=2;i<=N-5;++i) {
		if(isp[i]) pr[++pn]=i,pre[pn]=pre[pn-1]+i-1;
		for(int j=1;j<=pn&&pr[j]*i<=N-5;++j) {
			isp[pr[j]*i]=0;
			if(i%pr[j]==0) break;
		}
	}
	scanf("%lld",&n); m=sqrt(n);
	preproc();
	//cerr<<g[sub(n)]<<' '<<h[sub(n)]<<endl;
	printf("%lld\n",sum(n,1)+1);
	
	return 0;
}

