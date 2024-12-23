/**
* @file Proje1.c
* @description Bu dosya, birim ve çalışanlar için gerekli olan temel işlemleri gerçekleştiren fonksiyonların tanımlarını içerir. 
* Çalışan ekleme, birim oluşturma, maaş güncelleme, ve uzun süreli çalışanlara zam yapma gibi işlemler burada kodlanmıştır.
* @assignment 1. Ödev
* @date 23 Aralık 2024
* @author Sema Nur ÖZGEN - semanur.ozgen@stu.fsm.edu.tr
*/

#include "Proje1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//yeni biriem olusturalimm
Birim yeniBirim(const char *birimAdi,unsigned short int birimKodu){
    Birim birim;
    strcpy(birim.birimAdi,birimAdi);
    birim.birimKodu = birimKodu;
    birim.birimCalisanlar = NULL; //Başlangıçta calışan yoktur
    birim.calisanSayisi = 0;
    return birim;
}

Calisan yeniCalisan(const char *adi,const char *soyadi,unsigned short int birimKodu,float maas,int girisYili){
    Calisan calisan;
    strcpy(calisan.calisanAdi,adi);
    strcpy(calisan.calisanSoyadi,soyadi);
    calisan.birimKodu = birimKodu;
    calisan.maas = maas;
    calisan.girisYili= girisYili;
    return calisan;
}


// calisan eklemek için fonksiyonumuz
void calisanEkle(Calisan **calisanlar,Calisan yeniCalisan,int *calisanSayisi){
    //normalde malloc ile bi yer ayırdık ama yeni çalışan eklemek istediğimizde bunu realloc ile güncellememiz lazım
    *calisanlar = (Calisan *)realloc(*calisanlar,(*calisanSayisi + 1)*sizeof(Calisan));

    if(*calisanlar == NULL){ //eğer realloc başarızsız olursa diye bu if kısmını yazdık
        printf("Bellek tahsisi basarisiz !\n");
        exit(1); //olası bir hatada bu programi sonlamdırmak için bunu yazdık
    }

    //yeni calisanlar ekliyoruz
    (*calisanlar)[*calisanSayisi] = yeniCalisan;
    (*calisanSayisi)++;  //calisan sayisini arttırıyoruz 
}

float ortalamaMaasHesapla(Birim birim) {
    if (birim.calisanSayisi == 0) {
        printf("Birimde hic calisan yok");
        return 0.0f; //ort maas sıfırr
    }
    float toplamMaas = 0.0f;
    for (int i = 0; i < birim.calisanSayisi; i++) {
        toplamMaas += birim.birimCalisanlar[i].maas;
    }
    float ortalama  = toplamMaas / birim.calisanSayisi;
    return ortalama;
}

//ort üstü alan zenginleri listeleyen fonksiyon
void ortalamaUstuMaasAlanlariListele(Birim *birimler,int birimSayisi){
 for (int i = 0; i < birimSayisi; i++)
 {
    Birim birim = birimler[i];
    float ortalama = ortalamaMaasHesapla(birim);

    printf("Birim : %s\t Birim kodu :%hu\n",birim.birimAdi,birim.birimKodu);
    printf("Ortalama üstü maas alanlar :\n");

    int bulunan = 0;
    for (int j = 0; j < birim.calisanSayisi; j++)
    {
        if (birim.birimCalisanlar[j].maas > ortalama)
        {
             printf("*%s %s , Maas : %.2f\n",birim.birimCalisanlar[j].calisanAdi,birim.birimCalisanlar[j].calisanSoyadi,birim.birimCalisanlar[j].maas);
        bulunan = 1;
        }
       
    }
    if (!bulunan)
    {
        printf("ortalama üstü maas alan calisan yok!!!\n");
    }
    printf("\n");
    printf("\n"); //birimler arası 2 satir bısluk icin koydum
  
 }
  
}
// Birim ekleme
void birimEkle(Birim *birimler, Birim yeniBirim, int *birimSayisi) {
    birimler[*birimSayisi] = yeniBirim;
    (*birimSayisi)++;
}

//En yüksek alanları her birim için listeleme fonks.
void enYuksekMaasAlanlariListele(Birim *birimler, int birimSayisi){
    printf("En yuksek maas alan calisanlar sunlar: \n");
    for (int i = 0; i < birimSayisi; i++)
    {
        float maxMaas = 0;
        int maxIndex = -1;
        for (int j = 0; j < birimler[i].calisanSayisi; j++){
            if (birimler[i].birimCalisanlar[j].maas > maxMaas){
                maxMaas = birimler[i].birimCalisanlar[j].maas;
                maxIndex = j;
            }
            
        }
        if (maxIndex != -1)
        {
            printf("%s : \n",birimler[i].birimAdi);
            printf("%s %s ,maas : %.2f\n",birimler[i].birimCalisanlar[maxIndex].calisanAdi,birimler[i].birimCalisanlar[maxIndex].calisanSoyadi,maxMaas);
        } 
        
    }
    
}

