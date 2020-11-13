#include<stdio.h>
#include<math.h>

#define k 101

int main(){
	
	int m[k][k],x,y,l,c,n=0,nm=0,a=0,b=0;
	
	scanf("%i",&n);
	
	for(x=0;x<=n;x++){
		for(y=0;y<=n;y++){
			scanf("%i",&m[x][y]);
		}
	}
	
	for(x=0;x<n;x++){
		for(y=0;y<n;y++){
			if(m[x][y]==1){b++;}
			if(m[x+1][y]==1){b++;}
			if(m[x][y+1]==1){b++;}
			if(m[x+1][y+1]==1){b++;}
			if(b>=2){printf("S");}
			else{printf("U");}
		}
		printf("\n");
	}
	
	return 0;
}