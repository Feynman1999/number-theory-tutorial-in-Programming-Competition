#define Mo 1000007
int test,mo,a,b,g,cnt,size,hcnt,re,phi,now,x,y,G;
int p[20],ans[40000],Ans[40000],tans[40000];
int acnt,Acnt,tacnt;
int prime[5000],head[Mo];
bool vis[31760];
struct hmap{
	int num,k,next;
}h[40000];
inline int read(){
    int ret=0;char c=getchar();
    while((c>'9')||(c<'0'))c=getchar();
    while((c>='0')&&(c<='9'))ret=(ret<<1)+(ret<<3)+c-'0',c=getchar();
    return ret;
}
inline int Pow(int x,int k){
	int ans=1;
	for(;k;k>>=1,x=1LL*x*x%mo)if(k&1)ans=1LL*ans*x%mo;
	return ans;
}
inline int exgcd(int a,int b,int &x,int &y){
	if(a==0){y=1;x=0;return b;}
	int tmp=b/a,d=exgcd(b%a,a,y,x);
	x-=tmp*y;
	return d;
}
inline int find(int x){
	for(int i=2;;i++)if(i%x){
		bool ok=true;
		for(int j=1;j<=cnt;j++)if(Pow(i,phi/p[j])==1){ok=false;break;}
		if(ok)return i;
	}
}
void ins(int k,int x){
	int key=x%Mo;
	h[++hcnt]=(hmap){x,k,head[key]};
	head[key]=hcnt;
}
inline int query(int x){
	int key=x%Mo;
	for(int i=head[key];i;i=h[i].next)if(h[i].num==x)return h[i].k;
	return -1;
}
void solve(int p){
	if(p%G!=0)return;
	else{
		p/=G;
		int tmp=Pow(g,phi/G),w=Pow(g,1LL*x*p%(phi/G));
		for(int i=0;i<G;i++,w=1LL*w*tmp%mo)Ans[++Acnt]=w;
	}
}
void bsgs(int x){
	size=int(sqrt(phi)+0.0000001);int w=1,gi=Pow(g,phi-size);
	for(int i=0;i<size;i++){
		ins(i,w);
		w=1LL*w*g%mo;
	}
	w=x;
	for(int i=0;i<=phi;i+=size){
		int tmp=query(w);
		if(tmp!=-1){
			w=1;hcnt=0;
			for(int j=0;j<size;j++)head[w%Mo]=0,w=1LL*w*g%mo;
			solve(i+tmp);
			return;
		}
		w=1LL*w*gi%mo;
	}
}
void work(int a,int b,int pr,int s){
	mo=1;
	for(int i=1;i<=s;i++)mo*=pr;b%=mo;
	if(b%pr==0){
		if(b==0)
			for(int i=1,S=pr;i<=s;i++,S*=pr)if(i*a>=s){
				for(int j=0;j<mo/S;j++)Ans[++Acnt]=j*S;
				break;
			}
		else{
			int ts=0;while(b%pr==0)b/=pr,ts++;
			if(ts%a==0){
				work(a,b,pr,s-ts);int S=1;
				for(int j=1;j<=ts/a;j++)S*=pr;
				for(int j=1;j<=Acnt;j++)Ans[i]*=S;
			}
		}
		return;
	}
	phi=mo/pr*(pr-1);a%=phi;
	if((pr==2)&&(s>2)){
		phi/=2;
		if(b%4==3){
			if(a%2==0)return;
			g=5;b=mo-b;G=exgcd(a,phi,x,y);if(x<0)x+=phi/G;
			bsgs(b);
			tacnt=0;
			for(int i=1;i<=Acnt;i++)if(Ans[i]%4==1)tans[++tacnt]=Ans[i];
			Acnt=tacnt;
			for(int i=1;i<=Acnt;i++)Ans[i]=mo-tans[i];
		}else{
			g=5;G=exgcd(a,phi,x,y);if(x<0)x+=phi/G;
			bsgs(b);
			if(a%2==0){
				int tmp=Acnt;
				for(int i=1;i<=tmp;i++)Ans[++Acnt]=mo-Ans[i];
			}
		}
		return;
	}
	int tmp=pr-1;cnt=0;
	for(int i=1;prime[i]*prime[i]<=tmp;i++)if(tmp%prime[i]==0){
		p[++cnt]=prime[i];
		while(tmp%prime[i]==0)tmp/=prime[i];
	}
	if(tmp>1)p[++cnt]=tmp;
	if(s>2)p[++cnt]=pr;
	g=find(pr);G=exgcd(a,phi,x,y);if(x<0)x+=phi/G;
	bsgs(b);
}
void merge(int Pow){
	tacnt=0;
	exgcd(now,Pow,x,y);
	for(int i=1;i<=acnt;i++)
		for(int j=1;j<=Acnt;j++)tans[++tacnt]=(1LL*x*(Ans[j]-ans[i])%Pow+Pow)%Pow*now+ans[i];
	acnt=tacnt;for(int i=1;i<=tacnt;i++)ans[i]=tans[i];now*=Pow;
}
int main(){
	for(int i=2;i<=31700;i++){
		if(!vis[i])prime[++cnt]=i;
		for(int j=1;(j<=cnt)&&(prime[j]*i<=31700);j++){
			int k=prime[j]*i;
			vis[k]=true;
			if(i%prime[j]==0)break;
		}
	}
	test=read();
	while(test--){
		mo=read();a=read();b=read();size=int(sqrt(mo)+0.0000001);
		//x^a = b(mod mo)
		now=1;acnt=1;ans[1]=0;
		int tmp=mo;
		for(int i=1;(prime[i]*prime[i]<=tmp)&&(acnt);i++)if(tmp%prime[i]==0){
			int s=0,S=1;
			while(tmp%prime[i]==0)tmp/=prime[i],s++,S*=prime[i];
			Acnt=0;
			work(a,b,prime[i],s);merge(S);
		}
		if((tmp>1)&&(acnt))Acnt=0,work(a,b,tmp,1),merge(tmp);
		if(acnt){
			sort(ans+1,ans+1+acnt);
			for(int i=1;i<=acnt;i++)printf("%d ",ans[i]);
			puts("");
		}else puts("No Solution");
	}
}
