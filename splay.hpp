/*
TLsLib - version WIP 0.1
template struct Splay
*/
#include <algorithm>
#include <queue>
#include <cstring>

template <class datatype>
struct Splay {
	const int Msize=1e5+5;
	std::queue<int> q;
	struct spnode {
		int fa,sz,cnt,son[2];
		inline void clear() {ls=rs=fa=sz=cnt=0;}
		inline spnode() {clear();}
	}t[Msize];
	inline int sonid(int k) {return t[t[k].fa].son[1]==k;}
	
}
