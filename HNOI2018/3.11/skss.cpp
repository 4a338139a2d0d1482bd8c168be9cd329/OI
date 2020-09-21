#include<bits/stdc++.h>
using namespace std;

const int maxabsn=1500+10,maxn=2*maxabsn,max2n=2*maxn;
int n,ans;
int asum[maxn][maxn],bsum[max2n][max2n];

int main(){
	freopen("skss.in","r",stdin);
	freopen("skss.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		char s[2];
		int x,y,a;
		scanf("%s%d%d%d",s,&x,&y,&a);
		x+=maxabsn;y+=maxabsn;a/=2;
		if(s[0]=='A'){
			int x0=x-a,x1=x+a,y0=y-a,y1=y+a;
			++asum[x0][y0];
			--asum[x0][y1];
			--asum[x1][y0];
			++asum[x1][y1];
		}
		else{
			int xx=x+y,yy=x-y+maxn;
			int x0=xx-a,x1=xx+a,y0=yy-a,y1=yy+a;
			++bsum[x0][y0];
			--bsum[x0][y1];
			--bsum[x1][y0];
			++bsum[x1][y1];
		}
	}
	for(int i=1;i<max2n;++i)
		for(int j=1;j<max2n;++j)
			bsum[i][j]+=bsum[i][j-1]+bsum[i-1][j]-bsum[i-1][j-1];
	for(int i=1;i<maxn;++i)
		for(int j=1;j<maxn;++j){
			asum[i][j]+=asum[i][j-1]+asum[i-1][j]-asum[i-1][j-1];
			if(asum[i][j]){
				ans+=4;
				continue;
			}
			int x=i+j,y=i-j+maxn;
			if(bsum[x][y])
				++ans;
			if(bsum[x][y-1])
				++ans;
			if(bsum[x+1][y])
				++ans;
			if(bsum[x+1][y-1])
				++ans;
		}
	printf("%.2f\n",ans/4.0);
	return 0;
}
