#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void ogrenci_ekle();
void ogrenci_sil();
void ogrenci_guncelle();
void ogrenci_bilgi();
void teslim_etmemis();
void cezali_listele();
void ogrenci_listele();
void odunc_al();
void odunc_dosyaya_yaz();
void odunc_dosyadan_oku();
void teslim_et();
void ogrenci_dosyaya_yaz();
void ogrenci_dosyadan_oku();

void kitap_ekle();
void kitap_sil();
void kitap_guncelle();
void kitap_bilgi();
void raftakiler();
void gecikenler();
void kitap_yazar_eslestir();
void kitap_yazar_dosyadan_oku();
void kitap_yazar_dosyaya_yaz();
void kitap_yazar_guncelle();
void kitap_ornek_dosyadan_oku();
void kitap_ornek_dosyaya_yaz();
void kitap_dosyadan_oku();
void kitap_dosyaya_yaz();

void yazar_ekle();
void yazar_sil();
void yazar_guncelle();
void yazar_bilgi();
void yazar_listele();
void yazar_dosyaya_yaz();
void yazar_dosyadan_oku();

typedef struct Yazar
{
    int yazarID;
    char ad[50];
    char soyad[50];
    struct Yazar *next;
} Yazar;

typedef struct Ogrenci
{
    char ad[50];
    char soyad[50];
    char ogrenciNo[9]; // 8 haneli + null
    int puan;
    struct Ogrenci *next;
    struct Ogrenci *prev;
} Ogrenci;

typedef struct KitapOrnek
{
    char etiketNo[20]; // orn: 1234567891011_1
    char durum[20];    // "Rafta" veya ogrenciNo
    struct KitapOrnek *next;
} KitapOrnek;

typedef struct Kitap
{
    char ad[100];
    char ISBN[14]; // 13 hane + null
    int adet;
    KitapOrnek *ornekListesi;
    struct Kitap *next;
} Kitap;

typedef struct KitapYazar
{
    char ISBN[14];
    int *yazarIDler;
    int yazarSayisi;
} KitapYazar;

typedef struct KitapOdunc
{
    char etiketNo[20];
    char ogrenciNo[10];
    int islemTuru;    // 0: Odunc alma, 1: Teslim etme
    int gun, ay, yil; // Tarih bilgisi
    struct KitapOdunc *next;
} KitapOdunc;

int main()
{
    int secim;
    char devam;

    Kitap *kitapHead = NULL;
    Ogrenci *ogrenciHead = NULL;
    KitapOdunc *oduncHead = NULL;
    Yazar *yazarHead = NULL;
    KitapYazar *kitapYazarEslesmeler = NULL;
    int eslesmeSayisi = 0;
    do
    {
        printf("\n=========== MENU ===========\n");
        printf("OGRENCI ISLEMLERI:\n");
        printf(" 1 - Ogrenci Ekle\n");
        printf(" 2 - Ogrenci Sil\n");
        printf(" 3 - Ogrenci Guncelle\n");
        printf(" 4 - Ogrenci Bilgisi Goruntuleme\n");
        printf(" 5 - Kitap Teslim Etmemis Ogrencileri Listele\n");
        printf(" 6 - Cezali Ogrencileri Listele\n");
        printf(" 7 - Tum Ogrencileri Listele\n");
        printf(" 8 - Kitap Odunc Al\n");
        printf(" 9 - Kitap Teslim Et\n");

        printf("\nKITAP ISLEMLERI:\n");
        printf("10 - Kitap Ekle\n");
        printf("11 - Kitap Sil\n");
        printf("12 - Kitap Guncelle\n");
        printf("13 - Kitap Bilgisi Goruntuleme\n");
        printf("14 - Raftaki Kitaplari Listele\n");
        printf("15 - Zamaninda Teslim Edilmeyen Kitaplari Listele\n");
        printf("16 - Kitap-Yazar Eslestir\n");
        printf("17 - Kitabin Yazarini Guncelle\n");

        printf("\nYAZAR ISLEMLERI:\n");
        printf("18 - Yazar Ekle\n");
        printf("19 - Yazar Sil\n");
        printf("20 - Yazar Guncelle\n");
        printf("21 - Yazar Bilgisi Goruntuleme\n");
        printf("22 - Tum Yazarlari Listele\n");

        printf("\n0 - CIKIS\n");
        printf("Seciminiz: ");
        scanf("%d", &secim);
        getchar(); // \n karakterini temizle

        yazar_dosyadan_oku(&yazarHead);
        ogrenci_dosyadan_oku(&ogrenciHead);
        kitap_dosyadan_oku(&kitapHead);
        kitap_ornek_dosyadan_oku(kitapHead);
        odunc_dosyadan_oku(&oduncHead);
        kitap_yazar_dosyadan_oku(&kitapYazarEslesmeler, &eslesmeSayisi);

        switch (secim)
        {
        case 1:
            ogrenci_ekle(&ogrenciHead);
            break;

        case 2:
            ogrenci_sil(&ogrenciHead);
            break;

        case 3:
            ogrenci_guncelle(ogrenciHead);
            break;

        case 4:
            ogrenci_bilgi(ogrenciHead, oduncHead);
            break;

        case 5:
            teslim_etmemis(ogrenciHead, oduncHead);
            break;

        case 6:
            cezali_listele(ogrenciHead);
            break;

        case 7:
            ogrenci_listele(ogrenciHead);
            break;

        case 8:
            odunc_al(&kitapHead, &ogrenciHead, &oduncHead);
            break;

        case 9:
            teslim_et(&kitapHead, &ogrenciHead, &oduncHead);
            break;

        case 10:
            kitap_ekle(&kitapHead);
            break;

        case 11:
            kitap_sil(&kitapHead);
            break;

        case 12:
            kitap_guncelle(kitapHead);
            break;

        case 13:
            kitap_bilgi(kitapHead);
            break;

        case 14:
            raftakiler(kitapHead);
            break;

        case 15:
            gecikenler(oduncHead);
            break;

        case 16:
            kitap_yazar_eslestir(kitapHead, yazarHead);
            break;

        case 17:
            kitap_yazar_guncelle(kitapHead, yazarHead);
            break;

        case 18:
            yazar_ekle(&yazarHead);
            break;

        case 19:
            yazar_sil(&yazarHead);
            break;

        case 20:
            yazar_guncelle(yazarHead);
            break;

        case 21:
            yazar_bilgi(yazarHead, kitapHead, kitapYazarEslesmeler, eslesmeSayisi);
            break;

        case 22:
            yazar_listele(yazarHead);
            break;

        case 0:
            printf("Programdan cikiliyor...\n");
            return 0;
        default:
            printf("Gecersiz secim!\n");
        }

        printf("\nBaska bir islem yapmak istiyor musunuz? (E/h): ");
        scanf(" %c", &devam);
        getchar();

    } while (devam == 'E' || devam == 'e');

    printf("Programdan cikiliyor...\n");
    return 0;
}

