#include "tubes.h"

void createListRuangan(ListRuangan &LR){
    LR.first = NULL;
}
void createListPelanggan( ListPelanggan &LP){
    LP.first = NULL;
    LP.last = NULL;
};

addressRuangan createElemenRuangan(infotypeRuangan x){
    addressRuangan p = new ElemenRuangan;
    p->info = x;
    p->next = NULL;
    p->pesanan = NULL;
    return p;
};
addressPelanggan createElemenPelanggan(infotypeDataPelanggan x){
    addressPelanggan q = new ElemenDataPelanggan;
    q->info = x;
    q->next = NULL;
    q->prev = NULL;
    return q;
};

void insertRuangan(ListRuangan &LR, addressRuangan p){
    addressRuangan q = LR.first;
    if (LR.first == NULL) {
        LR.first = p;
    } else {
        while (q->next != NULL) {
            q = q->next;
        }
        q->next = p;
    }
};
void insertPelanggan(ListPelanggan &LP, ListRuangan &LR, addressPelanggan q){
    if (LP.first == NULL && LP.last == NULL) {
        LP.first = q;
        LP.last = q;
    } else {
        q->prev = LP.last;
        LP.last->next = q;
        LP.last = q;
    }
    insertRelation(LP, LR, q);
};

void insertRelation(ListPelanggan &LP, ListRuangan &LR, addressPelanggan p) {
    addressRuangan q = searchRuangan(LR, p->info.ruanganPesanan);
    if (q != NULL) {
        addressRelasi r = new ElemenRelasi;
        r->pemesan = p;
        r->next = NULL;

        if (q->pesanan == NULL) {
            q->pesanan = r;
        } else {
            addressRelasi prev = NULL;
            addressRelasi temp = q->pesanan;
            while (temp != NULL && temp->pemesan->info.JamMasuk <= p->info.JamMasuk) {
                prev = temp;
                temp = temp->next;
            }
            if (prev == NULL) {
                r->next = q->pesanan;
                q->pesanan = r;
            } else {
                r->next = temp;
                prev->next = r;
            }
        }
    } else {
        cout << "Tidak bisa melakukan pesanan" << endl;
    }
}

addressRuangan searchRuangan(ListRuangan LR, string namaRuangan){
    addressRuangan p = LR.first;
    while (p != NULL){
        if (p->info.noRuangan== namaRuangan){
            return p;
        }
        p = p->next;
    }
    return NULL;
}
addressPelanggan searchPelanggan (ListPelanggan LP, string namaPelanggan){
    addressPelanggan p = LP.first;
    while (p != NULL){
        if (p->info.NamaPelanggan == namaPelanggan){
            return p;
        }
        p = p->next;
    }
    return NULL;
}
addressRelasi searchRelasi(ListRuangan LR, ListPelanggan LP, string namaRuang, string namaPelanggan){
  addressRuangan cariRuangan = LR.first;
  while (cariRuangan != NULL){
    addressRuangan q = searchRuangan(LR, namaRuang);
    if (q != NULL){
         addressRelasi cariPelanggan = cariRuangan->pesanan;
         while (cariPelanggan != NULL){
            addressPelanggan p = searchPelanggan (LP, namaPelanggan);
            if (p != NULL){
                return cariPelanggan;
            }
            cariPelanggan = cariPelanggan->next;
         }
    }
    cariRuangan = cariRuangan->next;
  }
  return NULL;
}
void deleteRuangan(ListRuangan &LR, ListPelanggan &LP, string ruangan, addressRuangan &p) {
    addressRuangan cari = searchRuangan(LR, ruangan);
    if (cari == NULL) {
        cout << "Ruangan tidak ditemukan!" << endl;
    }
    while (cari->pesanan != NULL) {
        addressRelasi r;
        deleteRelasi(LR, LP, cari->pesanan->pemesan->info.NamaPelanggan, ruangan, r);
    }
    if (cari == LR.first) {
        p = LR.first;
        LR.first = p->next;
    } else {
        addressRuangan prev = LR.first;
        while (prev->next != cari) {
            prev = prev->next;
        }
        p = prev->next;
        prev->next = cari->next;
    }
    p->next = NULL;
    cout << "Ruangan " << ruangan << " berhasil dihapus!" << endl;
}

