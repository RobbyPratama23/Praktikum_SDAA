#include <iostream>
#include <string.h>

using namespace std;

// Struct Menu Kopi
struct MenuKopi {
    char nama_kopi[50];
    float harga;
    int tersedia; // 1 = tersedia, 0 = tidak tersedia
};

// Struct Pesanan
struct Pesanan {
    char nama_pelanggan[50];
    char nama_kopi[50];
    int jumlah;
    float total_harga;
};

// Struct Stok Bahan
struct StokBahan {
    char nama_bahan[50];
    int jumlah_stok;
};

void TambahMenuKopi(MenuKopi* Menu, int* JumlahMenu) {
    if (*JumlahMenu < 100) {
        cout << "Masukkan Nama Kopi: ";
        cin >> Menu[*JumlahMenu].nama_kopi;
        cout << "Masukkan Harga: ";
        cin >> Menu[*JumlahMenu].harga;
        Menu[*JumlahMenu].tersedia = 1;
        (*JumlahMenu)++;
    }
    else {
        cout << "Menu penuh, tidak bisa menambah kopi baru." << endl;
    }
}

void TampilkanMenu(MenuKopi* Menu, int JumlahMenu) {
    cout << "\n=== Daftar Menu Kopi ===\n";
    for (int i = 0; i < JumlahMenu; i++) {
        cout << "Kopi: " << Menu[i].nama_kopi << ", Harga: " << Menu[i].harga
            << ", Ketersediaan: " << (Menu[i].tersedia ? "Tersedia" : "Habis") << endl;
    }
}

void UpdateMenuKopi(MenuKopi* Menu, int JumlahMenu) {
    char nama_kopi[50];
    cout << "Masukkan Nama Kopi yang ingin diperbarui: ";
    cin >> nama_kopi;

    for (int i = 0; i < JumlahMenu; i++) {
        if (strcmp(Menu[i].nama_kopi, nama_kopi) == 0) {
            cout << "Masukkan Harga Baru: ";
            cin >> Menu[i].harga;
            cout << "Masukkan Ketersediaan (1 = Tersedia, 0 = Tidak Tersedia): ";
            cin >> Menu[i].tersedia;
            cout << "Menu kopi berhasil diperbarui." << endl;
            return;
        }
    }
    cout << "Kopi tidak ditemukan dalam menu." << endl;
}

void HapusMenuKopi(MenuKopi* Menu, int* JumlahMenu) {
    char nama_kopi[50];
    cout << "Masukkan Nama Kopi yang ingin dihapus: ";
    cin >> nama_kopi;

    for (int i = 0; i < *JumlahMenu; i++) {
        if (strcmp(Menu[i].nama_kopi, nama_kopi) == 0) {
            for (int j = i; j < *JumlahMenu - 1; j++) {
                Menu[j] = Menu[j + 1];
            }
            (*JumlahMenu)--;
            cout << "Menu kopi berhasil dihapus." << endl;
            return;
        }
    }
    cout << "Kopi tidak ditemukan dalam menu." << endl;
}

void TambahPesanan(Pesanan* pesanan, int* JumlahPesanan, MenuKopi* Menu, int JumlahMenu) {
    if (*JumlahPesanan < 100) {
        cout << "Masukkan Nama Pelanggan: ";
        cin >> pesanan[*JumlahPesanan].nama_pelanggan;
        cout << "Masukkan Nama Kopi: ";
        cin >> pesanan[*JumlahPesanan].nama_kopi;
        cout << "Masukkan Jumlah: ";
        cin >> pesanan[*JumlahPesanan].jumlah;

        for (int i = 0; i < JumlahMenu; i++) {
            if (strcmp(Menu[i].nama_kopi, pesanan[*JumlahPesanan].nama_kopi) == 0) {
                if (Menu[i].tersedia) {
                    pesanan[*JumlahPesanan].total_harga = pesanan[*JumlahPesanan].jumlah * Menu[i].harga;
                    (*JumlahPesanan)++;
                }
                else {
                    cout << "Kopi tidak tersedia." << endl;
                }
                return;
            }
        }
        cout << "Kopi tidak ditemukan dalam menu." << endl;
    }
    else {
        cout << "Pesanan penuh, tidak bisa menambah pesanan baru." << endl;
    }
}

void TampilkanPesanan(Pesanan* pesanan, int JumlahPesanan) {
    cout << "\n=== Daftar Pesanan ===\n";
    for (int i = 0; i < JumlahPesanan; i++) {
        cout << "Pelanggan: " << pesanan[i].nama_pelanggan << ", Kopi: " << pesanan[i].nama_kopi
            << ", Jumlah: " << pesanan[i].jumlah << ", Total Harga: " << pesanan[i].total_harga << endl;
    }
}

void TambahStokBahan(StokBahan* stokbahan, int* JumlahBahan) {
    if (*JumlahBahan < 50) {
        cout << "Masukkan Nama Bahan: ";
        cin >> stokbahan[*JumlahBahan].nama_bahan;
        cout << "Masukkan Jumlah Stok: ";
        cin >> stokbahan[*JumlahBahan].jumlah_stok;
        (*JumlahBahan)++;
    }
    else {
        cout << "Stok bahan penuh, tidak bisa menambah bahan baru." << endl;
    }
}

