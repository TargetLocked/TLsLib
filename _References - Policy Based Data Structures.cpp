#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

struct myhash {
	typedef unsigned long long ull;
	ull mogic=chrono::high_resolution_clock::now().time_since_epoch().count();
	myhash() {ull *p=new ull; mogic^=*p; delete p;}
	unsigned operator()(int x) {return x^mogic;}
};

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
typedef gp_hash_table<int,int,myhash,equal_to<int>,direct_mod_range_hashing<int>,linear_probe_fn<>,
	hash_standard_resize_policy<hash_prime_size_policy,hash_load_check_resize_trigger<true>, true>> hash_table;