void deletePelanggan(ListRuangan &LR, ListPelanggan &LP, string pelanggan, addressPelanggan &q) {
    addressPelanggan cari = searchPelanggan(LP, pelanggan);
    if (cari == NULL) {
        cout << "Pelanggan tidak ditemukan!" << endl;
        return;
    }
    addressRuangan p = LR.first;
    while (p != NULL) {
        addressRelasi r = p->pesanan;
        addressRelasi prev = NULL;
        while (r != NULL) {
            if (r->pemesan == cari) {
                addressRelasi temp = r;
                if (prev == NULL) {
                    p->pesanan = r->next;
                } else {
                    prev->next = r->next;
                }
            } else {
                prev = r;
            }
            r = r->next;
        }
        p = p->next;
    }
    if (cari == LP.first && cari == LP.last) {
        q = LP.first;
        LP.first = LP.last = NULL;
    } else if (cari == LP.first) {
        q = LP.first;
        LP.first = q->next;
        LP.first->prev = NULL;
    } else if (cari == LP.last) {
        q = LP.last;
        LP.last = q->prev;
        LP.last->next = NULL;
    } else {
        q = cari;
        cari->prev->next = cari->next;
        cari->next->prev = cari->prev;
    }

    q->next = q->prev = NULL;
    cout << "Pelanggan " << pelanggan << " berhasil dihapus!" << endl;
}

void deleteRelasi(ListRuangan &LR, ListPelanggan &LP, string pelanggan, string ruangan, addressRelasi &r) {
    addressRuangan cariRuangan = searchRuangan(LR, ruangan);
    if (cariRuangan == NULL) {
        cout << "Ruangan tidak ditemukan!" << endl;
        return;
    }

    addressRelasi cariRelasi = cariRuangan->pesanan;
    addressRelasi prevRelasi = NULL;

    while (cariRelasi != NULL && cariRelasi->pemesan->info.NamaPelanggan != pelanggan) {
        prevRelasi = cariRelasi;
        cariRelasi = cariRelasi->next;
    }

    if (cariRelasi == NULL) {
        cout << "Relasi tidak ditemukan!" << endl;
        return;
    }
    if (cariRelasi == cariRuangan->pesanan) {
        r = cariRelasi;
        cariRuangan->pesanan = r->next;
    } else {
        r = cariRelasi;
        prevRelasi->next = r->next;
    }

    r->next = NULL;
    r->pemesan->info.ruanganPesanan = "-";
    cout << "Relasi pelanggan " << pelanggan << " pada ruangan " << ruangan << " berhasil dihapus!" << endl;
}


void showRuangan(ListRuangan LR){
    addressRuangan p = LR.first;
    int i = 1;
    while (p != NULL){
        cout << "---Data pelanggan ke-" << i << "---" << endl;
        cout << "Lantai: " << p->info.lantai << endl;
        cout << "No Ruangan: " << p->info.noRuangan << endl;
        cout << "Kapasitas dalam ruangan: " << p->info.kapasitas << endl;
        cout << "Harga ruangan per jam: " << p->info.harga << endl;
        cout << endl;
        i++;
        p = p->next;
    }
    cout << endl;
}
void showPelanggan(ListPelanggan LP){
    addressPelanggan q = LP.first;
    int i = 1;
    while (q != NULL){
        cout << "---Data pelanggan ke-" << i << "---" << endl;
        cout << "Nama Pelanggan: " << q->info.NamaPelanggan << endl;
        cout << "Nomor Telepon: " << q->info.Notelp << endl;
        cout << "ID Member: " << q->info.IDmember << endl;
        cout << "Potongan Jika Mempunyai Member: " << q->info.Diskon << endl;
        cout << "Jam Masuk: " << q->info.JamMasuk << endl;
        cout << "Jam Keluar: " << q->info.JamKeluar << endl;
        cout << endl;
        i++;
        q = q->next;
    }
    cout << endl;
}

