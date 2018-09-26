/*
TLsLib - version WIP 0.1
template struct Splay
template struct SplayForest
*/
#include <stack>
#include <cstring>
#include <cstdlib>

template <class datatype>
struct Splay {
	static const size_t Msize=1e5+5;
	std::stack<int> p;
	struct spnode {
		int fa,cnt,son[2];
		size_t sz;
		datatype d;
		//change here to extend the function
		inline void clear() {son[0]=son[1]=fa=sz=cnt=0;}
		inline spnode() {clear();}
	}t[Msize];
	int rt;
	
	inline void clear() {
		rt=0; t[0].clear();
		while(!p.empty()) p.pop();
		for(unsigned i=1;i<Msize;++i) p.push(i);
	}
	inline Splay() {clear();}
	inline int newnode(int x) {
		int ret=p.top(); p.pop();
		//change here to extend the function
		t[ret].clear(),t[ret].fa=x,t[ret].cnt=t[ret].sz=1;
		return ret;
	}
	inline size_t size() {return t[rt].sz;}
	inline datatype operator[](int p) {return t[p].d;}
	inline int sonid(int x) {return t[t[x].fa].son[1]==x;}
	inline void updnode(int x) {
		//change here to extend the function
		t[x].sz=t[t[x].son[0]].sz+t[t[x].son[1]].sz+t[x].cnt;
	}
	inline void rotate(int x) {
		int f=t[x].fa,id=sonid(x);
		if(t[f].fa) t[t[f].fa].son[sonid(f)]=x;
		t[x].fa=t[f].fa,t[f].fa=x;
		if(t[x].son[id^1]) t[t[x].son[id^1]].fa=f;
		t[f].son[id]=t[x].son[id^1],t[x].son[id^1]=f;
		updnode(f),updnode(x);
	}
	inline void splay(int x,int T=0) {
		if(x==T||x==0) return;
		for(int f=t[x].fa;f!=T;f=t[x].fa) {
			if(t[f].fa!=T) rotate(sonid(x)==sonid(f) ? f : x);
			rotate(x);
		}
		if(T==0) rt=x;
	}
	inline int insert(const datatype& d) {
		if(rt==0) {
			rt=newnode(0),t[rt].d=d,updnode(rt);
			return rt;
		}
		int x=rt,f=0;
		while(1) {
			if(t[x].d==d) {
				++t[x].cnt;
				updnode(x),updnode(f),splay(x);
				return x;
			}
			f=x,x=t[f].son[d>t[f].d];
			if(x==0) {
				int y=(t[f].son[d>t[f].d]=newnode(f));
				t[y].d=d,updnode(y);
				updnode(f),splay(y);
				return y;
			}
		}
	}
	inline int getrank(const datatype& d) {
		int x=rt,ret=0;
		while(x&&t[x].d!=d) {
			if(d>t[x].d) ret+=t[t[x].son[0]].sz+t[x].cnt;
			x=t[x].son[d>t[x].d];
		}
		ret+=t[t[x].son[0]].sz;
		splay(x);
		return ret+1;
	}
	inline datatype findrank(size_t r) {
		int x=rt; size_t tmp=t[t[x].son[0]].sz+t[x].cnt;
		while(1) {
			if(r<=t[t[x].son[0]].sz) x=t[x].son[0];
			else {
				tmp=t[t[x].son[0]].sz+t[x].cnt;
				if(r<=tmp) break;
				r-=tmp,x=t[x].son[1];
			}
		}
		splay(x);
		return t[x].d;
	}
	//iterator operations : find , find previous , find next
	inline int find(const datatype& d) {
		int x=rt;
		while(x&&t[x].d!=d) x=t[x].son[d>t[x].d];
		splay(x);
		return x;
	}
	inline int prev(int x) {
		splay(x);
		if(t[x].son[0]==0) return 0;
		x=t[x].son[0];
		while(t[x].son[1]) x=t[x].son[1];
		return x;
	}
	inline int next(int x) {
		splay(x);
		if(t[x].son[1]==0) return 0;
		x=t[x].son[1];
		while(t[x].son[0]) x=t[x].son[0];
		return x;
	}
	//void erase(SplayIterator x)
	inline void erase(int x) {
		if(t[x].cnt==0) return;
		splay(x);
		if(t[x].cnt>1) {
			--t[x].cnt,updnode(x);
			return;
		}
		else if(t[x].son[0]&&t[x].son[1]) {
			int y=prev(x); splay(y);
			t[t[x].son[1]].fa=y,t[y].son[1]=t[x].son[1];
			updnode(y);
		}
		else rt=t[x].son[0]+t[x].son[1];
		t[rt].fa=0,p.push(x);
	}
	//data access : get precursor , get successor
	inline datatype prec(const datatype& d) {
		int x=insert(d),y=prev(x);
		erase(x);
		if(y==0) return t[0].d;
		return t[y].d;
	}
	inline datatype succ(const datatype& d) {
		int x=insert(d),y=next(x);
		erase(x);
		if(y==0) return t[0].d;
		return t[y].d;
	}
};

