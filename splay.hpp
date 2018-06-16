/*
TLsLib - version WIP 0.1
template struct Splay
*/
#include <stack>
#include <cstring>
#include <cstdlib>

template <class datatype>
struct Splay {
	static const size_t Msize=1e5+5;
	std::stack<int> p;
	struct spnode {
		int fa,sz,cnt,son[2];
		datatype d;
		inline void clear() {son[0]=son[1]=fa=sz=cnt=0;}
		inline spnode() {clear();}
	}t[Msize];
	int rt;
	
	inline void clear() {
		rt=0; t[0].clear();
		while(!p.empty()) p.pop();
		for(int i=1;i<Msize;++i) p.push(i);
	}
	inline Splay() {clear();}
	inline int newnode(int x) {
		int ret=p.top(); p.pop();
		t[ret].clear(),t[ret].fa=x,t[ret].cnt=t[ret].sz=1;
		return ret;
	}
	inline int sonid(int x) {return t[t[x].fa].son[1]==x;}
	inline void updnode(int x) {t[x].sz=t[t[x].son[0]].sz+t[t[x].son[1]].sz+t[x].cnt;}
	inline void rotate(int x) {
		int f=t[x].fa,id=sonid(x);
		if(t[f].fa) t[t[f].fa].son[sonid(f)]=x;
		t[x].fa=t[f].fa,t[f].fa=x;
		if(t[x].son[id^1]) t[t[x].son[id^1]].fa=f;
		t[f].son[id]=t[x].son[id^1],t[x].son[id^1]=f;
		updnode(f),updnode(x);
	}
	inline void splay(int x,int T=0) {
		int f=t[x].fa;
		for(;f!=T;f=t[x].fa) {
			if(t[f].fa!=T) rotate(sonid(x)==sonid(f) ? f : x);
			rotate(x);
		}
		if(T==0) rt=x;
	}
	inline int insert(const datatype& d) {
		if(rt==0) {
			rt=newnode(0),t[rt].cnt=t[rt].sz=1,t[rt].d=d;
			return 1;
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
				t[y].d=d;
				updnode(f),splay(y);
				return y;
			}
		}
	}
	inline int getrank(const datatype& d) {
		int x=rt,ret=0;
		while(t[x].d!=d) {
			if(d>t[x].d) ret+=t[t[x].son[0]].sz+t[x].cnt;
			x=t[x].son[d>t[x].d];
		}
		splay(x);
		return ret+1;
	}
	inline datatype findrank(int r) {
		int x=rt,tmp=t[t[x].son[0]].sz+t[x].cnt;
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
		return (x ? x : -1);
	}
	inline int prev(int p) {
		if(t[p].son[0]==0) return -1;
		p=t[p].son[0];
		while(t[p].son[1]) p=t[p].son[1];
	}
	inline int next(int p) {
		if(t[p].son[1]==0) return -1;
		p=t[p].son[1];
		while(t[p].son[0]) p=t[p].son[0];
	}
	inline void erase(int x) {
		if(t[x].cnt==0) return;
		splay(x);
		if(t[x].cnt>1) --t[x].cnt;
		else if(!t[x].son[0]||!t[x].son[1]) {
			if(t[x].son[0]) rt=t[x].son[0];
			else rt=t[x].son[1];
			t[x].clear(),p.push(x);
			if(t[x].son[0]+t[x].son[1]==0) rt=0;
		}
		else {
			int y=prev(x); splay(y);
			t[t[x].son[1]].fa=y,t[y].son[1]=t[x].son[1];
			updnode(y);
			t[x].clear(),p.push(x);
		}
	}
	//data access : get precursor , get successor
	inline datatype prec(const datatype& d) {
		int x=insert(d),y=prev(x);
		erase(x);
		if(y==-1) return t[0].d;
		return t[y].d;
	}
	inline datatype succ(const datatype& d) {
		int x=insert(d),y=next(x);
		erase(x);
		if(y==-1) return t[0].d;
		return t[y].d;
	}
};

int main() {
	return 0;
}