void showDataRuanganTertentu(ListRuangan LR){
    string ruangan;
    cout << "Masukkan ruangan yang ingin ditampilkan: ";
    cin >> ruangan;
    cout << "\nData ruangan " << ruangan << endl;
    addressRuangan q = searchRuangan(LR, ruangan);
    cout << "Lantai: " << q->info.lantai << endl;
    cout << "No Ruangan: " << q->info.noRuangan << endl;
    cout << "Kapasitas dalam ruangan: " << q->info.kapasitas << endl;
    cout << "Harga ruangan per jam: " << q->info.harga << endl;
    cout << endl;
    cout << "Data Pemesan: " << endl;
    if (q != NULL){
        addressRelasi r = q->pesanan;
        int j = 1;
        while (r != NULL){
            cout << "---Data pemesan ke-" << j << "---" << endl;
            cout << "Nama Pelanggan: " << r->pemesan->info.NamaPelanggan << endl;
            cout << "Nomor Telepon: " << r->pemesan->info.Notelp << endl;
            cout << "ID Member: " << r->pemesan->info.IDmember << endl;
            cout << "Potongan Jika Mempunyai Member: " << r->pemesan->info.Diskon << endl;
            cout << "Jam Masuk: " << r->pemesan->info.JamMasuk << endl;
            cout << "Jam Keluar: " << r->pemesan->info.JamKeluar << endl;
            cout << endl;
            j++;
            r = r->next;
        }
    }
}

void showDataSeluruhIsiRuangan(ListRuangan LR){
    addressRuangan q = LR.first;
    int i = 1;
    while (q != NULL){
        cout << "---Data ruangan ke-" << i << "---" << endl;
        cout << "Lantai: " << q->info.lantai << endl;
        cout << "No Ruangan: " << q->info.noRuangan << endl;
        cout << "Kapasitas dalam ruangan: " << q->info.kapasitas << endl;
        cout << "Harga ruangan per jam: " << q->info.harga << endl;
        cout << endl;
        cout << "Data Pemesan: " << endl;
        addressRelasi r = q->pesanan;
        int j = 1;
        while (r != NULL){
            cout << "---Data pemesan ke-" << j << "---" << endl;
            cout << "Nama Pelanggan: " << r->pemesan->info.NamaPelanggan << endl;
            cout << "Nomor Telepon: " << r->pemesan->info.Notelp << endl;
            cout << "ID Member: " << r->pemesan->info.IDmember << endl;
            cout << "Potongan Jika Mempunyai Member: " << r->pemesan->info.Diskon << endl;
            cout << "Jam Masuk: " << r->pemesan->info.JamMasuk << endl;
            cout << "Jam Keluar: " << r->pemesan->info.JamKeluar << endl;
            cout << endl;
            r = r->next;
        }
        cout << endl;
        i++;
        q = q->next;
    }
}

void showSemuaPesananPelanggan(ListPelanggan LP, ListRuangan LR){
    addressPelanggan p = LP.first;
    int i = 1;
    while (p != NULL){
        cout << "---Data Pelanggan ke-" << i << endl;
        cout << "Nama Pelanggan: " << p->info.NamaPelanggan << endl;
        cout << "Nomor Telepon: " << p->info.Notelp << endl;
        cout << "ID Member: " << p->info.IDmember << endl;
        cout << "Potongan Jika Mempunyai Member: " << p->info.Diskon << endl;
        cout << endl;
        cout << "Data pesanan: " << endl;
        bool adaPesanan = false;
        addressRuangan q = LR.first;
        while (q != NULL) {
            addressRelasi r = q->pesanan;
            int j = 1;
            while (r != NULL) {
                if (r->pemesan == p) {
                    adaPesanan = true;
                    cout << "--- Data Pesanan ke-" << j << " ---" << endl;
                    cout << "Lantai: " << q->info.lantai << endl;
                    cout << "No Ruangan: " << q->info.noRuangan << endl;
                    cout << "Kapasitas dalam ruangan: " << q->info.kapasitas << endl;
                    cout << "Harga ruangan per jam: " << q->info.harga << endl;
                    ++j;
                }
                r = r->next;
            }
            q = q->next;
        }

        if (!adaPesanan) {
            cout << p->info.NamaPelanggan << " tidak memesan ruangan" << endl;
        }
        i++;
        p = p->next;
    }
}