void ogrenci_ekle(Ogrenci **ogrenciHead)
{
    int i;
    Ogrenci *yeni_ogrenci = (Ogrenci *)malloc(sizeof(Ogrenci));
    if (yeni_ogrenci == NULL)
    {
        printf("Bellek ayrilamadi.\n");
        return;
    }

    printf("Ogrenci adi: ");
    scanf(" %49[^\n]", yeni_ogrenci->ad);

    printf("Ogrenci soyadi: ");
    scanf(" %49[^\n]", yeni_ogrenci->soyad);

    int numaraUygun = 0;

    while (!numaraUygun)
    {
        int sayi = rand() % 100000000;
        for (i = 7; i >= 0; i--)
        {
            yeni_ogrenci->ogrenciNo[i] = (sayi % 10) + '0';
            sayi /= 10;
        }
        yeni_ogrenci->ogrenciNo[8] = '\0';

        numaraUygun = 1;
        Ogrenci *ptr = *ogrenciHead;

        while (ptr != NULL && numaraUygun == 1)
        {
            if (strcmp(ptr->ogrenciNo, yeni_ogrenci->ogrenciNo) == 0)
            {
                numaraUygun = 0;
            }
            ptr = ptr->next;
        }
    }

    yeni_ogrenci->puan = 100;
    yeni_ogrenci->prev = NULL;
    yeni_ogrenci->next = *ogrenciHead;

    if (*ogrenciHead != NULL)
        (*ogrenciHead)->prev = yeni_ogrenci;

    *ogrenciHead = yeni_ogrenci;

    ogrenci_dosyaya_yaz(*ogrenciHead);
    printf("Ogrenci eklendi. Ogrenci No: %s\n", yeni_ogrenci->ogrenciNo);
}

void ogrenci_dosyadan_oku(Ogrenci **ogrenciHead)
{
    FILE *file = fopen("ogrenciler.csv", "r");
    if (!file)
    {
        printf("ogrenciler.csv dosyasi bulunamadi veya acilamadi.\n");
        return;
    }

    // Mevcut listeyi temizle
    Ogrenci *temp;
    while (*ogrenciHead)
    {
        temp = *ogrenciHead;
        *ogrenciHead = (*ogrenciHead)->next;
        free(temp);
    }

    Ogrenci *last = NULL;
    char no[9], ad[50], soyad[50];
    int puan;

    while (fscanf(file, "%8[^,], %49[^,], %49[^,], %d\n", no, ad, soyad, &puan) == 4)
    {
        Ogrenci *yeni = (Ogrenci *)malloc(sizeof(Ogrenci));
        if (!yeni)
        {
            printf("Bellek ayrilamadi.\n");
            fclose(file);
            return;
        }

        strcpy(yeni->ogrenciNo, no);
        strcpy(yeni->ad, ad);
        strcpy(yeni->soyad, soyad);
        yeni->puan = puan;

        yeni->next = NULL;
        yeni->prev = last;

        if (last)
            last->next = yeni;
        else
            *ogrenciHead = yeni;

        last = yeni;
    }

    fclose(file);
}

void ogrenci_dosyaya_yaz(Ogrenci *ogrenciHead)
{
    FILE *file = fopen("ogrenciler.csv", "w");
    if (!file)
    {
        printf("Dosya acilamadi.\n");
        return;
    }

    Ogrenci *current = ogrenciHead;
    while (current)
    {
        fprintf(file, "%s, %s, %s, %d\n", current->ogrenciNo, current->ad, current->soyad, current->puan);
        current = current->next;
    }

    fclose(file);
}

void ogrenci_sil(Ogrenci **ogrenciHead)
{
    char no[9];
    printf("Silinecek ogrenci numarasi : ");
    scanf(" %8s", no);

    Ogrenci *current = *ogrenciHead;

    while (current != NULL)
    {
        if (strcmp(current->ogrenciNo, no) == 0)
        {
            if (current->prev != NULL)
                current->prev->next = current->next;
            else
                *ogrenciHead = current->next;

            if (current->next != NULL)
                current->next->prev = current->prev;

            free(current);
            ogrenci_dosyaya_yaz(*ogrenciHead);
            printf("Ogrenci silindi.\n");
            return;
        }
        current = current->next;
    }

    printf("Ogrenci bulunamadi.\n");
}

void ogrenci_guncelle(Ogrenci *ogrenciHead)
{
    char no[9];
    printf("Guncellenecek ogrenci numarasi: ");
    scanf(" %8s", no);

    Ogrenci *current = ogrenciHead;
    while (current != NULL && strcmp(current->ogrenciNo, no) != 0)
        current = current->next;

    if (current == NULL)
    {
        printf("Ogrenci bulunamadi.\n");
        return;
    }

    int secim;
    do
    {
        printf("\n--- Hangi bilgiyi guncellemek istiyorsunuz? ---\n");
        printf("1 - Ad\n");
        printf("2 - Soyad\n");
        printf("3 - Ogrenci Numarasi\n");
        printf("4 - Puan\n");
        printf("0 - cikis\n");
        printf("Seciminiz: ");
        scanf("%d", &secim);
        getchar();

        switch (secim)
        {
        case 1:
            printf("Yeni ad: ");
            scanf(" %49[^\n]", current->ad);
            break;
        case 2:
            printf("Yeni soyad: ");
            scanf(" %49[^\n]", current->soyad);
            break;
        case 3:
        {
            int numaraUygun = 0;
            char yeniNo[9];

            while (!numaraUygun)
            {
                printf("Yeni ogrenci numarasi (8 haneli): ");
                scanf(" %8s", yeniNo);
                numaraUygun = 1;

                Ogrenci *tmp = ogrenciHead;

                while (tmp != NULL && numaraUygun == 1)
                {
                    if (tmp != current && strcmp(tmp->ogrenciNo, yeniNo) == 0)
                    {
                        printf("Bu numara zaten kullaniliyor.\n");
                        numaraUygun = 0;
                    }
                    tmp = tmp->next;
                }
            }

            strcpy(current->ogrenciNo, yeniNo);
        }

        case 4:
            printf("Yeni puan: ");
            scanf("%d", &current->puan);
            break;
        case 0:
            printf("Guncelleme islemi sona erdi.\n");
            break;
        default:
            printf("Gecersiz secim!\n");
        }

    } while (secim != 0);

    ogrenci_dosyaya_yaz(ogrenciHead);
    printf("Ogrenci bilgileri basariyla guncellendi.\n");
}