//Mass güncelliyoz
void maasGuncelle(Birim *birim,int calisanIndex,float yeniMaas){
    if (calisanIndex >= 0 && calisanIndex < birim->calisanSayisi)
    {
        birim->birimCalisanlar[calisanIndex].maas = yeniMaas;
    }
    
}

//Birim ve calisan bilgilerini dosyadan okuma islemi
void birimVeCalisanBilgileriniDosyadanOku(Birim **birimler,int *birimSayisi,const char *birimDosya,const char *calisanDosya){
    FILE *birimFile = fopen( birimDosya , "r");
    FILE *calisanFile = fopen(calisanDosya,"r");

    if (!birimFile || !calisanFile)
    {
        printf("Dosyalar acilmadi");
        return;
    }

    //printf("1*****************************************"); 
    *birimSayisi = 0;
    while (!feof(birimFile))
    {
        char birimAdi[30];
        unsigned short int birimKodu;
        if (fscanf(birimFile,"%hu %s",&birimKodu,birimAdi)==2)
        {
            Birim birim = yeniBirim(birimAdi,birimKodu);
            birim.birimCalisanlar = 0;
            (*birimler)[(*birimSayisi)++] = birim;
            printf("%hu\t %s\n",birimKodu,birimAdi);
        }
        
    }
    //printf("2*****************");
    fclose(birimFile);
    while (!feof(calisanFile))
    {
        char calisanAdi[30],calisanSoyadi[30];
        unsigned short int birimKodu;
        float maas;
        int girisYili;
        if (fscanf(calisanFile,"%hu %s %s %f %d",&birimKodu,calisanAdi,calisanSoyadi,&maas,&girisYili) == 5)
        {
            Calisan calisan = yeniCalisan(calisanAdi,calisanSoyadi,birimKodu,maas,girisYili);
            for (int i = 0; i < *birimSayisi; i++)
            {
                if ((*birimler)[i].birimKodu == birimKodu)
                {
                    calisanEkle(&(*birimler)[i].birimCalisanlar,calisan,&(*birimler)[i].calisanSayisi);
                }
                
            }
            
            printf("%hu\t %s\t %s\t %f\t %d\n",birimKodu,calisanAdi,calisanSoyadi,maas,girisYili);
        }
        
    }
   // printf("3***************");
    fclose(calisanFile);
    
}

void birimVeCalisanBilgileriniDosyayaYaz(Birim *birimler, int birimSayisi, const char *birimDosya, const char *calisanDosya) {
    FILE *birimFile = fopen(birimDosya, "w");
    FILE *calisanFile = fopen(calisanDosya, "w");

    if (!birimFile || !calisanFile) {
        printf("Dosyalar acilamadi.\n");
        return;
    }

    for (int i = 0; i < birimSayisi; i++) {
        fprintf(birimFile, "%hu %s\n", birimler[i].birimKodu, birimler[i].birimAdi);
        for (int j = 0; j < birimler[i].calisanSayisi; j++) {
            fprintf(calisanFile, "%hu %s %s %.2f %d\n",
                    birimler[i].birimCalisanlar[j].birimKodu,
                    birimler[i].birimCalisanlar[j].calisanAdi,
                    birimler[i].birimCalisanlar[j].calisanSoyadi,
                    birimler[i].birimCalisanlar[j].maas,
                    birimler[i].birimCalisanlar[j].girisYili);
        }
    }

    fclose(birimFile);
    fclose(calisanFile);
}

//calişani dosyaya ekleme methodduu
void calisanDosyayaEkle(const char *calisanDosya, Calisan yeniCalisan){
    FILE *file = fopen(calisanDosya,"a");
    if(!file){
        printf("calisan dosyasi acilmadi!!!!\n");
        return;
    }
    fprintf(file,"%hu %s %s %.2f %d\n",yeniCalisan.birimKodu,yeniCalisan.calisanAdi,yeniCalisan.calisanSoyadi,yeniCalisan.maas,yeniCalisan.girisYili);
    fclose(file);
}
void uzunSureliCalisanlaraZamYap(Birim *birim, float yeniMaas) {
    for (int i = 0; i < birim->calisanSayisi; i++) {
        if ((2024 - birim->birimCalisanlar[i].girisYili) > 10 && birim->birimCalisanlar[i].maas < yeniMaas) {
            // Çalışanın işe giriş yılı 10 yıldan eski mi ve maaşı yeniMaas'tan düsük olup olmadığına göre maası düzenliyoruz
           
                birim->birimCalisanlar[i].maas = yeniMaas;
                printf("Maas guncellendi: %s %s, Yeni Maas: %.2f\n",birim->birimCalisanlar[i].calisanAdi,birim->birimCalisanlar[i].calisanSoyadi,yeniMaas);
            }
        }
    }