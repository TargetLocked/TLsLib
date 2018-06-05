/*
TLsLib - version WIP 0.1
template class Treap
*/
#include <cstdlib>

template<class dataType>
class Treap {
	struct nodeType {
		nodeType *l,*r;
		dataType d;
		int size,wg,fix;
		inline void clear() {l=r=NULL; d(); size=wg=fix=0;}
		inline nodeType() {clear();}
		inline int lsize() {return l==NULL ? 0 : l->size;}
		inline int rsize() {return r==NULL ? 0 : r->size;}
	};
	nodeType* root;
	inline Treap() {root=new nodeType;}

public:
	//rotate
	friend inline void leftRotate(nodeType*& u) {
		nodeType* t=u->r;
		u->r=t->l; t->l=u;
		u=t;
		t=u->left;
		t->size=t.lsize()+t.rsize()+t.wg;
		u->size=u.lsize()+u.rsize()+u.wg;
	}
	friend inline void rightRotate(nodeType*& u) {
		nodeType* t=u->l;
		u->l=t->r; t->r=u;
		u=t;
		t=u->right;
		t->size=t.lsize()+t.rsize()+t.wg;
		u->size=u.lsize()+u.rsize()+u.wg;
	}
	//insert
	inline nodeType* insert(nodeType*& u,const dataType& d) {
		if(u==NULL) {
			u=new nodeType;
			u->d(d);
			u->wg=1,u->size=1,u->fix=rand();
			return u;
		}
		if(u->d==d) {
			++u->wg; ++u->size;
			return u;
		}
		else {
			nodeType* ret;
			if(d<u->d) {
				ret=insert(u->l,d);
				if(u->fix>u->l->fix) rightRotate(u);
			}
			else {
				ret=insert(u->r,d);
				if(u->fix>u->r->fix) leftRotate(u);
			}
			return ret;
		}
	}
	//find	
	inline nodeType* find(const dataType& d) {
		nodeType* u=root;
		while(u!=NULL&&u->d!=d) {
			if(d<u->d) u=u->l;
			else u=u->r;
		}
		return u;
	}
	
	inline nodeType** find_ptr(const dataType& d) {
		nodeType* u=root; nodeType** ret;
		while(u!=NULL&&u->d!=d) {
			ret=&u;
			if(d<u->d) u=u->l;
			else u=u->r;
		}
		return ret;
	}
	//erase
	inline void erase(nodeType*& u,const dataType& d) {
		if(u==NULL) return;
		if(u->d==d) {
			if(u->l==NULL||u->r==NULL) {
				nodeType* t=u;
				if(u->l!=NULL) u=u->l; else u=u->r;
				delete t;
			}
			else {
				if(u->l->fix<u->r->fix) {
					rightRotate(u);
					erase(u->r);
				}
				else {
					leftRotate(u);
					erase(u->l);
				}
			}
		}
		else {
			if(d<u->d) erase(u->l,d);
			else erase(u->r,d);
		}
	}
	//findrank
	inline nodeType* findrank(nodeType* u,const int r) {
	}
};