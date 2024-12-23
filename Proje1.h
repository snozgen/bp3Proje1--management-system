/**
* @file Proje1.h
* @description Bu dosya, birim ve çalışan işlemleri için kullanılan veri yapıları ve fonksiyonların prototiplerini içerir. 
* Yapılar, çalışan ve birim bilgilerinin düzenli bir şekilde saklanmasını sağlar ve işlevsellik için gereken tanımlar buradadır.
* @assignment 1. Ödev
* @date 23 Aralık 2024
* @author Sema Nur ÖZGEN - semanur.ozgen@stu.fsm.edu.tr
*/

#ifndef PROJE1_H
#define PROJE1_H

typedef struct 
{
    char    calisanAdi[30];
    char    calisanSoyadi[30];
    unsigned    short   int birimKodu;
    float   maas;
    int girisYili;
}Calisan;

typedef struct 
{
    char    birimAdi[30];
    unsigned    short   int birimKodu;
    Calisan *birimCalisanlar; //Dinamik bir çalışan listesi için pointer olarak tanımlıyoruz 
    int calisanSayisi;                        
}Birim;

//hocanın istediği fonksiyonların imazasını(prototipini) yazıyoss

Birim   yeniBirim(const char *birimAdi,unsigned short int birimKodu);
Calisan yeniCalisan(const char *adi,const char *soyadi,unsigned short int birimKodu,float maas, int girisYili);
void calisanEkle(Calisan **calisanlar,Calisan yeniCalisan,int *calisanSayisi);
void birimEkle(Birim *birimler,Birim yeniBirim,int *birimSayisi);
float ortalamaMaasHesapla(Birim birim);
void ortalamaUstuMaasAlanlariListele(Birim *birimler, int birimSayisi);
void enYuksekMaasAlanlariListele(Birim *birimler, int birimSayisi);
void maasGuncelle(Birim *birim,int calisanIndex,float yeniMaas);
void birimVeCalisanBilgileriniDosyadanOku(Birim **birimler, int *birimSayisi, const char *birimDosya, const char *calisanDosya);
void birimVeCalisanBilgileriniDosyayaYaz(Birim *birimler,int birimSayisi,const char *birimDosya,const char *calisanDosya);
void calisanDosyayaEkle(const char *calisanDosya,Calisan yeniCalisan);
void uzunSureliCalisanlaraZamYap(Birim *birim, float yeniMaas);
#endif



