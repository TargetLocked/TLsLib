//Notice: unsigned
#include <cstring>
#include <utility>

#define Ru register unsigned
//using namespace std::rel_ops;
const int sz=1000;
struct BigBinary {
	bool d[sz+5];
	size_t len;
	inline BigBinary() {memset(d,0,sizeof(d));len=0;}
	inline bool iszero() {return len==1&&!d[0];}
};