void showDataPelangganTertentu(ListRuangan LR, ListPelanggan LP){
    string pelanggan;
    int j =1;
    cout << "Masukkan pelanggan yang ingin ditampilkan: ";
    cin >> pelanggan;
    cout << "\nData pelanggan " << pelanggan << endl;
    addressPelanggan p = searchPelanggan(LP, pelanggan);
    cout << "Nama Pelanggan: " << p->info.NamaPelanggan << endl;
    cout << "Nomor Telepon: " << p->info.Notelp << endl;
    cout << "ID Member: " << p->info.IDmember << endl;
    cout << "Potongan Jika Mempunyai Member: " << p->info.Diskon << endl;
    cout << endl;
    cout << "Data pesanan: " << endl;
    bool adaPesanan = false;
    addressRuangan q = LR.first;
    while (q != NULL) {
        addressRelasi r = q->pesanan;
        while (r != NULL) {
            if (r->pemesan == p) {
                adaPesanan = true;
                cout << "--- Data Pesanan ke-" << j << " ---" << endl;
                cout << "Lantai: " << q->info.lantai << endl;
                cout << "No Ruangan: " << q->info.noRuangan << endl;
                cout << "Kapasitas dalam ruangan: " << q->info.kapasitas << endl;
                cout << "Harga ruangan per jam: " << q->info.harga << endl;
                ++j;
            }
            r = r->next;
        }
        q = q->next;
    }

    if (!adaPesanan) {
        cout << p->info.NamaPelanggan << " tidak memesan ruangan" << endl;
    }
}

void countPemesanRuangan(ListRuangan &LR){
    addressRuangan q = LR.first;
    int jum = 0;
    while (q != NULL){
        cout << "Jumlah pemesan ruangan " << q ->info.noRuangan;
        addressRelasi r = q->pesanan;
        while (r != NULL){
            jum++;
            r = r->next;
        }
        cout << ": " << jum << endl;
        jum = 0;
        q = q->next;
    }
}

int countPemesanRuanganTertentu(ListRuangan LR, string namaRuangan){
    addressRuangan q = searchRuangan(LR, namaRuangan);
    int jum = 0;
    if (q != NULL){
        addressRelasi r = q->pesanan;
        while (r != NULL){
            jum++;
            r = r->next;
        }
    }
    return jum;
}

int countPelangganTidakPesan(ListRuangan LR, ListPelanggan LP) {
    addressPelanggan p = LP.first;
    int count = 0;

    while (p != NULL) {
        bool adaPesanan = false;
        addressRuangan q = LR.first;

        while (q != NULL && !adaPesanan) {
            addressRelasi r = q->pesanan;

            while (r != NULL) {
                if (r->pemesan == p) {
                    adaPesanan = true;
                }
                r = r->next;
            }
            q = q->next;
        }

        if (!adaPesanan) {
            count++;
        }

        p = p->next;
    }

    return count;
}

void tukarRelasi(ListRuangan &LR, ListPelanggan &LP, addressPelanggan p, addressRuangan rLama, addressRuangan rBaru) {
    addressRelasi prev = NULL, temp = rLama->pesanan, tempWaktu = rBaru->pesanan;
    while (temp != NULL && temp->pemesan != p) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        cout << p->info.NamaPelanggan << " tidak memesan di ruangan " << rLama->info.noRuangan << endl;
        return;
    }
    if (prev == NULL) {
        rLama->pesanan = temp->next;
    } else {
        prev->next = temp->next;
    }

    addressRelasi newRelasi = new ElemenRelasi;
    string jamMasukBaru, jamKeluarBaru;
    bool waktuValid = false;

    while (!waktuValid) {
        cout << "Masukkan jam masuk baru: ";
        cin >> jamMasukBaru;
        cout << "Masukkan jam keluar baru: ";
        cin >> jamKeluarBaru;

        tempWaktu = rBaru->pesanan;
        bool waktuTersedia = true;

        while (tempWaktu != NULL) {
            if (jamMasukBaru == tempWaktu->pemesan->info.JamMasuk || jamKeluarBaru == tempWaktu->pemesan->info.JamKeluar) {
                cout << "Waktu sudah terpesan, coba waktu lain." << endl;
                waktuTersedia = false;
            }
            tempWaktu = tempWaktu->next;
        }

        if (waktuTersedia) {
            waktuValid = true;
        }
    }
    p->info.JamMasuk = jamMasukBaru;
    p->info.JamKeluar = jamKeluarBaru;
    p->info.ruanganPesanan = rBaru->info.noRuangan;
    insertRelation(LP, LR, p);

    cout << "Reschedule berhasil." << endl;
}