void ogrenci_bilgi(Ogrenci *ogrenciHead, KitapOdunc *oduncHead)
{
    char secim;
    char ad[50], soyad[50], no[9];
    Ogrenci *ogr = NULL;
    Ogrenci *gecici = ogrenciHead;

    printf("Arama secimi: (N)umarayla veya (A)d-Soyad ile: ");
    scanf(" %c", &secim);

    if (secim == 'N' || secim == 'n')
    {
        printf("Ogrenci numarasi (8 haneli): ");
        scanf(" %8s", no);

        while (gecici != NULL && ogr == NULL)
        {
            if (strcmp(gecici->ogrenciNo, no) == 0)
                ogr = gecici;
            gecici = gecici->next;
        }
    }
    else if (secim == 'A' || secim == 'a')
    {
        printf("Ogrenci adi: ");
        scanf(" %49[^\n]", ad);
        printf("Ogrenci soyadi: ");
        scanf(" %49[^\n]", soyad);

        while (gecici != NULL && ogr == NULL)
        {
            if (strcmp(gecici->ad, ad) == 0 && strcmp(gecici->soyad, soyad) == 0)
                ogr = gecici;
            gecici = gecici->next;
        }
    }
    else
    {
        printf("Gecersiz secim!\n");
        return;
    }

    if (ogr == NULL)
    {
        printf("Ogrenci bulunamadi.\n");
        return;
    }

    // Öğrenci bilgileri
    printf("\n--- Ogrenci Bilgileri ---\n");
    printf("Ad       : %s\n", ogr->ad);
    printf("Soyad    : %s\n", ogr->soyad);
    printf("Numara   : %s\n", ogr->ogrenciNo);
    printf("Puan     : %d\n", ogr->puan);

    // Kitap hareketleri
    printf("\n--- Kitap Hareketleri ---\n");

    int bulundu = 0;
    KitapOdunc *odunc = oduncHead;
    while (odunc != NULL)
    {
        if (strcmp(odunc->ogrenciNo, ogr->ogrenciNo) == 0)
        {
            bulundu = 1;
            printf("Etiket No: %s | Islem: %s | Tarih: %02d/%02d/%04d\n",
                   odunc->etiketNo,
                   (odunc->islemTuru == 0 ? "Odunc Alindi" : "Teslim Edildi"),
                   odunc->gun, odunc->ay, odunc->yil);
        }
        odunc = odunc->next;
    }

    if (!bulundu)
    {
        printf("Bu ogrenciye ait kitap hareketi bulunmamaktadir.\n");
    }
}

void teslim_etmemis(Ogrenci *ogrenciHead, KitapOdunc *oduncHead)
{
    KitapOdunc *odunc = oduncHead;

    printf("Ad                   Soyad                Ogrenci No   Etiket No\n");
    printf("------------------------------------------------------------------------\n");

    while (odunc != NULL)
    {
        if (odunc->islemTuru == 0) // ödünç alma
        {
            // Daha yeni bir teslim var mi kontrol et
            int teslimEdilmis = 0;
            KitapOdunc *kontrol = oduncHead;
            while (kontrol != NULL)
            {
                if (strcmp(kontrol->etiketNo, odunc->etiketNo) == 0 &&
                    strcmp(kontrol->ogrenciNo, odunc->ogrenciNo) == 0 &&
                    kontrol->islemTuru == 1)
                {
                    int oduncTarih = odunc->yil * 10000 + odunc->ay * 100 + odunc->gun;
                    int teslimTarih = kontrol->yil * 10000 + kontrol->ay * 100 + kontrol->gun;

                    if (teslimTarih > oduncTarih)
                    {
                        teslimEdilmis = 1;
                    }
                }
                kontrol = kontrol->next;
            }

            if (!teslimEdilmis)
            {
                // öğrenciyi yazdir
                Ogrenci *o = ogrenciHead;
                while (o != NULL)
                {
                    if (strcmp(o->ogrenciNo, odunc->ogrenciNo) == 0)
                    {
                        printf("%-20s %-20s %-12s %-10s\n",
                               o->ad, o->soyad, o->ogrenciNo, odunc->etiketNo);
                    }
                    o = o->next;
                }
            }
        }
        odunc = odunc->next;
    }
}

void cezali_listele(Ogrenci *ogrenciHead)
{
    printf("\nAd                   Soyad                Ogrenci No\n");
    printf("---------------------------------------------------------------\n");

    Ogrenci *ogr = ogrenciHead;
    while (ogr != NULL)
    {
        if (ogr->puan < 0)
        {
            printf("%-20s %-20s %-11s\n", ogr->ad, ogr->soyad, ogr->ogrenciNo);
        }
        ogr = ogr->next;
    }
}

void ogrenci_listele(Ogrenci *ogrenciHead)
{
    Ogrenci *current = ogrenciHead;

    if (current == NULL)
    {
        printf("Hic ogrenci yok.\n");
        return;
    }

    printf("\n%-20s %-20s %-12s %-5s\n", "Ad", "Soyad", "Ogrenci No", "Puan");
    printf("---------------------------------------------------------------\n");

    while (current != NULL)
    {
        printf("%-20s %-20s %-12s %-5d\n",
               current->ad, current->soyad, current->ogrenciNo, current->puan);
        current = current->next;
    }
}