//not modified yet
template <class datatype>
struct SplayForest {
	static const size_t Msize=N<<2;
	std::stack<int> p;
	struct spnode {
		int fa,cnt,son[2];
		size_t sz;
		datatype d;
		//change here to extend the function
		inline void clear() {son[0]=son[1]=fa=sz=cnt=0;}
		inline spnode() {clear();}
	}t[Msize];
	int rt[Msize];
	
	inline void clear() {
		t[0].clear();
		std::memset(rt,0,sizeof(rt));
		while(!p.empty()) p.pop();
		for(unsigned i=1;i<Msize;++i) p.push(i);
	}
	inline SplayForest() {clear();}
	inline int newnode(int fa) {
		int ret=p.top(); p.pop();
		//change here to extend the function
		t[ret].clear(),t[ret].fa=fa,t[ret].cnt=t[ret].sz=1;
		return ret;
	}
	inline size_t size(int u) {return t[rt[u]].sz;}
	inline datatype operator[](int p) {return t[p].d;}
	inline int sonid(int x) {return t[t[x].fa].son[1]==x;}
	inline void updnode(int x) {
		//change here to extend the function
		t[x].sz=t[t[x].son[0]].sz+t[t[x].son[1]].sz+t[x].cnt;
	}
	inline void rotate(int x) {
		int f=t[x].fa,id=sonid(x);
		if(t[f].fa) t[t[f].fa].son[sonid(f)]=x;
		t[x].fa=t[f].fa,t[f].fa=x;
		if(t[x].son[id^1]) t[t[x].son[id^1]].fa=f;
		t[f].son[id]=t[x].son[id^1],t[x].son[id^1]=f;
		updnode(f),updnode(x);
	}
	inline void splay(int u,int x,int T=0) {
		if(x==0) return;
		int f=t[x].fa;
		for(;f!=T;f=t[x].fa) {
			if(t[f].fa!=T) rotate(sonid(x)==sonid(f) ? f : x);
			rotate(x);
		}
		if(T==0) rt[u]=x;
	}
	inline int insert(int u,const datatype& d) {
		if(rt[u]==0) {
			rt[u]=newnode(0),t[rt[u]].d=d,updnode(rt[u]);
			return rt[u];
		}
		int x=rt[u],f=0;
		while(1) {
			if(t[x].d==d) {
				++t[x].cnt;
				updnode(x),updnode(f),splay(u,x);
				return x;
			}
			f=x,x=t[f].son[d>t[f].d];
			if(x==0) {
				int y=(t[f].son[d>t[f].d]=newnode(f));
				t[y].d=d,updnode(y);
				updnode(f),splay(u,y);
				return y;
			}
		}
	}
	inline int getrank(int u,const datatype& d) {
		int x=rt[u],ret=0;
		while(x&&t[x].d!=d) {
			if(d>t[x].d) ret+=t[t[x].son[0]].sz+t[x].cnt;
			x=t[x].son[d>t[x].d];
		}
		ret+=t[t[x].son[0]].sz;
		splay(u,x);
		return ret+1;
	}
	inline datatype findrank(int u,int r) {
		int x=rt[u],tmp=t[t[x].son[0]].sz+t[x].cnt;
		while(1) {
			if(r<=t[t[x].son[0]].sz) x=t[x].son[0];
			else {
				tmp=t[t[x].son[0]].sz+t[x].cnt;
				if(r<=tmp) break;
				r-=tmp,x=t[x].son[1];
			}
		}
		splay(u,x);
		return t[x].d;
	}
	//iterator operations : find , find previous , find next
	inline int find(int u,const datatype& d) {
		int x=rt[u];
		while(x&&t[x].d!=d) x=t[x].son[d>t[x].d];
		splay(u,x);
		return x;
	}
	inline int prev(int p) {
		if(t[p].son[0]==0) return 0;
		p=t[p].son[0];
		while(t[p].son[1]) p=t[p].son[1];
		return p;
	}
	inline int next(int p) {
		if(t[p].son[1]==0) return 0;
		p=t[p].son[1];
		while(t[p].son[0]) p=t[p].son[0];
		return p;
	}
	//void erase(SplayIterator x)
	inline void erase(int u,int x) {
		if(t[x].cnt==0) return;
		splay(u,x);
		if(t[x].cnt>1) {
			--t[x].cnt,updnode(x);
			return;
		}
		else if(t[x].son[0]&&t[x].son[1]) {
			int y=prev(x); splay(u,y);
			t[t[x].son[1]].fa=y,t[y].son[1]=t[x].son[1];
			updnode(y);
		}
		else rt[u]=t[x].son[0]+t[x].son[1];
		t[rt[u]].fa=0,p.push(x);
	}
	//data access : get precursor , get successor
	inline datatype prec(int u,const datatype& d) {
		int x=insert(u,d),y=prev(x);
		erase(u,x);
		if(y==0) return t[0].d;
		return t[y].d;
	}
	inline datatype succ(int u,const datatype& d) {
		int x=insert(u,d),y=next(x);
		erase(u,x);
		if(y==0) return t[0].d;
		return t[y].d;
	}
};
