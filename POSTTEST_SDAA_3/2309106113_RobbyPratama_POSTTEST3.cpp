#include <iostream>
#include <cstring>

using namespace std;

// Struktur Menu Kopi
struct MenuKopi {
    char nama_kopi[50];
    float harga;
    int tersedia; // 1 = tersedia, 0 = tidak tersedia
};

// Struktur Pesanan
struct Pesanan {
    char nama_pelanggan[50];
    char nama_kopi[50];
    int jumlah;
    float total_harga;
};

// Struktur Stok Bahan
struct StokBahan {
    char nama_bahan[50];
    int jumlah_stok;
};

// Node untuk Menu Kopi
struct MenuKopiNode {
    MenuKopi data;
    MenuKopiNode* next;
};

// Node untuk Pesanan
struct PesananNode {
    Pesanan data;
    PesananNode* next;
};

// Node untuk Stok Bahan
struct StokBahanNode {
    StokBahan data;
    StokBahanNode* next;
};


void TambahMenuKopi(MenuKopiNode** head) {
    MenuKopiNode* newNode = new MenuKopiNode;
    cout << "Masukkan Nama Kopi: ";
    cin >> newNode->data.nama_kopi;
    cout << "Masukkan Harga: ";
    cin >> newNode->data.harga;
    newNode->data.tersedia = 1;
    newNode->next = *head;
    *head = newNode;
}


void TampilkanMenu(MenuKopiNode* head) {
    cout << "\n=== Daftar Menu Kopi ===\n";
    for (MenuKopiNode* current = head; current != nullptr; current = current->next) {
        cout << "Kopi: " << current->data.nama_kopi << ", Harga: " << current->data.harga
            << ", Ketersediaan: " << (current->data.tersedia ? "Tersedia" : "Habis") << endl;
    }
}


void UpdateMenuKopi(MenuKopiNode* head) {
    char nama_kopi[50];
    cout << "Masukkan Nama Kopi yang ingin diperbarui: ";
    cin >> nama_kopi;

    for (MenuKopiNode* current = head; current != nullptr; current = current->next) {
        if (strcmp(current->data.nama_kopi, nama_kopi) == 0) {
            cout << "Masukkan Harga Baru: ";
            cin >> current->data.harga;
            cout << "Masukkan Ketersediaan (1 = Tersedia, 0 = Tidak Tersedia): ";
            cin >> current->data.tersedia;
            cout << "Menu kopi berhasil diperbarui." << endl;
            return;
        }
    }
    cout << "Kopi tidak ditemukan dalam menu." << endl;
}


void HapusMenuKopi(MenuKopiNode** head) {
    char nama_kopi[50];
    cout << "Masukkan Nama Kopi yang ingin dihapus: ";
    cin >> nama_kopi;

    MenuKopiNode* current = *head;
    MenuKopiNode* prev = nullptr;

    while (current != nullptr && strcmp(current->data.nama_kopi, nama_kopi) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Kopi tidak ditemukan dalam menu." << endl;
        return;
    }

    if (prev == nullptr) {
        *head = current->next;
    }
    else {
        prev->next = current->next;
    }
    delete current;
    cout << "Menu kopi berhasil dihapus." << endl;
}


void TambahPesanan(PesananNode** pesananHead, MenuKopiNode* menuHead) {
    PesananNode* newNode = new PesananNode;
    cout << "Masukkan Nama Pelanggan: ";
    cin >> newNode->data.nama_pelanggan;
    cout << "Masukkan Nama Kopi: ";
    cin >> newNode->data.nama_kopi;
    cout << "Masukkan Jumlah: ";
    cin >> newNode->data.jumlah;


    for (MenuKopiNode* current = menuHead; current != nullptr; current = current->next) {
        if (strcmp(current->data.nama_kopi, newNode->data.nama_kopi) == 0) {
            if (current->data.tersedia) {
                newNode->data.total_harga = newNode->data.jumlah * current->data.harga;
                newNode->next = *pesananHead;
                *pesananHead = newNode;
                cout << "Pesanan berhasil ditambahkan." << endl;
                return;
            }
            else {
                cout << "Kopi tidak tersedia." << endl;
                delete newNode;
                return;
            }
        }
    }
    cout << "Kopi tidak ditemukan dalam menu." << endl;
    delete newNode;
}


