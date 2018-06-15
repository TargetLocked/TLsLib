/*
TLsLib - version WIP 0.1
class Fraction
*/
#include <utility>
#include <cmath>

typedef unsigned long long ull;
typedef long long LL;
//using namespace std::rel_ops;
struct Fraction {
	ull p,q;
	bool neg;
	static inline ull gcd(ull a,ull b) {
		while(b^=a^=b^=a=a%b);
		return a;
	}
	// initialization
	inline void clear() {p=0,q=1;}
	// constructor
	inline Fraction& simplify() {
		ull x=gcd(p,q);
		if(x==1) return *this;
		p/=x,q/=x;
		return *this;
	}
	inline Fraction() {clear();}
	inline Fraction(LL a,LL b) {p=abs(a),q=abs(b); simplify(); neg=(a^b)<0;}
	inline Fraction(LL a) {p=a,q=1; neg=(a<0);}
	// functional functions
	
	// arithmetic operators
	inline Fraction operator* (const Fraction& rhs) const {return Fraction(p*rhs.p,q*rhs.q);}
	inline Fraction operator/ (const Fraction& rhs) const {return Fraction(p*rhs.q,q*rhs.p);}
	// relational operators
	inline bool operator <(const Fraction& rhs) const {return p*rhs.q<rhs.p*q;}
	inline bool operator ==(const Fraction& rhs) const {return p*rhs.q==rhs.p*q;}
};

//signed (implement using LL instead of ull)
struct Fraction_ {	
	LL p,q;
	static inline LL gcd(LL a,LL b) {
		while(b^=a^=b^=a=a%b);
		return a;
	}
	// initialization
	inline void clear() {p=0,q=1;}
	// constructor
	inline Fraction& simplify() {
		LL x=gcd(p,q);
		if(x==1) return *this;
		p/=x,q/=x;
		return *this;
	}
	inline Fraction() {clear();}
	inline Fraction(LL a,LL b) {p=a,q=b; simplify();}
	inline Fraction(LL a) {p=a,q=1;}
	// functional functions
	
	// arithmetic operators
	inline Fraction operator* (const Fraction& rhs) const {return Fraction(p*rhs.p,q*rhs.q);}
	inline Fraction operator/ (const Fraction& rhs) const {return Fraction(p*rhs.q,q*rhs.p);}
	// relational operators
	inline bool operator <(const Fraction& rhs) const {return p*rhs.q<rhs.p*q;}
	inline bool operator ==(const Fraction& rhs) const {return p*rhs.q==rhs.p*q;}
};
