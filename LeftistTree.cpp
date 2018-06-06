/*
TLsLib - version WIP 0.1
template struct LeftistTree
template struct LeftistTreeForest
*/
#include <algorithm>
#include <queue>
#include <cstring>

template<class datatype>
struct LeftistTree {
	static const size_t Msize=1e5;
	struct ltnode {
		int ls,rs,sz,dep;
		datatype d;
	}t[Msize];
	std::queue<int> q;
	int rt;
	#define treesz t[rt].sz
	
	inline void clear() {
		t[0].dep=-1;
		for(unsigned i=1;i<Msize;++i) q.push(i);
		rt=0;
	}
	inline LeftistTree() {clear();}
	inline int newnode() {
		int loc=q.front(); q.pop();
		t[loc].ls=t[loc].rs=t[loc].dep=0;
		t[loc].sz=1;
		return loc;
	}
	int merge(int a,int b) {
		if(a==0||b==0) return a+b;
		if(t[a].d>t[b].d) std::swap(a,b);
		t[a].rs=merge(t[a].rs,b);
		if(t[t[a].ls].dep<t[t[a].rs].dep) std::swap(t[a].ls,t[a].rs);
		t[a].dep=t[t[a].rs].dep+1;
		t[a].sz=t[t[a].ls].sz+t[t[a].rs].sz;
		return a;
	}
	inline void insert(const datatype& d) {
		int loc=newnode();
		t[loc].d=d;
		if(treesz==0) rt=1; else rt=merge(rt,loc);
	}
	inline datatype top() {return t[rt].d;}
	inline void pop() {
		q.push(rt);
		rt=merge(t[rt].ls,t[rt].rs);
	}
	inline void build(datatype* st,datatype* ed) {
		std::queue<int> q; while(!q.empty()) q.pop();
		int loc;
		for(datatype* i=st;i!=ed;++i) q.push(loc=newnode()),t[loc].d=*i;
		while(q.size()>=2) {
			int f=q.front(); q.pop();
			q.push(merge(f,q.front())); q.pop();
		}
		rt=q.front();
	}
};

template<class datatype>
struct LeftistTreeForest {
	static const size_t Msize=1e5;
	struct ltnode {
		int ls,rs,sz,dep;
		datatype d;
	}t[Msize];
	std::queue<int> q;
	int rt[Msize],tn;
	
	inline int& operator[](const int k) {return rt[k];}
	inline void clear() {
		t[0].dep=-1;
		for(unsigned i=1;i<Msize;++i) q.push(i);
		std::memset(rt,0,sizeof(rt));
	}
	inline LeftistTreeForest() {clear();}
	inline int size(int a) {return t[rt[a]].sz;}
	inline int newnode() {
		int loc=q.front(); q.pop();
		t[loc].ls=t[loc].rs=t[loc].dep=0;
		t[loc].sz=1;
		return loc;
	}
	int auxmerge(int a,int b) {
		if(a==0||b==0) return a+b;
		if(t[a].d>t[b].d) std::swap(a,b);
		t[a].rs=auxmerge(t[a].rs,b);
		if(t[t[a].ls].dep<t[t[a].rs].dep) std::swap(t[a].ls,t[a].rs);
		t[a].dep=t[t[a].rs].dep+1;
		t[a].sz=t[t[a].ls].sz+t[t[a].rs].sz;
		return a;
	}
	inline void merge(int a,int b) {
		rt[a]=auxmerge(rt[a],rt[b]);
	}
	inline void insert(int a,const datatype& d) {
		int loc=newnode();
		t[loc].d=d;
		if(t[rt[a]].sz==0) rt[a]=1; else rt[a]=auxmerge(rt[a],loc);
	}
	inline datatype top(int a) {return t[rt[a]].d;}
	inline void pop(int a) {
		q.push(rt[a]);
		rt[a]=auxmerge(t[rt[a]].ls,t[rt[a]].rs);
	}
	inline void newtree(int a=-1) {if(a==-1) a=++tn; rt[a]=newnode();}
};

