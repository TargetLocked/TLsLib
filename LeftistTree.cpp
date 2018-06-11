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
		t[loc].ls=t[loc].rs=t[loc].dep=t[loc].sz=0;
		return loc;
	}
	//merge b into a
	int merge(int a,int b) {
		if(a==0||b==0) return a+b;
		if(t[a].d>t[b].d) std::swap(a,b); //root has the minimum value
		t[a].rs=merge(t[a].rs,b);
		if(t[t[a].ls].dep<t[t[a].rs].dep) std::swap(t[a].ls,t[a].rs);
		t[a].dep=t[t[a].rs].dep+1;
		t[a].sz=t[t[a].ls].sz+t[t[a].rs].sz+1;
		return a;
	}
	inline void insert(const datatype& d) {
		if(treesz==0) {
			t[rt].d=d;
			treesz=1;
			return;
		}
		int loc=newnode();
		t[loc].d=d;
		rt=merge(rt,loc);
	}
	inline datatype top() {return t[rt].d;}
	inline void pop() {
		if(t[rt].ls==0&&t[rt].rs==0) t[rt].sz=0;
		else q.push(rt),rt=merge(t[rt].ls,t[rt].rs);
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
	int rt[Msize];
	
	inline int& operator[](const int k) {return rt[k];}
	inline void clear() {
		t[0].dep=-1;
		for(unsigned i=1;i<Msize;++i) q.push(i);
		std::memset(rt,0,sizeof(rt));
	}
	inline LeftistTreeForest() {clear();}
	inline int size(int a) {return t[rt[a]].sz;}
	inline bool empty(int a) {return t[rt[a]].sz==0;}
	inline int newnode() {
		int loc=q.front(); q.pop();
		t[loc].ls=t[loc].rs=t[loc].dep=t[loc].sz=0;
		return loc;
	}
	int auxmerge(int a,int b) {
		if(a==0||b==0) return a+b;
		if(t[a].d>t[b].d) std::swap(a,b); //root has the minimum value
		t[a].rs=auxmerge(t[a].rs,b);
		if(t[t[a].ls].dep<t[t[a].rs].dep) std::swap(t[a].ls,t[a].rs);
		t[a].dep=t[t[a].rs].dep+1;
		t[a].sz=t[t[a].ls].sz+t[t[a].rs].sz+1;
		return a;
	}
	//merge b into a
	inline void merge(int a,int b) {
		rt[a]=auxmerge(rt[a],rt[b]);
	}
	inline void insert(int a,const datatype& d) {
		if(t[rt[a]].sz==0) {
			t[rt[a]].d=d;
			t[rt[a]].sz=1;
			return;
		}
		int loc=newnode();
		t[loc].d=d;
		rt[a]=auxmerge(rt[a],loc);
	}
	inline datatype top(int a) {return t[rt[a]].d;}
	inline void pop(int a) {
		if(t[rt[a]].ls==0&&t[rt[a]].rs==0) t[rt[a]].sz=0;
		else q.push(rt[a]),rt[a]=auxmerge(t[rt[a]].ls,t[rt[a]].rs);
	}
	inline void newtree(int a) {rt[a]=newnode();}
};

