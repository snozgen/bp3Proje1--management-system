/**
* @file main.c
* @description Bu dosya, birim ve çalışan bilgileri üzerinde çeşitli işlemler yapmayı sağlayan 
* menü tabanlı bir programın ana fonksiyonlarını içerir.
* @assignment 1. Ödev
* @date 23 Aralık 2024
* @author Sema Nur ÖZGEN - semanur.ozgen@stu.fsm.edu.tr
*/


#include "Proje1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//istedigimiz islemi yapabilmek icin bi menu olusturduk
void menu() {
    printf("Yapmak istediginiz islemi seciniz:\n");
    printf("1. Birim ve calisan bilgilerini dosyadan oku\n");
    printf("2. Yeni birim ve calisan ekle\n");
    printf("3. Tum birim bilgilerini yazdir\n");
    printf("4. Ortalama maas hesapla\n");
    printf("5. Ortalama ustu maas alanlari listele\n");
    printf("6. En yuksek maas alanlari listele\n");
    printf("7. Maas guncelle\n");
    printf("8. 10+ yil calisanlara zam yap\n");
    printf("9. Birim ve calisan bilgilerini dosyaya yazdir\n");
    printf("10. cikis\n");
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Kullanim: %s <birimDosya> <calisanDosya>\n", argv[0]);
        return 1;
    }
    const char *birimDosya = argv[1];
    const char *calisanDosya = argv[2];

    
    Birim *birimler = (Birim *)malloc(10 * sizeof(Birim));
    int birimSayisi = 0;
    while (1) {
        int secim;
        menu();
        printf("Seciminiz: ");
        scanf("%d", &secim);
        //printf("secim %d",secim);

        switch (secim) {
        case 1:
       // printf("case 1e girildi");
            birimVeCalisanBilgileriniDosyadanOku(&birimler, &birimSayisi, birimDosya, calisanDosya);
            break;
        case 2: {
            char birimAdi[30], calisanAdi[30], calisanSoyadi[30];
            unsigned short int birimKodu;
            float maas;
            int girisYili;

            printf("Birim adi: ");
            scanf("%s", birimAdi);
            printf("Birim kodu: ");
            scanf("%hu", &birimKodu);
            Birim yeniB = yeniBirim(birimAdi, birimKodu);

            printf("calisan adi: ");
            scanf("%s", calisanAdi);
            printf("calisan soyadi: ");
            scanf("%s", calisanSoyadi);
            printf("Maas: ");
            scanf("%f", &maas);
            printf("Giris yili: ");
            scanf("%d", &girisYili);

            Calisan yeniC = yeniCalisan(calisanAdi, calisanSoyadi, birimKodu, maas, girisYili);
            calisanEkle(&yeniB.birimCalisanlar, yeniC, &yeniB.calisanSayisi);
            birimEkle(birimler, yeniB, &birimSayisi);
            calisanDosyayaEkle(calisanDosya, yeniC);
            break;
        }
        case 3:
            for (int i = 0; i < birimSayisi; i++) {
                printf("Birim Adi: %s, Birim Kodu: %hu\n", birimler[i].birimAdi, birimler[i].birimKodu);
            }
            break;
        case 4: {
            unsigned short int birimKodu;
            printf("Ortalama maas hesaplanacak birim kodu: ");
            scanf("%hu", &birimKodu);
            int birimBulundu = 0;
            for (int i = 0; i < birimSayisi; i++) {
                if (birimler[i].birimKodu == birimKodu) {
                    float ortalama = ortalamaMaasHesapla(birimler[i]);
                    printf("Ortalama maas: %.2f\n", ortalama);
                    birimBulundu =1;
                    break;
                }
            }
            break;
            if ((!birimBulundu))
            {
                printf("Girdiginiz birim kodu ile eslesen bir birim bulunmadi!!!\n");
            }
            break;
            
        }
        case 5:
            
                ortalamaUstuMaasAlanlariListele(birimler,birimSayisi);
            break;
        case 6:
            enYuksekMaasAlanlariListele(birimler, birimSayisi);
            break;
        case 7: {
            unsigned short int birimKodu;
            printf("Birim kodu: ");
            scanf("%hu", &birimKodu);
            int calisanIndex;
            printf("calisan index: ");
            scanf("%d", &calisanIndex);
            float yeniMaas;
            printf("Yeni maas: ");
            scanf("%f", &yeniMaas);
            for (int i = 0; i < birimSayisi; i++) {
                if (birimler[i].birimKodu == birimKodu) {
                    maasGuncelle(&birimler[i], calisanIndex, yeniMaas);
                }
            }
            break;
        }
        case 8:{
            float yeniMaas;
            printf("10 yildan fazla calisanlar icin yeni maas güncellemesi:");
            scanf("%f",&yeniMaas);
            for (int i = 0; i < birimSayisi; i++)
            {
                uzunSureliCalisanlaraZamYap(&birimler[i],yeniMaas);
            }
            break;
            
        }
        case 9:
            birimVeCalisanBilgileriniDosyayaYaz(birimler, birimSayisi, birimDosya, calisanDosya);
            break;
        case 10:
            for (int i = 0; i < birimSayisi; i++) {
                free(birimler[i].birimCalisanlar);
            }
            free(birimler);
            return 0;
        default:
            printf("Gecersiz secim! Tekrar deneyin.\n");
        }
    }
}