void odunc_dosyaya_yaz(KitapOdunc *oduncHead)
{
    FILE *file = fopen("KitapOduncAl.csv", "w");
    KitapOdunc *current = oduncHead;
    while (current != NULL)
    {
        fprintf(file, "%s,%s,%d,%02d.%02d.%04d\n", current->etiketNo, current->ogrenciNo, current->islemTuru, current->gun, current->ay, current->yil);
        current = current->next;
    }
    fclose(file);
}

void odunc_dosyadan_oku(KitapOdunc **oduncHead)
{
    FILE *file = fopen("KitapOduncAl.csv", "r");
    if (file == NULL)
    {
        printf("KitapOduncAl.csv dosyasi acilamadi.\n");
        return;
    }

    KitapOdunc *temp;
    while (*oduncHead)
    {
        temp = *oduncHead;
        *oduncHead = (*oduncHead)->next;
        free(temp);
    }

    char satir[100];
    while (fgets(satir, sizeof(satir), file))
    {
        KitapOdunc *yeni = malloc(sizeof(KitapOdunc));
        if (!yeni)
        {
            printf("Bellek ayrilamadi.\n");
            fclose(file);
            return;
        }

        int gun, ay, yil;
        sscanf(satir, "%[^,],%[^,],%d,%d.%d.%d",
               yeni->etiketNo, yeni->ogrenciNo, &yeni->islemTuru, &gun, &ay, &yil);

        yeni->gun = gun;
        yeni->ay = ay;
        yeni->yil = yil;
        yeni->next = *oduncHead;
        *oduncHead = yeni;
    }

    fclose(file);
}

void odunc_al(Kitap **kitapHead, Ogrenci **ogrenciHead, KitapOdunc **oduncHead)
{
    KitapOdunc *yeni = malloc(sizeof(KitapOdunc));
    printf("Kitap Etiket No: ");
    scanf("%19[^\n]", yeni->etiketNo);
    getchar();
    printf("Ogrenci No: ");
    scanf("%9[^\n]", yeni->ogrenciNo);
    getchar();
    printf("Tarih (GG AA YYYY): ");
    scanf("%d %d %d", &yeni->gun, &yeni->ay, &yeni->yil);
    getchar();

    int kitapBulundu = 0;
    int ornekUygun = 0;
    Kitap *kitap = *kitapHead;

    while (kitap != NULL)
    {
        KitapOrnek *ornek = kitap->ornekListesi;
        while (ornek != NULL)
        {
            if (strcmp(ornek->etiketNo, yeni->etiketNo) == 0)
            {
                kitapBulundu = 1;
                if (strcmp(ornek->durum, "Rafta") == 0)
                {
                    strcpy(ornek->durum, yeni->ogrenciNo);
                    ornekUygun = 1;
                }
            }
            ornek = ornek->next;
        }
        kitap = kitap->next;
    }

    int ogrenciBulundu = 0;
    int puanYeterli = 0;
    Ogrenci *ogr = *ogrenciHead;

    while (ogr != NULL)
    {
        if (strcmp(ogr->ogrenciNo, yeni->ogrenciNo) == 0)
        {
            ogrenciBulundu = 1;
            if (ogr->puan >= 0)
            {
                puanYeterli = 1;
            }
        }
        ogr = ogr->next;
    }

    if (!kitapBulundu)
    {
        printf("Kitap bulunamadi.\n");
        free(yeni);
        return;
    }

    if (!ogrenciBulundu)
    {
        printf("Ogrenci bulunamadi.\n");
        free(yeni);
        return;
    }

    if (!puanYeterli)
    {
        printf("Ogrencinin puani yetersiz, kitap verilemez.\n");
        free(yeni);
        return;
    }

    if (!ornekUygun)
    {
        printf("Tum ornekler odunc verilmis.\n");
        free(yeni);
        return;
    }

    yeni->islemTuru = 0;
    yeni->next = *oduncHead;
    *oduncHead = yeni;

    odunc_dosyaya_yaz(*oduncHead);
    kitap_ornek_dosyaya_yaz(*kitapHead);
    printf("Kitap odunc verildi.\n");
}

void teslim_et(Kitap **kitapHead, Ogrenci **ogrenciHead, KitapOdunc **oduncHead)
{
    char etiketNo[20];
    char ogrenciNo[10];
    int gun, ay, yil;
    int fark, gun1, gun2;
    printf("Kitap Etiket No: ");
    scanf("%19[^\n]", etiketNo);
    getchar();
    printf("Ogrenci No: ");
    scanf("%9[^\n]", ogrenciNo);
    getchar();
    printf("Teslim Tarihi (GG AA YYYY): ");
    scanf("%d %d %d", &gun, &ay, &yil);
    getchar();

    KitapOdunc *current = *oduncHead;
    while (current != NULL)
    {
        if (strcmp(current->etiketNo, etiketNo) == 0 &&
            strcmp(current->ogrenciNo, ogrenciNo) == 0 &&
            current->islemTuru == 0)
        {

            gun1 = 365 * current->yil + 30 * current->ay + current->gun;
            gun2 = 365 * yil + 30 * ay + gun;

            fark = gun2 - gun1;

            KitapOdunc *yeni = malloc(sizeof(KitapOdunc));
            strcpy(yeni->etiketNo, etiketNo);
            strcpy(yeni->ogrenciNo, ogrenciNo);
            yeni->gun = gun;
            yeni->ay = ay;
            yeni->yil = yil;
            yeni->islemTuru = 1;
            yeni->next = *oduncHead;
            *oduncHead = yeni;

            Kitap *kitap = *kitapHead;
            while (kitap != NULL)
            {
                KitapOrnek *ornek = kitap->ornekListesi;
                while (ornek != NULL)
                {
                    if (strcmp(ornek->etiketNo, etiketNo) == 0 && strcmp(ornek->durum, ogrenciNo) == 0)
                    {
                        strcpy(ornek->durum, "Rafta");
                    }
                    ornek = ornek->next;
                }
                kitap = kitap->next;
            }

            if (fark > 15)
            {
                Ogrenci *ogr = *ogrenciHead;
                while (ogr != NULL)
                {
                    if (strcmp(ogr->ogrenciNo, ogrenciNo) == 0)
                    {
                        ogr->puan -= 10;
                    }
                    ogr = ogr->next;
                }
                ogrenci_dosyaya_yaz(*ogrenciHead);
                printf("15 gunden gec teslim! Ceza puani uygulandi.\n");
            }

            odunc_dosyaya_yaz(*oduncHead);
            kitap_ornek_dosyaya_yaz(*kitapHead);
            printf("Kitap teslim edildi.\n");
            return;
        }
        current = current->next;
    }
    printf("Gecmis odunc kaydi bulunamadi.\n");
}

