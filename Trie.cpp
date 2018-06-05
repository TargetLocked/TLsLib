/*
TLsLib - version WIP 0.1
template class Trie
template class octalTrie

deprecated :
template class hash4Trie
*/
#include <cstdlib>
#include <cstring>

template<int card,int SZ>
struct Trie {
	struct nodeType {
		int ne[card],val;
		inline nodeType() {val=0;}
		inline void clear() {memset(ne,255,sizeof(ne)); val=0;}
	}nd[SZ];
	size_t sz;
	inline Trie() {nd[0].clear(); sz=0;}
	inline void clear() {for(unsigned int i=0;i<=sz;++i) nd[i].clear(); sz=0;}
	
	template<class InputIterator>
	inline void insert(InputIterator st,InputIterator ed,const int& val) {
		int Node=0;
		for(;st!=ed;Node=nd[Node].ne[*(st++)])
			if(nd[Node].ne[*st]==-1) {
				nd[Node].ne[*st]=++sz;
				nd[sz].clear();
			}
		nd[Node].val=val;
	}
	template<class InputIterator,class Function>
	inline void insert(InputIterator st,InputIterator ed,Function fn,const int& val) {
		int Node=0;
		for(;st!=ed;Node=nd[Node].ne[fn(*(st++))])
			if(nd[Node].ne[fn(*st)]==-1) {
				nd[Node].ne[fn(*st)]=++sz;
				nd[sz].clear();
			}
		nd[Node].val=val;
	}
	
	template<class InputIterator>
	inline int find(InputIterator st,InputIterator ed) const {
		int Node=0;
		for(;st!=ed;Node=nd[Node].ne[*(st++)])
			if(nd[Node].ne[*st]==-1) return -1;
		return nd[Node].val;
	}
	template<class InputIterator,class Function>
	inline int find(InputIterator st,InputIterator ed,Function fn) const {
		int Node=0;
		for(;st!=ed;Node=nd[Node].ne[fn(*(st++))])
			if(nd[Node].ne[fn(*st)]==-1) return -1;
		return nd[Node].val;
	}
};

template<int maxsize>
struct octalTrie {
	static const int nilval=-2147483647;
	struct nodeType {
		int ne[8],val;
		inline nodeType() {val=0;}
		inline void clear() {memset(ne,255,sizeof(ne)); val=0;}
	}nd[maxsize+2];
	size_t size;
	inline octalTrie() {nd[0].clear(); nd[1].clear(); size=1;}
	inline void clear() {for(unsigned int i=0;i<=size;++i) nd[i].clear(); size=1;}
	
	inline void insert(int key,int val) {
		int Node=(key<0);
		key=abs(key);
		for(;key;Node=nd[Node].ne[key&7],key>>=3)
			if(nd[Node].ne[key&7]==-1) {
				nd[Node].ne[key&7]=++size;
				nd[size].clear();
			}
		nd[Node].val=val;
	}
	
	inline int find(int key) const {
		int Node=(key<0);
		key=abs(key);
		for(;key;Node=nd[Node].ne[key&7],key>>=3)
			if(nd[Node].ne[key&7]==-1) return nilval;
		return nd[Node].val;
	}
};

//deprecated
template<int Size,typename DataType,DataType nilval>
struct hashTrie4 {
	const int l[5]={7,41,127,233,1};
	static const int L=8492617; // product
	struct dataContType {
		int val;
		dataContType* bro;
		DataType datum;
		inline void clear() {datum(nilval),val=-1,bro=NULL;}
		inline dataContType() {datum(nilval),val=-1,bro=NULL;}
	}br[Size+1];
	
	struct nodeType {
		int* ne;
		int bran;
		dataContType* pt;
		inline nodeType() {pt=NULL;}
		inline void createBranch(const int k) {bran=k; ne=new int[k];}
		inline ~nodeType() {delete []ne; pt=NULL;}
		inline void clear() {memset(ne,255,bran*sizeof(int)); pt=NULL;}
	}nd[((long long)Size<<2)>L ? L : ((long long)Size<<2) +1];
	
	size_t sz,bn;
	inline hashTrie4() {nd[0].createBranch(l[0]); nd[0].clear(); sz=bn=0;}
	inline void clear() {
		nd[0].clear(); for(unsigned int i=1;i<=sz;++i) ~nd[i];
		for(unsigned int i=1;i<=bn;++i) br[i].clear();
		sz=bn=0;
	}
	
	inline void insert(const int val,const DataType& datum) {
		int Node=0;
		for(int i=0,p=val%l[0];i<4;Node=nd[Node].ne[p],p=val%l[++i])
			if(nd[Node].ne[p]==-1) {
				nd[Node].ne[p]=++sz;
				nd[sz].createBranch(l[i+1]);
				nd[sz].clear();
			}
		if(nd[Node].pt==NULL) {
			nd[Node].pt=&br[++bn];
			br[bn].val=val;
			br[bn].datum=datum;
		}
		else {
			dataContType* d=nd[Node].pt;
			for(;d->val!=val&&d->bro!=NULL;d=d->bro);
			if(d->val==val) {
				d->datum=datum;
			}
			else {
				d->bro=&br[++bn];
				br[bn].val=val;
				br[bn].datum=datum;
			}
		}
	}
	
	inline DataType find(const int val) const {
		int Node=0;
		for(int i=0,p=val%l[0];i<4;Node=nd[Node].ne[p],p=val%l[++i])
			if(nd[Node].ne[p]==-1) return nilval;
		if(nd[Node].pt==NULL) return nilval;
		else {
			dataContType* d=nd[Node].pt;
			for(;d->val!=val&&d->bro!=NULL;d=d->bro);
			if(d->val==val) return d->datum;
			else return nilval;
		}
	}
};