void clearScreen() {
    system("cls");
}
int selamatDatang(){
    cout << "========================================="<< endl;
    cout << "     SELAMAT DATANG DI KARAOKE KAMI      " << endl;
    cout << endl;
    cout << "1. Masukkan data" << endl;
    cout << "2. Tampilan data" << endl;
    cout << "3. Hitung data" << endl;
    cout << "4. Menghapus data" << endl;
    cout << "5. Reschedule " << endl;
    cout << "0. Exit" << endl;
    cout << "========================================="<< endl;
    cout << "Pilihan: ";
    int input;
    cin >> input;
    cout << endl;
    return input;
}

void pilihanSelamatDatang(ListRuangan &LR, ListPelanggan &LP){
    int pilihan = selamatDatang();
    while (pilihan != 0){
        switch (pilihan){
        case 1:
            clearScreen();
            pilihanMasukkanData(LR, LP);
            break;
        case 2:
            clearScreen();
            pilihanTampilanData(LR, LP);
            break;
        case 3:
            clearScreen();
            pilihanHitungData(LR, LP);
            break;
        case 4:
            clearScreen();
            pilihanHapusData(LR, LP);
            break;
        case 5 :
            clearScreen();
            reschedule(LR, LP);
            break;
        default:
            cout << "Pilihan tidak valid, silahka coba lagi" << endl;
            break;
        }
        pilihan = selamatDatang();
    }
    cout << "Terima kasih, semoga datang kembali" << endl;
    clearScreen();
}

int masukkanData(){
    cout << "===============================" << endl;
    cout << "1. Masukkan data ruangan" << endl;
    cout << "2. Masukkan data pelanggan" << endl;
    cout << "3. Kembali" << endl;
    cout << "0. Exit" << endl;
    cout << "===============================" << endl;
    cout << "Pilihan: ";
    int input;
    cin >> input;
    cout << endl;
    return input;
}

void pilihanMasukkanData(ListRuangan &LR, ListPelanggan &LP){
    int pilihan;
    pilihan = masukkanData();
    while (pilihan != 0){
        switch (pilihan) {
        case 1:
            masukkanDataRuangan(LR);
            break;
        case 2:
            masukkanDataPelanggan(LP, LR);
            break;
        case 3 :
            clearScreen();
            pilihanSelamatDatang(LR, LP);
            break;
        default :
            cout << "Pilihan tidak valid, silahka coba lagi" << endl;
            break;
        }
        pilihan = masukkanData();
    }
    cout << "Terima kasih, semoga datang kembali" << endl;
    clearScreen();
}

void masukkanDataRuangan(ListRuangan &LR){
    infotypeRuangan data;
    cout << "Masukkan lantai ruangan: ";
    cin >> data.lantai;
    cout << "Masukkan nomor ruangan: ";
    cin >> data.noRuangan;
    cout << "Masukkan kapasitas ruangan: ";
    cin >> data.kapasitas;
    if (data.kapasitas == 5){
        data.harga = 35000;
    } else{
        data.harga = 55000;
    }
    addressRuangan q = createElemenRuangan(data);
    insertRuangan(LR, q);
}