void kitap_dosyadan_oku(Kitap **kitapHead)
{
    FILE *file = fopen("kitaplar.csv", "r");
    if (!file)
        return;

    Kitap *temp;
    while (*kitapHead)
    {
        temp = *kitapHead;
        *kitapHead = (*kitapHead)->next;
        free(temp);
    }

    Kitap *last = NULL;
    while (!feof(file))
    {
        Kitap *yeni = malloc(sizeof(Kitap));
        if (!yeni)
        {
            fclose(file);
            return;
        }

        if (fscanf(file, "%99[^,],%13[^,],%d\n", yeni->ad, yeni->ISBN, &yeni->adet) == 3)
        {
            yeni->ornekListesi = NULL;
            yeni->next = NULL;

            if (*kitapHead == NULL)
            {
                *kitapHead = yeni;
                last = yeni;
            }
            else
            {
                last->next = yeni;
                last = yeni;
            }
        }
        else
        {
            free(yeni);
        }
    }

    fclose(file);
}

void kitap_ornek_dosyadan_oku(Kitap *kitapHead)
{
    FILE *file = fopen("kitapOrnekleri.csv", "r");
    if (!file)
        return;

    char etiketNo[20], durum[20];
    while (fscanf(file, "%19[^,],%19[^\n]\n", etiketNo, durum) == 2)
    {
        char isbn[14];
        int i = 0;
        while (etiketNo[i] != '_' && etiketNo[i] != '\0' && i < 13)
        {
            isbn[i] = etiketNo[i];
            i++;
        }
        isbn[i] = '\0';

        Kitap *kitap = kitapHead;
        int bulundu = 0;

        while (kitap != NULL && !bulundu)
        {
            if (strcmp(kitap->ISBN, isbn) == 0)
            {
                KitapOrnek *yeni = malloc(sizeof(KitapOrnek));
                if (!yeni)
                {
                    fclose(file);
                    return;
                }

                strcpy(yeni->etiketNo, etiketNo);
                strcpy(yeni->durum, durum);
                yeni->next = NULL;

                if (kitap->ornekListesi == NULL)
                {
                    kitap->ornekListesi = yeni;
                }
                else
                {
                    KitapOrnek *son = kitap->ornekListesi;
                    while (son->next != NULL)
                    {
                        son = son->next;
                    }
                    son->next = yeni;
                }

                bulundu = 1; // eşleşen kitap bulundu, döngü devam etmeyecek
            }
            if (!bulundu)
            {
                kitap = kitap->next;
            }
        }
    }

    fclose(file);
}

void kitap_dosyaya_yaz(Kitap *kitapHead)
{
    FILE *fp = fopen("kitaplar.csv", "w");
    if (fp == NULL)
    {
        printf("kitaplar.csv dosyasi acilamadi.\n");
        return;
    }

    Kitap *k = kitapHead;
    while (k != NULL)
    {
        fprintf(fp, "%s,%s,%d\n", k->ad, k->ISBN, k->adet);
        k = k->next;
    }

    fclose(fp);
}

void kitap_ornek_dosyaya_yaz(Kitap *kitapHead)
{
    FILE *file = fopen("kitapOrnekleri.csv", "w");
    if (!file)
    {
        printf("kitapOrnekleri.csv dosyasi acilamadi.\n");
        return;
    }

    Kitap *kitap = kitapHead;
    while (kitap != NULL)
    {
        KitapOrnek *ornek = kitap->ornekListesi;
        while (ornek != NULL)
        {
            fprintf(file, "%s,%s\n", ornek->etiketNo, ornek->durum);
            ornek = ornek->next;
        }
        kitap = kitap->next;
    }

    fclose(file);
}

void kitap_ekle(Kitap **kitapHead)
{
    int i, k;
    Kitap *yeni = (Kitap *)malloc(sizeof(Kitap));
    yeni->ornekListesi = NULL;
    yeni->next = NULL;

    printf("Kitap adi: ");
    scanf(" %[^\n]", yeni->ad);

    printf("13 haneli ISBN: ");
    scanf(" %[^\n]", yeni->ISBN);

    printf("Kitap adedi: ");
    scanf("%d", &yeni->adet);

    for (i = 1; i <= yeni->adet; i++)
    {
        KitapOrnek *ornek = (KitapOrnek *)malloc(sizeof(KitapOrnek));
        ornek->next = NULL;

        int j = 0;
        while (yeni->ISBN[j] != '\0')
        {
            ornek->etiketNo[j] = yeni->ISBN[j];
            j++;
        }

        ornek->etiketNo[j++] = '_';

        int adet = i, bas = j;
        int temp = adet, basamak = 0;
        while (temp > 0)
        {
            basamak++;
            temp /= 10;
        }

        for (k = basamak - 1; k >= 0; k--)
        {
            ornek->etiketNo[j + k] = (adet % 10) + '0';
            adet /= 10;
        }

        j += basamak;
        ornek->etiketNo[j] = '\0';

        strcpy(ornek->durum, "Rafta");

        ornek->next = yeni->ornekListesi;
        yeni->ornekListesi = ornek;
    }

    if (*kitapHead == NULL || strcmp(yeni->ad, (*kitapHead)->ad) < 0)
    {
        yeni->next = *kitapHead;
        *kitapHead = yeni;
    }
    else
    {
        Kitap *tmp = *kitapHead;
        while (tmp->next != NULL && strcmp(yeni->ad, tmp->next->ad) > 0)
            tmp = tmp->next;
        yeni->next = tmp->next;
        tmp->next = yeni;
    }

    kitap_dosyaya_yaz(*kitapHead);
    kitap_ornek_dosyaya_yaz(*kitapHead);
    printf("Kitap ve ornekleri eklendi.\n");
}

