#ifndef TUBES_H_INCLUDED
#define TUBES_H_INCLUDED
#include <iostream>
#include <cstdlib>
#include <limits>
#include <conio.h>

using namespace std;

struct ruangan {
    string lantai;
    string noRuangan;
    int kapasitas;
    int harga;
};
struct DataPelanggan{
    string NamaPelanggan;
    string Notelp;
    string IDmember;
    float Diskon;
    string JamMasuk;
    string JamKeluar;
    string ruanganPesanan;
};

typedef struct ElemenRuangan *addressRuangan;
typedef struct ElemenDataPelanggan *addressPelanggan;
typedef struct ElemenRelasi*addressRelasi;
typedef struct ruangan infotypeRuangan;
typedef struct DataPelanggan infotypeDataPelanggan;

struct ElemenRuangan {
    infotypeRuangan info;
    addressRuangan next;
    addressRelasi pesanan;
};
struct ElemenDataPelanggan {
    infotypeDataPelanggan info;
    addressPelanggan next;
    addressPelanggan prev;
};
struct ElemenRelasi{
    addressRelasi next;
    addressPelanggan pemesan;
};
struct ListRuangan {
    addressRuangan first;
};
struct ListPelanggan {
    addressPelanggan first;
    addressPelanggan last;
};


void createListRuangan(ListRuangan &LR);
void createListPelanggan(ListPelanggan &LP);
addressRuangan createElemenRuangan(infotypeRuangan x);
addressPelanggan createElemenPelanggan(infotypeDataPelanggan x);
void insertRuangan(ListRuangan &LR, addressRuangan p);
void insertPelanggan(ListPelanggan &LP, ListRuangan &LR, addressPelanggan q);
void insertRelation(ListPelanggan &LP, ListRuangan &LR, addressPelanggan p);
void deleteRuangan(ListRuangan &LR, ListPelanggan &LP, string ruangan, addressRuangan &p);
void deletePelanggan(ListRuangan &LR, ListPelanggan &LP, string pelanggan, addressPelanggan &q);
void deleteRelasi(ListRuangan &LR, ListPelanggan &LP, string pelanggan, string ruangan, addressRelasi &r);
addressRuangan searchRuangan(ListRuangan LR, string namaRuangan);
addressPelanggan searchPelanggan (ListPelanggan LP, string namaPelanggan);
addressRelasi searchRelasi(ListRuangan LR, ListPelanggan LP, string namaRuang, string namaPelanggan);
void showRuangan(ListRuangan LR);
void showPelanggan(ListPelanggan LP);
void showDataRuanganTertentu(ListRuangan LR);
void showDataSeluruhIsiRuangan(ListRuangan LR);
void showSemuaPesananPelanggan(ListPelanggan LP, ListRuangan LR);
void showDataPelangganTertentu(ListRuangan LR, ListPelanggan LP);
void countPemesanRuangan(ListRuangan &LR);
int countPemesanRuanganTertentu(ListRuangan LR, string namaRuangan);
int countPelangganTidakPesan(ListRuangan LR, ListPelanggan LP);
void tukarRelasi(ListRuangan &LR, ListPelanggan &LP, string pelanggan, string ruanganBaru);
// menu
int selamatDatang();
void pilihanSelamatDatang(ListRuangan &LR, ListPelanggan &LP);
int masukkanData();
void pilihanMasukkanData(ListRuangan &LR, ListPelanggan &LP);
void masukkanDataRuangan(ListRuangan &LR);
void masukkanDataPelanggan(ListPelanggan &LP, ListRuangan &LR);
int tampilanData();
void pilihanTampilanData(ListRuangan &LR, ListPelanggan &LP);
int hitungData();
void pilihanHitungData(ListRuangan &LR, ListPelanggan &LP);
int hapusData();
void pilihanHapusData(ListRuangan &LR, ListPelanggan &LP);
void reschedule(ListRuangan &LR, ListPelanggan &LP);
void clearScreen();


#endif // TUBES_H_INCLUDED