void masukkanDataPelanggan(ListPelanggan &LP, ListRuangan &LR) {
    infotypeDataPelanggan data;
    cout << "Masukkan nama pelanggan: ";
    cin >> data.NamaPelanggan;
    cout << "Masukkan nomor telepon pelanggan: ";
    cin >> data.Notelp;
    cout << "Apakah pelanggan memiliki member (yes/no)? ";
    string member;
    cin >> member;

    if (member == "yes") {
        cout << "Masukkan ID member pelanggan: ";
        cin >> data.IDmember;
        data.Diskon = 0.05;
    } else {
        data.IDmember = "-";
        data.Diskon = 0;
    }

    cout << "Masukkan ruangan pesanan pelanggan: ";
    cin >> data.ruanganPesanan;

    addressRuangan rBaru = searchRuangan(LR, data.ruanganPesanan);
    string jamMasukBaru, jamKeluarBaru;
    bool waktuValid = false;

    while (!waktuValid) {
        cout << "Masukkan jam masuk baru: ";
        cin >> jamMasukBaru;
        cout << "Masukkan jam keluar baru: ";
        cin >> jamKeluarBaru;

        addressRelasi tempWaktu = rBaru->pesanan;
        bool waktuTersedia = true;
        while (tempWaktu != NULL) {
            if ((jamMasukBaru >= tempWaktu->pemesan->info.JamMasuk && jamMasukBaru < tempWaktu->pemesan->info.JamKeluar) ||
                (jamKeluarBaru > tempWaktu->pemesan->info.JamMasuk && jamKeluarBaru <= tempWaktu->pemesan->info.JamKeluar)) {
                cout << "Waktu sudah terpesan, coba waktu lain." << endl;
                waktuTersedia = false;
            }
            tempWaktu = tempWaktu->next;
        }

        if (waktuTersedia) {
            waktuValid = true;
        }
    }
    data.JamMasuk = jamMasukBaru;
    data.JamKeluar = jamKeluarBaru;
    addressPelanggan p = createElemenPelanggan(data);
    insertPelanggan(LP, LR, p);
}

int tampilanData(){
    cout << "================================================"<<endl;
    cout << "1. Tampilkan semua ruangan" << endl;
    cout << "2. Tampilkan semua pelanggan" << endl;
    cout << "3. Tampilakan pemesan ruangan tertentu" << endl;
    cout << "4. Tampilkan seluruh pemesan setiap ruangan" << endl;
    cout << "5. Tampilkan pesanan semua pelanggan" << endl;
    cout << "6. Tampilkan pesanan pelanggan tertentu" << endl;
    cout << "7. Kembali" << endl;
    cout << "0. Exit" << endl;
    cout << "================================================"<<endl;
    cout << "Pilihan: ";
    int pilihan;
    cin >> pilihan;
    cout << endl;
    return pilihan;
}

void pilihanTampilanData(ListRuangan &LR, ListPelanggan &LP){
    int pilihan;
    pilihan = tampilanData();
    while (pilihan != 0){
        switch (pilihan){
        case 1:
            showRuangan(LR);
            break;
        case 2:
            showPelanggan(LP);
            break;
        case 3:
            showDataRuanganTertentu(LR);
            break;
        case 4:
            showDataSeluruhIsiRuangan(LR);
            break;
        case 5 :
            showSemuaPesananPelanggan(LP, LR);
            break;
        case 6 :
            showDataPelangganTertentu(LR, LP);
            break;
        case 7 :
            clearScreen();
            pilihanSelamatDatang(LR, LP);
            break;
        default:
            cout << "Pilihan tidak valid, silahka coba lagi" << endl;
            break;
        }
        pilihan = tampilanData();
    }
    cout << "Terima kasih, semoga datang kembali" << endl;
    clearScreen();
}

int hitungData(){
    cout << "=========================================" << endl;
    cout << "1. Hitung pemesan setiap ruangan " << endl;
    cout << "2. Hitung pemesan ruangan tertentu" << endl;
    cout << "3. Hitung pelanggan yang tidak pesan" << endl;
    cout << "4. Kembali" << endl;
    cout << "0. Exit" << endl;
    cout << "=========================================" << endl;
    cout << "Pilihan: ";
    int input;
    cin >> input;
    cout << endl;
    return input;
}