void kitap_sil(Kitap **kitapHead)
{
    char silinecekISBN[14];
    printf("Silinecek kitap ISBN: ");
    scanf(" %[^\n]", silinecekISBN);

    Kitap *onceki = NULL;
    Kitap *current = *kitapHead;

    while (current != NULL)
    {
        if (strcmp(current->ISBN, silinecekISBN) == 0)
        {
            if (onceki == NULL)
                *kitapHead = current->next;
            else
                onceki->next = current->next;

            KitapOrnek *o = current->ornekListesi;
            while (o != NULL)
            {
                KitapOrnek *sil = o;
                o = o->next;
                free(sil);
            }

            free(current);
            kitap_dosyaya_yaz(*kitapHead);
            kitap_ornek_dosyaya_yaz(*kitapHead);
            printf("Kitap ve ornekleri silindi.\n");
            return;
        }
        onceki = current;
        current = current->next;
    }

    printf("Kitap bulunamadi.\n");
}

void kitap_guncelle(Kitap *kitapHead)
{
    char isbn[14];
    printf("Duzenlenecek kitabin ISBN numarasini girin: ");
    scanf(" %[^\n]", isbn);

    Kitap *k = kitapHead;

    while (k != NULL)
    {
        if (strcmp(k->ISBN, isbn) == 0)
        {
            printf("Mevcut Bilgiler:\n");
            printf("ISBN : %s\n", k->ISBN);
            printf("Ad   : %s\n\n", k->ad);

            printf("Yeni kitap adi: ");
            scanf(" %[^\n]", k->ad);

            char cevap;
            printf("ISBN numarasini da guncellemek ister misiniz? (E/h): ");
            scanf(" %c", &cevap);

            if (cevap == 'E' || cevap == 'e')
            {
                char yeni_isbn[14];
                printf("Yeni ISBN: ");
                scanf(" %[^\n]", yeni_isbn);
                strcpy(k->ISBN, yeni_isbn);
            }

            kitap_dosyaya_yaz(kitapHead);
            printf("Kitap bilgileri guncellendi.\n");
            return;
        }
        k = k->next;
    }

    printf("Kitap bulunamadi.\n");
}

void kitap_bilgi(Kitap *kitapHead)
{
    char arananAd[100];
    printf("Bilgilerini gormek istediginiz kitap adini girin: ");
    scanf(" %[^\n]", arananAd);

    int bulundu = 0;
    Kitap *kitap = kitapHead;

    while (kitap != NULL)
    {
        if (strstr(kitap->ad, arananAd) != NULL) // parça eşleşme (örneğin: "Matematik" → "İleri Matematik")
        {
            bulundu = 1;
            printf("\n--- Kitap Bilgisi ---\n");
            printf("Kitap Adi : %s\n", kitap->ad);
            printf("ISBN      : %s\n", kitap->ISBN);
            printf("Adet      : %d\n", kitap->adet);

            KitapOrnek *ornek = kitap->ornekListesi;
            int sira = 1;

            if (ornek == NULL)
            {
                printf("Bu kitaba ait ornek bulunamadi.\n");
            }
            else
            {
                printf("Ornekler:\n");
                while (ornek != NULL)
                {
                    printf(" %d) Etiket No: %s, Durum: %s\n", sira, ornek->etiketNo, ornek->durum);
                    ornek = ornek->next;
                    sira++;
                }
            }
        }

        kitap = kitap->next;
    }

    if (!bulundu)
    {
        printf("Aranan ad iceren kitap bulunamadi.\n");
    }
}

void raftakiler(Kitap *kitapHead)
{
    Kitap *kitap = kitapHead;
    int bulundu = 0;

    printf("\n=== Raftaki Kitaplar ===\n");
    printf("%-14s     %-20s   %-20s\n", "ISBN", "Ad", "Etiket No");
    printf("---------------------------------------------------------------\n");

    while (kitap)
    {
        KitapOrnek *ornek = kitap->ornekListesi;

        while (ornek)
        {
            if (strcmp(ornek->durum, "Rafta") == 0)
            {
                printf("%-14s     %-20s   %-20s\n",
                       kitap->ISBN, kitap->ad, ornek->etiketNo);
                bulundu = 1;
            }
            ornek = ornek->next;
        }

        kitap = kitap->next;
    }

    if (!bulundu)
        printf("Rafta hiç kitap yok.\n");
}

void gecikenler(KitapOdunc *oduncHead)
{
    KitapOdunc *odunc = oduncHead;

    while (odunc != NULL)
    {
        if (odunc->islemTuru == 1) // teslim kaydı
        {
            KitapOdunc *onceki = oduncHead;
            while (onceki != NULL)
            {
                if (onceki->islemTuru == 0 &&
                    strcmp(onceki->etiketNo, odunc->etiketNo) == 0 &&
                    strcmp(onceki->ogrenciNo, odunc->ogrenciNo) == 0)
                {
                    int gun1 = 365 * onceki->yil + 30 * onceki->ay + onceki->gun;
                    int gun2 = 365 * odunc->yil + 30 * odunc->ay + odunc->gun;
                    int fark = gun2 - gun1;

                    if (fark > 15)
                    {
                        printf("GEC TESLIM EDILEN KITAP:\n");
                        printf("Etiket No   : %s\n", odunc->etiketNo);
                        printf("Ogrenci No  : %s\n", odunc->ogrenciNo);
                        printf("Odunc Tarihi: %02d.%02d.%04d\n", onceki->gun, onceki->ay, onceki->yil);
                        printf("Teslim Tarihi: %02d.%02d.%04d\n", odunc->gun, odunc->ay, odunc->yil);
                        printf("Gecikme     : %d gun\n\n", fark);
                    }
                }
                onceki = onceki->next;
            }
        }
        odunc = odunc->next;
    }
}

void kitap_yazar_dosyaya_yaz(KitapYazar *liste, int adet)
{
    int i,j;
    FILE *file = fopen("kitapYazar.csv", "w");
    if (!file)
    {
        printf("kitap_yazar.csv dosyasi acilamadi (yazma).\n");
        return;
    }

    for (i = 0; i < adet; i++)
    {
        for (j = 0; j < liste[i].yazarSayisi; j++)
        {
            fprintf(file, "%s, %d\n", liste[i].ISBN, liste[i].yazarIDler[j]);
        }
    }

    fclose(file);
}

