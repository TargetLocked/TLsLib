/*
TLsLib - version WIP 0.1
template class myque (deque)
*/

template<class T>
struct myque {
	static const size_t qs=N;
	size_t head,tail;
	T q[qs+5];
	
	static size_t loopinc(size_t x) {return x==qs ? 0 : x+1;}
	static size_t loopdec(size_t x) {return x==0 ? qs : x-1;}
	
	myque():head(0),tail(0) {}
	
	bool empty() const {return head==tail;}
	size_t size() const {return (tail+qs-head)%qs;}
	void clear() {head=tail=0;}
	
	void pushfront(T x) {q[head=loopdec(head)]=x;}
	void pushback(T x) {q[tail]=x,tail=loopinc(tail);}
	
	void popfront() {head=loopinc(head);}
	void popback() {tail=loopdec(tail);}
	
	T front() const {return q[head];}
	T back() const {return q[loopdec(tail)];}
};
