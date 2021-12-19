#include<stdio.h>
#include<stdlib.h>

typedef struct bilgi{
	int musteri_no;
	char *ad;
	char *soyad;
}Musteri;

Musteri *veri_liste[10];
int hash_tablo[10][2];
int sayi,veri_sayisi=0,temp;
//**************************************************************************
	void ekle(int numara,char isim[],char soyisim[],int k)
{
	veri_sayisi++;
	sayi=numara%10;
	
	if(hash_tablo[sayi][0]==-1)
		{
			hash_tablo[sayi][0]=numara;
			k=sayi;
		}
	else
		{
		hash_tablo[k][0]=numara;	
		temp=sayi;
		while(hash_tablo[temp][1]!=-1)
			{
			temp=hash_tablo[temp][1];
			}
		hash_tablo[temp][1]=k;
		}	
				
			veri_liste[k]=(Musteri*)malloc(sizeof(Musteri));
			veri_liste[k]->musteri_no=numara;
			veri_liste[k]->ad=(char*)malloc(sizeof(char));
			for(int i=0;isim[i]!=NULL;i++) *(veri_liste[k]->ad+i)=isim[i];
			veri_liste[k]->soyad=(char*)malloc(sizeof(char));
			for(int i=0;soyisim[i]!=NULL;i++) *(veri_liste[k]->soyad+i)=soyisim[i];
	}
//**************************************************************************************************	
		int ara(int numara)
	{	
		sayi=numara%10;
			if(hash_tablo[sayi][0]==numara)
				{
				return 1;
				}
			else
			{
				temp=hash_tablo[sayi][1];
				int sayac=2,t=0;
				for(int i=0;i<veri_sayisi;i++)
				{
									
					if(hash_tablo[temp][0]==numara)
						{
							t=1;
							return sayac;	
						}
					else
						{
							sayac++;
							temp=hash_tablo[temp][1];
						}
				}
				if(t==0) return 0;	
			}
			
	}
//*******************************************************************
	void sil(int numara)
	{
		sayi=numara%10;
		if(ara(numara)==1)
		{
			hash_tablo[sayi][0]=-1;
			//free(veri_liste[sayi]);
			veri_liste[sayi]=NULL;
		}
		else if(ara(numara)==0)
		{
			printf("silmek istediginiz kayit zaten yok\n");
		}
		else
		{
			hash_tablo[temp][0]=-1;
			//free(veri_liste[temp]);
			veri_liste[temp]=NULL;
		}
	}
//**************************************************************************************		
int main()
{

	for(int i=0;i<10;i++)
	{
		veri_liste[i]=NULL;
	}
	
	//hash tablosunun ilk degerlerini atama
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<2;j++)
		{
			hash_tablo[i][j]=-1;
		}
	}
	int numara,k;
	char isim[20],soyisim[20];
	FILE*dosya;
	dosya=fopen("veri.txt","r");
	while(!feof(dosya))
	{
		fscanf(dosya,"%d",&numara);
		fscanf(dosya,"%s",isim);
		fscanf(dosya,"%s",soyisim);
		for( k=0;k<10;k++)
		{
			if(hash_tablo[k][0]==-1)
			break;
		}
		ekle(numara,isim,soyisim,k);
	}
	fclose(dosya);
	int secim;
	printf("Dosyanizdan veriler basariyla okunmustur.\n");
	do{
		printf("\n***BUYURUN MENUNUZ***\n");
		printf("1.Veri ekle\n2.Musteriyi arat\n3.Veri sil\n4.Hash Tablosunu Listele\n5.Veri Listesini Listele\n6.Butun kayitlara ulasmanin ortalama adim sayisi\n7.Exit\n");
		printf("sizin secim->>>");
		scanf("%d",&secim);
	switch(secim)
	{
		case 1: {		int t=0;	
						for(k=0;k<10;k++)
						{
							if(hash_tablo[k][0]==-1)
							{
								t=1;
								break;
							}
						}
						if(t==0)
						{
							printf("veri eklemek icin yeterli alan yoktur:/\n");
						}
						else
						{
						printf("\nmusteri numarasi giriniz:");
						scanf("%d",&numara);
						printf("musterinin adini girinz:");
						scanf("%s",isim);
						printf("musterinin soyadini giriniz:");
						scanf("%s",soyisim);
						ekle(numara,isim,soyisim,k);				
						}
						break;
				}
		case 2:{
						printf("\naratmak istediginiz musterinin numarasini giriniz:");
						scanf("%d",&numara);
						if(ara(numara)==1) 
						{
							printf("%d\t%s\t%s\n",veri_liste[sayi]->musteri_no,veri_liste[sayi]->ad,veri_liste[sayi]->soyad);
							printf("aradiginiz deger ilk (1) adimda bulundu\n");
						}
						else if(ara(numara)==0)
						{
							printf("aradiginiz deger bulunmadi\n");
						}
						else
						{
							printf("%d\t%s\t%s\n",veri_liste[temp]->musteri_no,veri_liste[temp]->ad,veri_liste[temp]->soyad);
							printf("aradiginiz deger %d adimda bulundu\n",ara(numara));
						}
		
						break;
			}
		case 3:
			{	
					printf("\nkayidini silmek istediginiz musterinin numarasini girniniz:");
					scanf("%d",&numara);
					sil(numara);
					break;
			}
		case 4:{
				
					for(int i=0;i<10;i++)
					{
						for(int j=0;j<2;j++)
						{
							printf("%d\t",hash_tablo[i][j]);
						}
						printf("\n");
					}
							break;
				}
		case 5:{
					for(int i=0;i<10;i++)
					{
						if(veri_liste[i]==NULL)printf("");
						else
						printf("%d\t%s\t%s\n",veri_liste[i]->musteri_no,veri_liste[i]->ad,veri_liste[i]->soyad);
					}
					break;
				}
		case 6:{
					double toplam=0;
					for(int i=0;i<10;i++)
					{
						toplam+=ara(hash_tablo[i][0]);
					}
					printf("tum kayitlara ortalama %.2f adimda ulasilir\n",toplam/veri_sayisi);
					break;
		}
		default:	 if(secim!=7)printf("menude olmayan bir secim yaptiniz\n"); break;
	}
			
	}while(secim!=7);
	printf("Hoscakalin:)))");
	return 0;
}