void kitap_yazar_dosyadan_oku(KitapYazar **liste, int *adet)
{
    int k;
    FILE *file = fopen("KitapYazar.csv", "r");
    if (!file)
    {
        printf("KitapYazar.csv dosyasi acilamadi.\n");
        *liste = NULL;
        *adet = 0;
        return;
    }

    KitapYazar *geciciListe = NULL;
    int sayi = 0;

    char satir[256];
    while (fgets(satir, sizeof(satir), file))
    {
        KitapYazar ky;
        int idler[10]; // max 10 yazar
        int sayac = 0;

        int i = 0, j = 0;

        // ISBN oku
        while (satir[i] != ',' && satir[i] != '\0' && satir[i] != '\n')
        {
            ky.ISBN[j++] = satir[i++];
        }
        ky.ISBN[j] = '\0';

        // Virgülü geç
        if (satir[i] == ',')
            i++;

        int devam = 1;
        while (devam)
        {
            int val = 0;
            int negatif = 0;

            // Boşlukları atla
            while (satir[i] == ' ')
                i++;

            // Negatif kontrolü
            if (satir[i] == '-')
            {
                negatif = 1;
                i++;
            }

            // Rakam değilse döngü bitmeli
            if (!(satir[i] >= '0' && satir[i] <= '9'))
            {
                devam = 0;
            }

            // Rakamlar varsa oku
            while (satir[i] >= '0' && satir[i] <= '9')
            {
                val = val * 10 + (satir[i] - '0');
                i++;
            }

            if (devam)
            {
                if (negatif)
                    val = -val;

                idler[sayac++] = val;

                while (satir[i] == ' ')
                    i++;

                if (satir[i] == ',')
                {
                    i++;
                }
                else
                {
                    devam = 0;
                }
            }
        }

        ky.yazarSayisi = sayac;
        ky.yazarIDler = malloc(sizeof(int) * sayac);
        for (k = 0; k < sayac; k++)
        {
            ky.yazarIDler[k] = idler[k];
        }

        geciciListe = realloc(geciciListe, sizeof(KitapYazar) * (sayi + 1));
        geciciListe[sayi++] = ky;
    }

    fclose(file);

    *liste = geciciListe;
    *adet = sayi;
}

void kitap_yazar_eslestir(Kitap *kitapHead, Yazar *yazarHead)
{
    int i, j, k;
    KitapYazar *liste = NULL;
    int adet = 0;

    kitap_yazar_dosyadan_oku(&liste, &adet);

    char isbn[14];
    int yazarID;

    printf("Kitap ISBN girin: ");
    scanf("%13s", isbn);
    getchar();

    Kitap *kitap = kitapHead;
    while (kitap && strcmp(kitap->ISBN, isbn))
        kitap = kitap->next;

    if (!kitap)
    {
        printf("Kitap bulunamadi.\n");
        free(liste);
        return;
    }

    printf("Yazar ID girin: ");
    scanf("%d", &yazarID);
    getchar();

    Yazar *yazar = yazarHead;
    while (yazar && yazar->yazarID != yazarID)
        yazar = yazar->next;

    if (!yazar)
    {
        printf("Yazar bulunamadi.\n");
        free(liste);
        return;
    }

    int var = 0;
    for (i = 0; i < adet; i++)
    {
        if (strcmp(liste[i].ISBN, isbn) == 0)
        {
            for (j = 0; j < liste[i].yazarSayisi; j++)
            {
                if (liste[i].yazarIDler[j] == yazarID)
                {
                    var = 1;
                }
            }

            if (!var)
            {
                liste[i].yazarIDler = realloc(liste[i].yazarIDler, sizeof(int) * (liste[i].yazarSayisi + 1));
                liste[i].yazarIDler[liste[i].yazarSayisi++] = yazarID;
            }

            kitap_yazar_dosyaya_yaz(liste, adet);
            printf("Eslestirme tamamlandi ve dosyaya yazildi.\n");
            for (k = 0; k < adet; k++)
                free(liste[k].yazarIDler);
            free(liste);
            return;
        }
    }

    liste = realloc(liste, sizeof(KitapYazar) * (adet + 1));
    strcpy(liste[adet].ISBN, isbn);
    liste[adet].yazarSayisi = 1;
    liste[adet].yazarIDler = malloc(sizeof(int));
    liste[adet].yazarIDler[0] = yazarID;
    adet++;

    kitap_yazar_dosyaya_yaz(liste, adet);
    printf("Yeni kitap-yazar eslestirmesi eklendi ve yazildi.\n");

    for (k = 0; k < adet; k++)
        free(liste[k].yazarIDler);
    free(liste);
}

void kitap_yazar_guncelle()
{
    int i;
    KitapYazar *liste = NULL;
    int adet = 0;
    kitap_yazar_dosyadan_oku(&liste, &adet);

    char isbn[14];
    int eskiID, yeniID;
    int guncellendi = 0;

    printf("Guncellenecek kitap ISBN: ");
    scanf("%13s", isbn);
    getchar();

    printf("Eski yazar ID: ");
    scanf("%d", &eskiID);
    getchar();

    printf("Yeni yazar ID: ");
    scanf("%d", &yeniID);
    getchar();

    for (i = 0; i < adet; i++)
    {
        if (strcmp(liste[i].ISBN, isbn) == 0 && liste[i].yazarIDler[0] == eskiID)
        {
            liste[i].yazarIDler[0] = yeniID;
            guncellendi = 1;
        }
    }

    if (guncellendi)
    {
        kitap_yazar_dosyaya_yaz(liste, adet);
        printf("Guncelleme tamamlandi.\n");
    }
    else
    {
        printf("Eslesme bulunamadi.\n");
    }

    for (i = 0; i < adet; i++)
        free(liste[i].yazarIDler);
    free(liste);
}

