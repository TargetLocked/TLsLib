#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

template<class Int>
struct myhash {
	unsigned mogic=chrono::high_resolution_clock::now().time_since_epoch().count();
	myhash() {unsigned *p=new unsigned; mogic^=*p; delete p;}
	unsigned operator()(Int x) const {
		x=x^(x>>32)*233^(x>>48)*2333;
		return x^mogic;
	}
};

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
typedef gp_hash_table<int,int,myhash<int>,equal_to<int>,direct_mod_range_hashing<int>,linear_probe_fn<>,
	hash_standard_resize_policy<hash_prime_size_policy,hash_load_check_resize_trigger<true>,true>> hash_table;
		//replacement: hash_exponential_size_policy<>