void pilihanHitungData(ListRuangan &LR, ListPelanggan &LP){
    int pilihan;
    string ruangan;
    pilihan = hitungData();
    while (pilihan != 0){
        switch (pilihan){
        case 1:
           countPemesanRuangan(LR);
            break;
        case 2:
            cout << "Masukkan ruangan yang ingin dihitung: ";
            cin >> ruangan;
            cout << "Pemesan ruangan "<< ruangan<<" berjumlah "<< countPemesanRuanganTertentu(LR, ruangan) << " orang" << endl;
            break;
        case 3:
            cout << "Jumlah pelanggan tidak pesan: " << countPelangganTidakPesan(LR, LP)<< endl;;
            break;
        case 4:
            clearScreen();
            pilihanSelamatDatang(LR, LP);
            break;
        default:
            cout << "Pilihan tidak valid, silahka coba lagi" << endl;
            break;
        }
        pilihan = hitungData();
    }
    cout << "Terima kasih, semoga datang kembali" << endl;
    clearScreen();
}

int hapusData(){
    cout << "===============================" << endl;
    cout << "1. Hapus Ruangan " << endl;
    cout << "2. Hapus pelanggan" << endl;
    cout << "3. Pelanggan tidak jadi pesan" << endl;
    cout << "4. Kembali" << endl;
    cout << "0. Exit" << endl;
    cout << "===============================" << endl;
    cout << "Pilihan: ";
    int input;
    cin >> input;
    cout << endl;
    return input;
}

void pilihanHapusData(ListRuangan &LR, ListPelanggan &LP){
    int pilihan;
    string ruangan, pelanggan;
    addressPelanggan p;
    addressRuangan q;
    addressRelasi r;
    pilihan = hapusData();
    while (pilihan != 0){
        switch(pilihan){
        case 1:
            cout << "Masukkan ruangan yang ingin dihapus: ";
            cin >> ruangan;
            deleteRuangan(LR, LP, ruangan, q);
            cout << q->info.noRuangan << " sudah terhapus" << endl;
            break;
        case 2:
            cout << "Masukkan pelanggan yang ingin dihapus: ";
            cin >> pelanggan;
            deletePelanggan(LR, LP, pelanggan, p);
            cout << p->info.NamaPelanggan << " sudah terhapus" << endl;
            break;
        case 3:
            cout << "Masukkan pelanggan yang tidak jadi pesan: "<< endl;
            cin >> pelanggan;
            cout << "Masukkan ruangan yang dipesan pelanggan sebelumnya: "<< endl;
            cin >> ruangan;
            deleteRelasi(LR, LP, pelanggan, ruangan, r);
            cout << "pesanan " << pelanggan << " di ruang " << ruangan << " sudah terhapus" << endl;
        case 4:
            clearScreen();
            pilihanSelamatDatang(LR, LP);
        default:
            cout << "Pilihan tidak valid, silahka coba lagi" << endl;
            break;
        }
        pilihan = hapusData();
    }
    cout << "Terima kasih, semoga datang kembali" << endl;
    clearScreen();

}

void reschedule(ListRuangan &LR, ListPelanggan &LP) {
    string pelanggan, ruanganBaru, pilihan;
    cout << "Masukkan pelanggan yang ingin reschedule: ";
    cin >> pelanggan;

    addressPelanggan p = searchPelanggan(LP, pelanggan);
    if (p == NULL) {
        cout << "Pelanggan tidak ditemukan!" << endl;

    }

    cout << "Masukkan ruangan baru yang ingin di reschedule: ";
    cin >> ruanganBaru;

    addressRuangan rBaru = searchRuangan(LR, ruanganBaru);
    if (rBaru == NULL) {
        cout << "Ruangan tidak ditemukan!" << endl;

    }

    addressRuangan rLama = searchRuangan(LR, p->info.ruanganPesanan);
    if (rLama == NULL) {
        cout << "Ruangan lama tidak ditemukan untuk pelanggan ini!" << endl;
    }

    tukarRelasi(LR, LP, p, rLama, rBaru);

    cout << "Ingin kembali (yes/no)? ";
    cin >> pilihan;
    while (pilihan != "yes" && pilihan != "no") {
        cout << "Pilihan tidak valid, masukkan 'yes' atau 'no': ";
        cin >> pilihan;
    }

    if (pilihan == "yes") {
        clearScreen();
        pilihanSelamatDatang(LR, LP);
    } else {
        reschedule(LR, LP);
    }
}

