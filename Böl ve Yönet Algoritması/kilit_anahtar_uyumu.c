//Havvanur Dervisoglu-Algoritma Analizi 1.Ödev
//ödev:key dizisinden rastgele secilen anahtari lock dizisini keye göre düzenliyerek ,ve key dizisini de lock[x] e göre duzenleyerek sonra 
//özyinelemeli olarak keyden büyük key degerleri ve kücük key degerleri icinde ayni islemleri yaparak "kilit-anahtar uyumunu" bulma
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//swap islemi icin kullanacagimiz fonksiyon
//fonksiyona verilen iki degeri ,birbiriyle degistirir
void swap(int* t1, int* t2) 
{   
    int tmp = *t1; 
    *t1= *t2; 
    *t2= tmp; 
} 

//parçalama fonksiyonu her seferinde girilen key degerinin yerini dönüyor
int partition(int array[],int p,int r,int key){
	//p dizinin dusuk indisi ilk durumda 0, r ise buyuk indisidir
	//key degerine göre array dizisi duzenlenecektir
	 //i degiskeni keyden kucuk olan elemanlarin sinir inidisi,yani i.elemandan öncekiler keyden kucuk
	 //j degeri ise keyden buyuk olan elemanlarin sinir degeridir ,yani i+1 ile j-1 arasindakiler keyden buyuk
	int i=p-1,j;
	for(j=p;j<=r-1;j++){
		if(array[j]<key){
			//eger key degeri büyükse girilen dizinin j. elemanindan 
			//keyden küçük olan indisleri tutan i degerini arttir 
			//sonra küçüklerin yanina koy yani swap yapiyoruz
			i++;
			swap(&array[i], &array[j]);
			 
		}
		else if(array[j]==key){
			//eger esitse key degerine bunu son yere koy en son yani dizinin sonuna
			// diger elemanlari da kontrol devam etmek için j'yi bir azaltki degistirdigi sayiyi da kontrol edebilsin
			 swap(&array[j], &array[r]);
			 j--;
		}
	}//döngünün bitme kosulu j=r dir, döngünün sonunda dizideki bütün girdiler keyden buyuk olnlar ,keyden buyuk olanlar ve key olarak 3'e bölündü
	//artik key degerimizin yeri kucuklerden bir sonraki olarak yerini koyuyoruz
	//key degeri ondan kucukler ve ondan buyuklerin arasina yerlestiridk
	 swap(&array[i+1], &array[r]);
	 //dönus degeri keyin yeri bölmeye burdan basliycaz
	 return (i+1);
}

//key lock esleme yapamk icin fonksiyon
void key_lock_match(int lock[],int key[],int p,int r,int n){
	//key ve lock degerleri giris degeri olarak aliniyor
	//p dizinin kucuk,baslangic indisi,r ise buyuk,bitis indisi
	
	if(p<r){//özyinelemeden çikma için bu kosulu kullandim
	     
		//random olarak bir key degeri seciliyor sonrasinda lock dizisinde
		//bu key dizisinin yeri berilirleniyor
		int random=(p+ (rand() % (r - p + 1)));
	    int key_r=	key[random];
	    int i;
	    		printf("random key degeri:%d \n",key_r);

		int q=partition(lock,p,r,key_r);
		printf("\n");
		//sonra bu deger ,lock[q] key degeri key dizisndede duznleniyor
		//bu drumda key dizisinde ve lock dizisinde lock[q] ve key[rand] degerleri karsilikli
		partition(key,p,r,lock[q]);
		printf("\n");
		printf("partition key:\n");
		for( i=0;i<n;i++){
			printf("%d\t",key[i]);
		}
		printf("\n");
			printf("partition lock:\n");
		for(i=0;i<n;i++){
			printf("%d\t",lock[i]);
		}
		printf("\n");
		
		//daha sonrasinda keyden öncekiler yani kucuk olanlar arasindan anahtar secilerek özyineleme olarak cagirilarak sýralanir
		key_lock_match(lock,key,p,q-1,n);
		//keyden büyük key degeri icinde  özyinelemeli olarak siralama yapilir
		key_lock_match(lock,key,q+1,r,n);
	}
}
void array_yazdir(int arr[],int n){
	//dizi yazdirma fonksiyonu
	int i;
	for(i=0;i<n;i++){
		printf("%d\t",arr[i]);
	}
}
void array_al(int arr[],int n){
	//diziyi kullanicidan alma fonksiyonu
	int i;
	for( i=0;i<n;i++){
		scanf("%d",&arr[i]);
	}
}
int main(){
	//n burada key lock eleman sayisi
	//i döngüdegiskeni
	//key anahtar degerleri tutan array
	//lock kilit degerleri tutan array
	int n,i;
	n=6;
    int	key[6]={1,7,14,9,5,18};
    int	lock[6]={18,14,1,7,5,9};
    printf("ilk hali:\n");
	printf("ilk key::\n");
	array_yazdir(key,n);
	printf("\n");
	printf("ilk lock::\n");
	array_yazdir(lock,n);
	printf("\n");
	//N degeri kullanicidan aliniyor
/*	printf("N?\n");
	scanf("%d",&n);
	
	//key ve lock degerleri kullanicidan aliniyor
	/*printf("key?\n");
	array_al(key,n);
	printf("lock?\n");
	array_al(lock,n);*/
	
	//sonra key lock esleme yapiyoruz
	key_lock_match(lock,key,0,n-1,n);
	
	//match olan key ve lock degerlerini yazdiriyoruz
	
	printf("\nSon hali:\n");
	printf("key::\n");
	array_yazdir(key,n);
	printf("\n");
	printf("lock::\n");
	array_yazdir(lock,n);
	
	printf("\n");
	system("pause");
	return 0;
}






