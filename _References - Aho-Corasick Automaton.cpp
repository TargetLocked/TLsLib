//AC自动机 子串计数

#include <bits/stdc++.h>
#define inline inline __attribute__((always_inline))
using namespace std;

const int N=1e6+5,M=233;
struct inpt {
	int cnt;
	char str[M];
}d[M];
char str[N];
struct eniac_automaton {
	struct tn {
		int ne[26],ptr,suf,dsuf;
	}t[M*M];
	int nn;
	
	inline eniac_automaton() {fill(t[0].ne,t[0].ne+26,1),nn=1;}
	inline int newnode() {
		++nn;
		memset(t[nn].ne,0,sizeof(t[nn].ne));
		t[nn].ptr=t[nn].suf=t[nn].dsuf=0;
		return nn;
	}
	inline void clear() {nn=0,newnode();}
	
	inline void insert(char *str,int id) {
		int u=1;
		for(int *v;*str!='\0';++str) {
			v=&t[u].ne[*str-'a'];
			if(*v==0) *v=newnode();
			u=*v;
		}
		t[u].ptr=id;
	}
	
	//optimized using Knuth's idea
	//excluding node 0, it's a DFA
	inline void getsuf() {
		static queue<int> q;
		q.push(1);
		while(!q.empty()) {
			int u=q.front(); q.pop();
			for(int i=0,v;i<26;++i) {
				v=t[u].ne[i];
				if(v!=0) {
					q.push(v);
					t[v].suf=t[t[u].suf].ne[i];
					t[v].dsuf=(t[t[v].suf].ptr ? t[v].suf : t[t[v].suf].dsuf);
				}
				else t[u].ne[i]=t[t[u].suf].ne[i];
			}
		}
	}
	
	inline void query(char *str) {
		int u=1;
		for(;*str!='\0';++str) {
			for(int v=u;v;v=t[v].dsuf) ++d[t[v].ptr].cnt;
			u=t[u].ne[*str-'a'];
		}
		for(int v=u;v;v=t[v].dsuf) ++d[t[v].ptr].cnt;
	}
}s;

int main() {
	//freopen("1.in","r",stdin);
	//freopen("1.ans","w",stdout);
	
	for(int n;scanf("%d",&n),n;) {
		s.clear();
		for(int i=1;i<=n;++i) {
			scanf("%s",d[i].str),d[i].cnt=0;
			s.insert(d[i].str,i);
		}
		s.getsuf();
		scanf("%s",str);
		s.query(str);
		int mx=0;
		for(int i=1;i<=n;++i) mx=max(mx,d[i].cnt);
		printf("%d\n",mx);
		for(int i=1;i<=n;++i) if(d[i].cnt==mx) puts(d[i].str);
	}
	
	return 0;
}