void TampilkanPesanan(PesananNode* pesananHead) {
    cout << "\n=== Daftar Pesanan ===\n";
    for (PesananNode* current = pesananHead; current != nullptr; current = current->next) {
        cout << "Pelanggan: " << current->data.nama_pelanggan << ", Kopi: " << current->data.nama_kopi
            << ", Jumlah: " << current->data.jumlah << ", Total Harga: " << current->data.total_harga << endl;
    }
}

void TambahStokBahan(StokBahanNode** stokHead) {
    StokBahanNode* newNode = new StokBahanNode;
    cout << "Masukkan Nama Bahan: ";
    cin >> newNode->data.nama_bahan;
    cout << "Masukkan Jumlah Stok: ";
    cin >> newNode->data.jumlah_stok;
    newNode->next = *stokHead;
    *stokHead = newNode;
}


void TampilkanStokBahan(StokBahanNode* stokHead) {
    cout << "\n=== Daftar Stok Bahan ===\n";
    for (StokBahanNode* current = stokHead; current != nullptr; current = current->next) {
        cout << "Bahan: " << current->data.nama_bahan << ", Jumlah Stok: " << current->data.jumlah_stok << endl;
    }
}


void UpdateStokBahan(StokBahanNode* stokHead) {
    char nama_bahan[50];
    cout << "Masukkan Nama Bahan yang ingin diperbarui: ";
    cin >> nama_bahan;

    for (StokBahanNode* current = stokHead; current != nullptr; current = current->next) {
        if (strcmp(current->data.nama_bahan, nama_bahan) == 0) {
            cout << "Masukkan Jumlah Stok Baru: ";
            cin >> current->data.jumlah_stok;
            cout << "Stok bahan berhasil diperbarui." << endl;
            return;
        }
    }
    cout << "Bahan tidak ditemukan dalam stok." << endl;
}


void HapusStokBahan(StokBahanNode** stokHead) {
    char nama_bahan[50];
    cout << "Masukkan Nama Bahan yang ingin dihapus: ";
    cin >> nama_bahan;

    StokBahanNode* current = *stokHead;
    StokBahanNode* prev = nullptr;

    while (current != nullptr && strcmp(current->data.nama_bahan, nama_bahan) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Bahan tidak ditemukan dalam stok." << endl;
        return;
    }

    if (prev == nullptr) {
        *stokHead = current->next;
    }
    else {
        prev->next = current->next;
    }
    delete current;
    cout << "Stok bahan berhasil dihapus." << endl;
}


void FreeMenu(MenuKopiNode* head) {
    while (head != nullptr) {
        MenuKopiNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void FreePesanan(PesananNode* head) {
    while (head != nullptr) {
        PesananNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void FreeStok(StokBahanNode* head) {
    while (head != nullptr) {
        StokBahanNode* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    MenuKopiNode* menuHead = nullptr;
    PesananNode* pesananHead = nullptr;
    StokBahanNode* stokHead = nullptr;

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
                    TambahMenuKopi(&menuHead);
                    break;
                case 2:
                    TampilkanMenu(menuHead);
                    break;
                case 3:
                    UpdateMenuKopi(menuHead);
                    break;
                case 4:
                    HapusMenuKopi(&menuHead);
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
                    TambahPesanan(&pesananHead, menuHead);
                    break;
                case 2:
                    TampilkanPesanan(pesananHead);
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
                    TambahStokBahan(&stokHead);
                    break;
                case 2:
                    TampilkanStokBahan(stokHead);
                    break;
                case 3:
                    UpdateStokBahan(stokHead);
                    break;
                case 4:
                    HapusStokBahan(&stokHead);
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

    FreeMenu(menuHead);
    FreePesanan(pesananHead);
    FreeStok(stokHead);

    return 0;
}
