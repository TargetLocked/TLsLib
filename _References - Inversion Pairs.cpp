//begin: 归并求逆序对数

long long ans;
void mergesort(int l,int r) {
	static int tmp[N];
	if(l>=r) return;
	int mid=(l+r)>>1;
	mergesort(l,mid); mergesort(mid+1,r);
	int pl=l,pr=mid+1,pt=l;
	while(pl<=mid&&pr<=r) {
		if(d[pl]<d[pr]) tmp[pt++]=d[pl++];
		else {
			ans+=mid-pl+1;
			tmp[pt++]=d[pr++];
		}
	}
	while(pl<=mid) tmp[pt++]=d[pl++];
	while(pr<=r) tmp[pt++]=d[pr++];
	for(pt=l;pt<=r;++pt) d[pt]=tmp[pt];
}

//end: 归并求逆序对数