void yazar_ekle(Yazar **yazarHead)
{
    Yazar *yeni = (Yazar *)malloc(sizeof(Yazar));

    printf("Yazar adini girin: ");
    scanf(" %49[^\n]", yeni->ad);

    printf("Yazar soyadini girin: ");
    scanf(" %49[^\n]", yeni->soyad);

    int maxID = 0;
    Yazar *tmp = *yazarHead;
    while (tmp)
    {
        if (tmp->yazarID > maxID)
            maxID = tmp->yazarID;
        tmp = tmp->next;
    }
    yeni->yazarID = maxID + 1;
    yeni->next = NULL;

    if (*yazarHead == NULL || yeni->yazarID < (*yazarHead)->yazarID)
    {
        yeni->next = *yazarHead;
        *yazarHead = yeni;
    }
    else
    {
        Yazar *current = *yazarHead;
        while (current->next && current->next->yazarID < yeni->yazarID)
        {
            current = current->next;
        }
        yeni->next = current->next;
        current->next = yeni;
    }

    yazar_dosyaya_yaz(*yazarHead);
    printf("Yazar eklendi (ID: %d)\n", yeni->yazarID);
}

void yazar_dosyaya_yaz(Yazar *yazarHead)
{
    FILE *file = fopen("yazarlar.csv", "w");
    if (!file)
        return;

    Yazar *current = yazarHead;
    while (current)
    {
        fprintf(file, "%d,%s,%s\n", current->yazarID, current->ad, current->soyad);
        current = current->next;
    }
    fclose(file);
}

void yazar_sil(Yazar **yazarHead)
{
    int i, j, id;
    printf("Silinecek yazar ID: ");
    scanf("%d", &id);

    Yazar *current = *yazarHead, *prev = NULL;
    while (current && current->yazarID != id)
    {
        prev = current;
        current = current->next;
    }

    if (!current)
    {
        printf("Yazar bulunamadi.\n");
        return;
    }

    if (prev)
        prev->next = current->next;
    else
        *yazarHead = current->next;

    free(current);
    yazar_dosyaya_yaz(*yazarHead);
    printf("Yazar silindi.\n");

    KitapYazar *liste = NULL;
    int adet = 0;
    kitap_yazar_dosyadan_oku(&liste, &adet);

    for (i = 0; i < adet; i++)
    {
        for (j = 0; j < liste[i].yazarSayisi; j++)
        {
            if (liste[i].yazarIDler[j] == id)
                liste[i].yazarIDler[j] = -1;
        }
    }

    kitap_yazar_dosyaya_yaz(liste, adet);

    for (i = 0; i < adet; i++)
        free(liste[i].yazarIDler);
    free(liste);
}

void yazar_guncelle(Yazar *yazarHead)
{
    int id;
    printf("Guncellenecek yazar ID: ");
    scanf("%d", &id);

    Yazar *current = yazarHead;
    while (current && current->yazarID != id)
    {
        current = current->next;
    }

    if (!current)
    {
        printf("Yazar bulunamadi.\n");
        return;
    }

    printf("Yeni ad: ");
    scanf(" %49[^\n]", current->ad);
    printf("Yeni soyad: ");
    scanf(" %49[^\n]", current->soyad);

    yazar_dosyaya_yaz(yazarHead);
    printf("Yazar bilgileri guncellendi.\n");
}

void yazar_listele(Yazar *yazarHead)
{
    printf("\n%-10s %-20s %-20s\n", "Yazar ID", "Ad", "Soyad");
    printf("----------------------------------------------\n");

    Yazar *current = yazarHead;
    while (current)
    {
        printf("%-10d %-20s %-20s\n", current->yazarID, current->ad, current->soyad);
        current = current->next;
    }
}

void yazar_dosyadan_oku(Yazar **yazarHead)
{
    FILE *file = fopen("yazarlar.csv", "r");
    if (!file)
        return;

    Yazar *temp;
    while (*yazarHead)
    {
        temp = *yazarHead;
        *yazarHead = (*yazarHead)->next;
        free(temp);
    }

    Yazar *last = NULL;
    int id;
    char ad[50], soyad[50];

    while (fscanf(file, "%d,%49[^,],%49[^\n]\n", &id, ad, soyad) == 3)
    {
        Yazar *yeni = (Yazar *)malloc(sizeof(Yazar));
        if (!yeni)
        {
            fclose(file);
            return;
        }

        yeni->yazarID = id;
        strcpy(yeni->ad, ad);
        strcpy(yeni->soyad, soyad);
        yeni->next = NULL;

        if (*yazarHead == NULL)
        {
            *yazarHead = yeni;
            last = yeni;
        }
        else
        {
            last->next = yeni;
            last = yeni;
        }
    }

    fclose(file);
}

void yazar_bilgi(Yazar *yazarHead, Kitap *kitapHead, KitapYazar *eslesmeler, int eslesmeSayisi)
{
    int i, j;
    char ad[50];
    printf("Yazar adi girin: ");
    scanf(" %[^\n]", ad);

    int yazarBulundu = 0;
    Yazar *y = yazarHead;

    while (y != NULL)
    {
        if (strcmp(y->ad, ad) == 0)
        {
            yazarBulundu = 1;
            printf("\nYazar ID : %d\n", y->yazarID);
            printf("Ad       : %s\n", y->ad);
            printf("Soyad    : %s\n", y->soyad);
            printf("Yazdigi Kitaplar:\n");

            for (i = 0; i < eslesmeSayisi; i++)
            {
                for (j = 0; j < eslesmeler[i].yazarSayisi; j++)
                {
                    if (eslesmeler[i].yazarIDler[j] == y->yazarID)
                    {
                        Kitap *k = kitapHead;
                        while (k != NULL)
                        {
                            if (strcmp(k->ISBN, eslesmeler[i].ISBN) == 0)
                            {
                                printf(" - Kitap Adi: %s\n", k->ad);
                                printf("   ISBN     : %s\n", k->ISBN);
                                printf("   Adet     : %d\n", k->adet);

                                KitapOrnek *ornek = k->ornekListesi;
                                printf("   Ornekler:\n");
                                while (ornek != NULL)
                                {
                                    printf("     Etiket No: %s | Durum: %s\n", ornek->etiketNo, ornek->durum);
                                    ornek = ornek->next;
                                }
                            }
                            k = k->next;
                        }
                    }
                }
            }
        }

        y = y->next;
    }

    if (!yazarBulundu)
    {
        printf("Bu isimde bir yazar bulunamadi.\n");
    }
}
