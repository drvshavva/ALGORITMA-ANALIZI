//problem : dinamik programlamayla verilen slogandaki kelimeleri her satir en fazla M karakter olacak sekilde satirlara yerlestirmek
//havanur dervioglu
#include<stdio.h>
#include <limits.h> 
#include<stdlib.h>
#include<string.h>
#define INF INT_MAX 
#define SIZE 100
//len kelimelerin uzunluklarinin tutuldugu dizi
//n kac tane kelime var stringte onun sayisi
//m ise her satirda en fazla kaç karakter olabilir onun sayisi
int yazdir(int lineAdr[],int n);
char *words[SIZE];
void DP(int len[],int n,int m)
{
	//space bir satirda i den j ye kelime yazinca -aralarinda bir boslukla- kalan bosluk sayisi
	//spaceCost bir satirda i den j ye kelime yazinca bu satirdaki bosluk bedeli
	//cost ise her satirin hangi kelime ile baslamasi durumda minimum bedel
	int space[n+1][n+1],spaceCost[n+1][n+1],cost[n+1];
	int lineAdr[n+1];//her satir kacinci kelime ile baslayacak onun tutuldugu dizi
	int i,j;//input stringte ki kelimelerin indisi
	
	//satir sonuna kalan bosluk hesabi
	for(i=1;i<=n;i++)
	{
		space[i][i]=m-len[i-1];
		for(j=i+1;j<=n;j++)
			space[i][j]=space[i][j-1]-len[j-1]-1;
	}
	printf("Space matrisi:\n");
	for(i=1;i<=n;i++)
	{  
	    j=0;
        while(j<i-1) {	
		j++;
        printf("-\t");
		}
    	for(j=i;j<=n;j++)
    	{
    		printf("%d\t",space[i][j]);
		}
    	printf("\n");
	}
	//spaceCost matrisi
	for(i=1;i<=n;i++)
	{
		for(j=i;j<=n;j++)
		{
			if(space[i][j]<0) 
			 	spaceCost[i][j]=INF;
			else if (j == n &&  space[i][j] >= 0) 
                spaceCost[i][j] = 0; 
			else 
				spaceCost[i][j]=space[i][j]*space[i][j]*space[i][j];
		}	
	}
	printf("\nSpaceCost matrisi:\n");
	for(i=1;i<=n;i++)
	{  
	    j=0;
        while(j<i-1) {	
		j++;
        printf("-\t");
		}
    	for(j=i;j<=n;j++)
    	{   
		    if(spaceCost[i][j]==INF) printf("INF\t");
    		else printf("%d\t",spaceCost[i][j]);
		}
    	printf("\n");
	}
	//cost degerinin hesaplanmasi
	cost[0]=0;
	for(j=1;j<=n;j++)
	{
		cost[j]=INF;
		for(i=1;i<=j;i++)
		{
			if(cost[i-1]!=INF && spaceCost[i][j]!=INF && cost[j]>cost[i-1]+spaceCost[i][j]){
				cost[j]=cost[i-1]+spaceCost[i][j];
				lineAdr[j]=i;
			}
		}
		
	}
	
	printf("\nCost dizisi:\n");
	for(i=0;i<=n;i++) printf("%d\t",cost[i]);
	printf("\n\nToplam bosluk bedeli: %d\n",cost[n]);
	printf("\nLineAdr dizisi:\n");
	for(i=1;i<=n;i++) printf("%d\t",lineAdr[i]);
	printf("\n");
	printf("\nSonuc:\n\n");
	yazdir(lineAdr,n);

}
int yazdir(int lineAdr[],int n)
{
	int line,i;
	if(lineAdr[n]==1) 
	    line=1;
	else
		line=yazdir(lineAdr,lineAdr[n]-1)+1;
    for(i=lineAdr[n]-1;i<n;i++) printf("%s ",words[i]);
    printf("\n");
	return line;
}
void main()
{
	int len[SIZE];
    char str[] = "Lorem Ipsum is simply dummy text of the printing and typesetting industry.";
    int n=0,i,m=15,count=0;
   //ilk kelime 
    char *kelime ;
	kelime = strtok(str, ",;. "); 
    
    //str bitene kadar kelimeleri ayikla
    while (kelime != NULL) 
    { 	
    	words[n]=kelime;
		len[n] = strlen(kelime);	
		n++;
		kelime = strtok(NULL, " "); 
    } 
    printf("Stringteki kelimelerin uzunlugu:\n");
    for( i=0;i<n;i++){
    	printf(" %d\t",len[i]);
	}
    printf("\nstringteki toplam kelime sayisi=%d\n",n);
    printf("Stringteki kelimeler:\n");
    for( i=0;i<n;i++){
    	printf(" %s\n",words[i]);
	}
	printf("\n");
    DP(len,n,m);
    system("pause");
}
