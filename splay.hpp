/*
TLsLib - version WIP 0.1
template struct Splay
*/
#include <algorithm>
#include <stack>
#include <cstring>

template <class datatype>
struct Splay {
	static const int Msize=1e5+5;
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
		for(int i=1;i<Msize;++i) p.push(i);
	}
	inline Splay() {clear();}
	inline int newnode(int x) {
		int ret=p.top(); p.pop();
		t[ret].clear(),t[ret].fa=x,t[ret].cnt=t[ret].sz=1;
		return ret;
	}
	inline int sonid(int x) {return t[t[x].fa].son[1]==x;}
	inline void updnode(int x) {
		if(x==0) return;
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
		int f=t[x].fa;
		for(;f!=T;f=t[x].fa) {
			if(t[f].fa!=T) rotate(sonid(x)==sonid(f) ? f : x);
			rotate(x);
		}
		if(T==0) rt=x;
	}
	inline void insert(const datatype& d) {
		if(rt==0) {
			rt=1,t[1].d=d;
			return;
		}
		int x=rt,f=0;
		while(1) {
			if(t[x].d==d) {
				++t[x].cnt;
				updnode(x),updnode(f),splay(x);
				return;
			}
			f=x,x=t[f].son[d>t[f].d];
			if(x==0) {
				int y=(t[f].son[d>t[f].d]=newnode(f));
				t[y].d=d;
				updnode(f),splay(y);
				return;
			}
		}
	}
};

int main() {
	return 0;
}
