 #include<stdlib.h>
#include<stdio.h>
#define MAX 10000
//THUAT TOAN SAP XEP
int N;
int a[MAX];
int b;

void gen_data(char*FILE_NAME,int N){
	FILE*f=fopen(FILE_NAME,"w");
	fprintf(f," %d ",N);
	fprintf(f,"\n");
	for(int i=1;i<=N;i++){
		//a[i]=rand()%100+1;
		fprintf(f,"%d ",rand()%100+1);
	}
	fclose(f);
}

void input(char*FILE_NAME){
	FILE*f=fopen(FILE_NAME,"r");
	fscanf(f,"%d",&N);
	for(int i=1;i<=N;i++){
		fscanf(f,"%d",&a[i]);
	}
	fclose(f);
}

void heapify(int i,int N){
	int L=2*i;
	int R=2*i+1;
	int max=i;
	if(L<=N&&a[L]>a[max]) max=L;
	if(R<=N&&a[R]>a[max]) max=R;
	if(max!=i){
		int tmp=a[max];
		a[max]=a[i];
		a[i]=tmp;
		heapify(max,N);
	}
}

void build_heap(){
	for(int i=N/2;i>=1;i--){
		heapify(i,N);
	}
}

void heap_sort(){
	build_heap();
	for(int i=N;i>=2;i--){
		int tmp=a[i];
		a[i]=a[1];
		a[1]=tmp;
		heapify(1,i-1);
	}
}

void algo1(){
	int cnt=0;
	for(int i=1;i<=N;i++){
		for(int j=i+1;j<=N;j++){
			if(a[i]+a[j]==b) cnt++;
		}
	}
	printf("\nalgo1: %d",cnt);
}

int Bsearch(int L,int R,int b){
	if(L>R) return 0;
	if(L==R){
		if(a[L]==b) return 1;
		else return 0;
	}
	int mid=(L+R)/2;
	if(a[mid]==b) return 1+Bsearch(L,mid-1,b)+Bsearch(mid+1,R,b);
	if(a[mid]<b) return Bsearch(mid+1,R,b);
	return Bsearch(L,mid-1,b);
}

void algo2(){
	int cnt=0;
	for(int i=1;i<=N;i++){
		cnt=cnt+Bsearch(i+1,N,b-a[i]);
	}
	printf("\nalgo2: %d",cnt);
}

void algo3(){
	int h=1;
	int t=N;
	int cnt=0;
	while(h<t){
		int cnth=1;
		int cntt=1;
		if(a[h]+a[t]==b){
			while(a[h]==a[h+1]){
				h++;
				cnth++;
			}
			while(a[t]==a[t-1]){
				t--;
				cntt++;
			}
			if(h<t){
				cnt=cnt+cntt*cnth;
			}
			else{
				cnt=cnt+cnth*(cntt-1)/2;
			}
			h++;
			t--;
		}
		else if(a[h]+a[t]>b){
			t--;
		}
		else{
			h++;
		}
	}
	printf("\nalgo3: %d",cnt);
}

int main(){
	b=100;
//	gen_data("Searching.txt",10000);
	input("Searching.txt");
	heap_sort();
//	algo1();
//	algo2();
	algo3();
}