void TampilkanStokBahan(StokBahan* stokbahan, int JumlahBahan) {
    cout << "\n=== Daftar Stok Bahan ===\n";
    for (int i = 0; i < JumlahBahan; i++) {
        cout << "Bahan: " << stokbahan[i].nama_bahan << ", Jumlah Stok: " << stokbahan[i].jumlah_stok << endl;
    }
}

void UpdateStokBahan(StokBahan* stokbahan, int JumlahBahan) {
    char nama_bahan[50];
    cout << "Masukkan Nama Bahan yang ingin diperbarui: ";
    cin >> nama_bahan;

    for (int i = 0; i < JumlahBahan; i++) {
        if (strcmp(stokbahan[i].nama_bahan, nama_bahan) == 0) {
            cout << "Masukkan Jumlah Stok Baru: ";
            cin >> stokbahan[i].jumlah_stok;
            cout << "Stok bahan berhasil diperbarui." << endl;
            return;
        }
    }
    cout << "Bahan tidak ditemukan dalam stok." << endl;
}

void HapusStokBahan(StokBahan* stokbahan, int* JumlahBahan) {
    char nama_bahan[50];
    cout << "Masukkan Nama Bahan yang ingin dihapus: ";
    cin >> nama_bahan;

    for (int i = 0; i < *JumlahBahan; i++) {
        if (strcmp(stokbahan[i].nama_bahan, nama_bahan) == 0) {
            for (int j = i; j < *JumlahBahan - 1; j++) {
                stokbahan[j] = stokbahan[j + 1];
            }
            (*JumlahBahan)--;
            cout << "Stok bahan berhasil dihapus." << endl;
            return;
        }
    }
    cout << "Bahan tidak ditemukan dalam stok." << endl;
}

int main() {
    MenuKopi Menu[100];
    Pesanan pesanan[100];
    StokBahan stokbahan[50];

    int JumlahMenu = 0, JumlahPesanan = 0, JumlahBahan = 0;
    int pilihan;

    do {
        cout << "\n=== Coffee Shop Management System ===\n";
        cout << "[1] Menu Kopi\n";
        cout << "[2] Pesanan\n";
        cout << "[3] Stok Bahan\n";
        cout << "[0] Keluar\n";
        cout << "Pilih Opsi: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1: {
            int menuChoice;
            do {
                cout << "\n=== Menu Kopi ===\n";
                cout << "[1] Tambah Menu Kopi\n";
                cout << "[2] Tampilkan Menu Kopi\n";
                cout << "[3] Update Menu Kopi\n";
                cout << "[4] Hapus Menu Kopi\n";
                cout << "[0] Kembali\n";
                cout << "Pilih Opsi: ";
                cin >> menuChoice;

                switch (menuChoice) {
                case 1:
                    TambahMenuKopi(Menu, &JumlahMenu);
                    break;
                case 2:
                    TampilkanMenu(Menu, JumlahMenu);
                    break;
                case 3:
                    TampilkanMenu(Menu, JumlahMenu);
                    UpdateMenuKopi(Menu, JumlahMenu);
                    break;
                case 4:
                    TampilkanMenu(Menu, JumlahMenu);
                    HapusMenuKopi(Menu, &JumlahMenu);
                    break;
                case 0:
                    break;
                default:
                    cout << "Opsi Tidak Valid...Silahkan Coba Lagi...\n";
                }
            } while (menuChoice != 0);
            break;
        }
        case 2: {
            int pesananChoice;
            do {
                cout << "\n=== Pesanan ===\n";
                cout << "[1] Tambah Pesanan\n";
                cout << "[2] Tampilkan Pesanan\n";
                cout << "[0] Kembali\n";
                cout << "Pilih Opsi: ";
                cin >> pesananChoice;

                switch (pesananChoice) {
                case 1:
                    TambahPesanan(pesanan, &JumlahPesanan, Menu, JumlahMenu);
                    break;
                case 2:
                    TampilkanPesanan(pesanan, JumlahPesanan);
                    break;
                case 0:
                    break;
                default:
                    cout << "Opsi Tidak Valid...Silahkan Coba Lagi...\n";
                }
            } while (pesananChoice != 0);
            break;
        }
        case 3: {
            int stokChoice;
            do {
                cout << "\n=== Stok Bahan ===\n";
                cout << "[1] Tambah Stok Bahan\n";
                cout << "[2] Tampilkan Stok Bahan\n";
                cout << "[3] Update Stok Bahan\n";
                cout << "[4] Hapus Stok Bahan\n";
                cout << "[0] Kembali\n";
                cout << "Pilih Opsi: ";
                cin >> stokChoice;

                switch (stokChoice) {
                case 1:
                    TambahStokBahan(stokbahan, &JumlahBahan);
                    break;
                case 2:
                    TampilkanStokBahan(stokbahan, JumlahBahan);
                    break;
                case 3:
                    TampilkanStokBahan(stokbahan, JumlahBahan);
                    UpdateStokBahan(stokbahan, JumlahBahan);
                    break;
                case 4:
                    TampilkanStokBahan(stokbahan, JumlahBahan);
                    HapusStokBahan(stokbahan, &JumlahBahan);
                    break;
                case 0:
                    break;
                default:
                    cout << "Opsi Tidak Valid...Silahkan Coba Lagi...\n";
                }
            } while (stokChoice != 0);
            break;
        }
        case 0:
            cout << "Keluar dari Program...\n";
            break;
        default:
            cout << "Opsi Tidak Valid...Silahkan Coba Lagi...\n";
        }
    } while (pilihan != 0);

    return 0;
}
