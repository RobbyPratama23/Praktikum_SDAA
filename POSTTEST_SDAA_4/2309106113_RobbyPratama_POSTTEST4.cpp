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

// Node untuk Pesanan (Queue)
struct PesananNode {
    Pesanan data;
    PesananNode* next;
};

// Node untuk Stok Bahan (Stack)
struct StokBahanNode {
    StokBahan data;
    StokBahanNode* next;
};

// Fungsi untuk Menu Kopi (Linked List)
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


void TambahPesanan(PesananNode** front, PesananNode** rear, MenuKopiNode* menuHead) {
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
                newNode->next = nullptr;
                if (*rear == nullptr) {
                    *front = *rear = newNode;
                }
                else {
                    (*rear)->next = newNode;
                    *rear = newNode;
                }
                cout << "Pesanan berhasil ditambahkan.\n";
                return;
            }
            else {
                cout << "Kopi tidak tersedia.\n";
                delete newNode;
                return;
            }
        }
    }
    cout << "Kopi tidak ditemukan dalam menu.\n";
    delete newNode;
}

void TampilkanPesanan(PesananNode* front) {
    cout << "\n=== Daftar Pesanan ===\n";
    for (PesananNode* current = front; current != nullptr; current = current->next) {
        cout << "Pelanggan: " << current->data.nama_pelanggan << ", Kopi: " << current->data.nama_kopi
            << ", Jumlah: " << current->data.jumlah << ", Total Harga: " << current->data.total_harga << endl;
    }
}

void HapusPesanan(PesananNode** front, PesananNode** rear) {
    if (*front == nullptr) {
        cout << "Antrian kosong, tidak ada pesanan yang dapat dihapus.\n";
        return;
    }

    PesananNode* temp = *front;
    *front = (*front)->next;

    if (*front == nullptr) {
        *rear = nullptr;
    }

    delete temp;
    cout << "Pesanan pertama berhasil dihapus.\n";
}


void TambahStokBahan(StokBahanNode** top) {
    StokBahanNode* newNode = new StokBahanNode;
    cout << "Masukkan Nama Bahan: ";
    cin >> newNode->data.nama_bahan;
    cout << "Masukkan Jumlah Stok: ";
    cin >> newNode->data.jumlah_stok;
    newNode->next = *top;
    *top = newNode;
}

void TampilkanStokBahan(StokBahanNode* top) {
    cout << "\n=== Daftar Stok Bahan ===\n";
    for (StokBahanNode* current = top; current != nullptr; current = current->next) {
        cout << "Bahan: " << current->data.nama_bahan << ", Jumlah Stok: " << current->data.jumlah_stok << endl;
    }
}

void HapusStokBahan(StokBahanNode** top) {
    if (*top == nullptr) {
        cout << "Stok bahan kosong.\n";
        return;
    }

    StokBahanNode* temp = *top;
    *top = (*top)->next;
    delete temp;

    cout << "Bahan paling atas dihapus dari stok.\n";
}


void FreeMenu(MenuKopiNode* head) {
    while (head != nullptr) {
        MenuKopiNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void FreePesanan(PesananNode* front) {
    while (front != nullptr) {
        PesananNode* temp = front;
        front = front->next;
        delete temp;
    }
}

void FreeStok(StokBahanNode* top) {
    while (top != nullptr) {
        StokBahanNode* temp = top;
        top = top->next;
        delete temp;
    }
}

// Fungsi utama
int main() {
    MenuKopiNode* menuHead = nullptr;
    PesananNode* front = nullptr;
    PesananNode* rear = nullptr;
    StokBahanNode* top = nullptr;

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
                cout << "[3] Hapus Pesanan Pertama\n";
                cout << "[0] Kembali\n";
                cout << "Pilih Opsi: ";
                cin >> pesananChoice;

                switch (pesananChoice) {
                case 1:
                    TambahPesanan(&front, &rear, menuHead);
                    break;
                case 2:
                    TampilkanPesanan(front);
                    break;
                case 3:
                    HapusPesanan(&front, &rear);
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
                cout << "[3] Hapus Bahan Teratas\n";
                cout << "[0] Kembali\n";
                cout << "Pilih Opsi: ";
                cin >> stokChoice;

                switch (stokChoice) {
                case 1:
                    TambahStokBahan(&top);
                    break;
                case 2:
                    TampilkanStokBahan(top);
                    break;
                case 3:
                    HapusStokBahan(&top);
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
            FreeMenu(menuHead);
            FreePesanan(front);
            FreeStok(top);
            cout << "Keluar dari program.\n";
            break;
        default:
            cout << "Opsi Tidak Valid...Silahkan Coba Lagi...\n";
        }
    } while (pilihan != 0);

    return 0;
}
