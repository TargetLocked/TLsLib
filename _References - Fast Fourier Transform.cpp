//FFT 多项式乘法 luogu3803

#include <bits/stdc++.h>
#define inline inline __attribute__((always_inline))
using namespace std;

const int N=4e6+5;
struct Complex {
	typedef double floatTp;
	floatTp r,i;
	inline Complex(const floatTp& r=0,const floatTp& i=0):r(r),i(i) {}
	inline Complex operator+(const Complex& rhs) const {return Complex(r+rhs.r,i+rhs.i);}
	inline Complex operator-(const Complex& rhs) const {return Complex(r-rhs.r,i-rhs.i);}
	inline Complex operator*(const Complex& rhs) const {return Complex(r*rhs.r-i*rhs.i,r*rhs.i+i*rhs.r);}
	inline Complex conj() const {return Complex(r,-i);}
};

int n;
Complex u[N];
const double pi=acos(-1);

inline void getomega(int f) {
	//with f = -1 will get omega.conj()
	u[0]=Complex(1),u[1]=Complex(cos(2*pi/n),sin(2*pi/n)*f);
	for(int i=2;i<n;++i) u[i]=u[i-1]*u[1];
}

Complex a[N],b[N],c[N];
inline void fft(Complex* a) {
	int k=__builtin_ctz(n);
	//bit inverse
	for(int i=0;i<n;++i) {
		int t=0;
		for(int j=0;j<k;++j) if(i&(1<<j)) t|=(1<<(k-j-1));
		if(i<t) swap(a[i],a[t]);
	}
	//iterate solve
	//since DFT on a single element equals to itself , iterate length from 2 to n
	for(int l=2;l<=n;l<<=1) {
		int h=l>>1; //half the length , i.e. previous iteration length
		for(Complex* p=a;p!=a+n;p+=l) {
			for(int i=0;i<h;++i) {
				//omega(l,i) = omega(n,i*n/l)
				//p[h+i] = A_1(i)
				Complex t=u[n/l*i]*p[h+i];
				p[h+i]=p[i]-t;
				p[i]=p[i]+t;
			}
		}
	}
}

inline int read() {
	char c=getchar(); bool neg=(c=='-');
	while(!('0'<=c&&c<='9')) c=getchar(),neg|=(c=='-');
	int ret=0;
	for(;'0'<=c&&c<='9';c=getchar()) ret=ret*10+c-48;
	return neg ? -ret : ret;
}

int main() {
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	
	int n=read(),m=read();
	++n,++m;
	for(int i=0;i<n;++i) a[i]=Complex(read());
	for(int i=0;i<m;++i) b[i]=Complex(read());
	//for(int i=0;i<n;++i) printf("%.2lf ",a[i].r);puts("");
	//for(int i=0;i<m;++i) printf("%.2lf ",b[i].r);puts("");
	::n=1;
	while((::n)<n+m) (::n)<<=1;
	getomega(1);
	fft(a); fft(b);
	//for(int i=0;i<(::n);++i) printf("(%.2lf,%.2lf) ",a[i].r,a[i].i); puts("");
	//for(int i=0;i<(::n);++i) printf("(%.2lf,%.2lf) ",b[i].r,b[i].i); puts("");
	for(int i=0;i<(::n);++i) c[i]=a[i]*b[i];
	getomega(-1);
	fft(c);
	//for(int i=0;i<(::n);++i) printf("(%.2lf,%.2lf) ",c[i].r,c[i].i); puts("");
	for(int i=0;i<n+m-1;++i) printf("%d ",(int)floor(0.5+c[i].r/(::n)));
	
	return 0;
}
