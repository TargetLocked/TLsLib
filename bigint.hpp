/*
TLsLib - version WIP 0.1
class BigInt(unsigned)
*/
#include <cstdio>
#include <cstring>
#include <utility>

#define Ru register unsigned
#define Rc register char
const int w=10000;
const size_t SZ=1000;
//using namespace std::rel_ops;
struct BigInt {
	int d[SZ+5];
	size_t len;
	// initialization
	inline void clear() {memset(d,0,sizeof(d)); len=0;}		
	// constructor
	inline BigInt() {clear();}
	inline BigInt(unsigned long long k) {
		clear(); len=(k==0);
		for(;k;k/=w) d[len++]=k%w;
	}
	// arithmetic operators
	inline BigInt& operator =(const BigInt& rhs) {
		memcpy(d,rhs.d,sizeof(d)); len=rhs.len;
		return *this;
	}
	inline BigInt operator +(const BigInt& rhs) const {
		BigInt res=*this; Ru i;
		for(i=0;i<rhs.len;++i) res.d[i]+=rhs.d[i];
		if(rhs.len>res.len) res.len=rhs.len;
		for(i=0;i<res.len;++i)
			if(res.d[i]>=w) {
				res.d[i+1]+=res.d[i]/w;
				res.d[i]%=w;
			}
		if(res.d[res.len]) ++res.len;
		return res;
	}
	inline BigInt& operator +=(const BigInt& rhs) {
		(*this)=(*this)+rhs;
		return *this;
	}
	inline BigInt operator -(const BigInt& rhs) const {
		BigInt res=*this; Ru i;
		for(i=0;i<rhs.len;++i) res.d[i]-=rhs.d[i];
		for(i=0;i<res.len;++i)
			if(res.d[i]<0) {
				res.d[i]+=w;
				--res.d[i+1];
			}
		while(res.len&&res.d[res.len-1]==0) --res.len;
		return res;
	}
	inline BigInt& operator -=(const BigInt& rhs) {
		(*this)=(*this)-rhs;
		return *this;
	}
	inline BigInt operator /(const unsigned& rhs) const {
		if(len<=1) return (BigInt)(d[0]/rhs);
		BigInt res; Ru i; unsigned long long r=0;
		for(i=len;i;--i) {
			r=r*w+d[i-1];
			res.d[i-1]=r/rhs;
			r%=rhs;
		}
		for(res.len=len;!res.d[res.len-1];) --res.len;
		return res;
	}
	inline BigInt& operator /=(const unsigned& rhs) {
		(*this)=(*this)/rhs;
		return *this;
	}
	// relational operators
	inline bool operator <(const BigInt& rhs) const {
		if(len!=rhs.len) return len<rhs.len;
		for(Ru i=rhs.len;i;--i) if(d[i-1]!=rhs.d[i-1]) return d[i-1]<rhs.d[i-1];
		return 0;
	}
	inline bool operator ==(const BigInt& rhs) const {
		if(len!=rhs.len) return 0;
		for(Ru i=rhs.len;i;--i) if(d[i-1]!=rhs.d[i-1]) return 0;
		return 1;
	}
	// I/O operations
	inline void write() const {
		if(len==0) {putchar(48); return;}
		printf("%d",d[len-1]);
		for(Ru i=len-1;i;--i) printf("%04d",d[i-1]);
	}
	inline bool read() {
		//return value : iszero()
		memset(d,0,sizeof(d)); len=1;
		Rc c=getchar(); Ru i,k=1;
		while(!('0'<=c&&c<='9')) c=getchar();
		for(;'0'<=c&&c<='9';++k,c=getchar()) {
			d[0]=(d[0]<<3)+(d[0]<<1)+c-48;
			if(k>=5) {
				for(i=0;i<len;++i) {
					d[i+1]=(d[i+1]<<3)+(d[i+1]<<1)+d[i]/w;
					d[i]%=w;
				}
				if(d[len]) ++len;
			}
		}
		return len==1&&!d[0];
	}
	// functional functions
	inline bool isodd() const {return len&&(d[0]&1);}
	inline bool iszero() const {return len==1&&d[0]==0;}
	inline BigInt distance(const BigInt& b) const {if(b<(*this)) return (*this)-b; else return b-(*this);}
};
