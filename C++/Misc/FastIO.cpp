#include<bits/stdc++.h>
#include<limits.h>
#include <unistd.h>
using namespace std;

class FastIO {

  // First Way (Using printf and scanf):
  // You can adjust the buffer size by the following code
  setvbuf(stdin, NULL, _IOFBF, 16 * (1<<20)); // 16MB
  setvbuf(stdout, NULL, _IOFBF, 256 * (1<<10)); // 256KB

  // Second Way (Using cout and cin):
  // This method will be sufficient for most problems
  // Change 'endl' to '\n' for the buffer issue
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // You can adjust the buffer size by the following code
  char input_buffer[16 * (1<<20)]; // 16MB
  cin.rdbuf()->pubsetbuf(input_buffer, sizeof(input_buffer));
  char output_buffer[256 * (1<<10)]; // 256KB
  cout.rdbuf()->pubsetbuf(output_buffer, sizeof(output_buffer));

  // Third Way ('u' means unsigned while 'i' means integer represented by Two's Complement):
  namespace io {
	const signed IS=1<<22, OS=1<<20;
	char I[IS+1],*J=I,O[OS],*K=O;

	inline void daer(){if(J>=I+IS-64){char*p=I;do*p++=*J++;while(J!=I+IS);p[read(0,p,I+IS-p)]=0;J=I;}}
	template<int N=10,typename T=int>inline T getu(){daer();T x=0;int k=0;do x=x*10+*J-'0';while(*++J>='0'&&++k<N);++J;return x;}
	template<int N=10,typename T=int>inline T geti(){daer();bool e=*J=='-';J+=e;return(e?-1:1)*getu<N,T>();}
	inline void flush(){write(1,O,K-O);K=O;}

	template<int N=10,typename T=int>inline void putu(T n){char s[(N+7)/8*8],*p=s;int k=0;do*p++=n%10+48;while((n/=10)&&++k<N);do*K++=*--p;while(p!=s);*K++=10;if(K>=O+OS-64)flush();}
	template<int N=10,typename T=int>inline void puti(T n){if(n<0)*K++='-',n=-n;putu<N,T>(n);}
	struct f{f(){I[read(0,I,IS)]=0;}~f(){flush();}}flu;
  };
  using namespace io;
}