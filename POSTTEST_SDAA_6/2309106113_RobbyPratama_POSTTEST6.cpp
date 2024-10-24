#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>

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

// Fibonacci Search pada harga kopi
int FibonacciSearch(MenuKopiNode* head, float x, int n) {
    int fib2 = 0;
    int fib1 = 1;
    int fib = fib2 + fib1;

    while (fib < n) {
        fib2 = fib1;
        fib1 = fib;
        fib = fib2 + fib1;
    }

    int offset = -1;

    MenuKopiNode* current = head;
    for (int i = 0; i < n; i++) {
        if (fib > 1) {
            if (current->data.harga < x) {
                fib = fib1;
                fib1 = fib2;
                fib2 = fib - fib1;
                offset = i;
            }
            else if (current->data.harga > x) {
                fib = fib2;
                fib1 -= fib2;
                fib2 = fib - fib1;
            }
            else {
                return i; // Ditemukan
            }
        }
        current = current->next;
    }

    return -1; // Tidak ditemukan
}

// Fungsi untuk Stok Bahan (Stack)
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

// Jump Search pada stok bahan
int JumpSearch(StokBahanNode* head, int x, int n) {
    int step = sqrt(n);
    int prev = 0;

    StokBahanNode* current = head;
    while (current != nullptr && current->data.jumlah_stok < x) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) return -1;
        current = current->next;
    }

    for (int i = prev; i < min(step, n); i++) {
        if (current != nullptr && current->data.jumlah_stok == x)
            return i;
        current = current->next;
    }

    return -1;
}

// Boyer-Moore String Search
int* BoyerMoorePreprocess(const char* pattern) {
    int m = strlen(pattern);
    int* badChar = new int[256];

    for (int i = 0; i < 256; i++)
        badChar[i] = -1;

    for (int i = 0; i < m; i++)
        badChar[(int)pattern[i]] = i;

    return badChar;
}

int BoyerMooreSearch(const char* text, const char* pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    int* badChar = BoyerMoorePreprocess(pattern);

    int s = 0;
    while (s <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[s + j])
            j--;

        if (j < 0) {
            return s; // Pola ditemukan
            s += (s + m < n) ? m - badChar[text[s + m]] : 1;
        }
        else {
            s += max(1, j - badChar[text[s + j]]);
        }
    }

    return -1; // Tidak ditemukan
}

// Menu Utama
int main() {
    MenuKopiNode* menuHead = nullptr;
    StokBahanNode* top = nullptr;

    int pilihan;
    do {
        cout << "\n=== Sistem Manajemen Kafe ===\n";
        cout << "[1] Kelola Menu Kopi\n";
        cout << "[2] Kelola Stok Bahan\n";
        cout << "[3] Cari Kopi atau Stok\n";
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
            int stokChoice;
            do {
                cout << "\n=== Stok Bahan ===\n";
                cout << "[1] Tambah Stok Bahan\n";
                cout << "[2] Tampilkan Stok Bahan\n";
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
                case 0:
                    break;
                default:
                    cout << "Opsi Tidak Valid...Silahkan Coba Lagi...\n";
                }
            } while (stokChoice != 0);
            break;
        }

        case 3: {
            int cariChoice;
            cout << "\n=== Pencarian ===\n";
            cout << "[1] Cari Harga Kopi (Fibonacci Search)\n";
            cout << "[2] Cari Stok Bahan (Jump Search)\n";
            cout << "[3] Cari Nama Kopi atau Bahan (Boyer-Moore Search)\n";
            cout << "Pilih Opsi: ";
            cin >> cariChoice;

            switch (cariChoice) {
            case 1: {
                float harga_dicari;
                cout << "Masukkan harga kopi yang dicari: ";
                cin >> harga_dicari;
                int posisi = FibonacciSearch(menuHead, harga_dicari, 15);  // Misalnya, 15 data menu kopi
                if (posisi != -1)
                    cout << "Kopi dengan harga tersebut ditemukan di posisi: " << posisi << endl;
                else
                    cout << "Kopi dengan harga tersebut tidak ditemukan." << endl;
                break;
            }
            case 2: {
                int stok_dicari;
                cout << "Masukkan stok bahan yang dicari: ";
                cin >> stok_dicari;
                int posisi = JumpSearch(top, stok_dicari, 15);  // Misalnya, 15 data stok bahan
                if (posisi != -1)
                    cout << "Bahan dengan jumlah stok tersebut ditemukan di posisi: " << posisi << endl;
                else
                    cout << "Bahan dengan jumlah stok tersebut tidak ditemukan." << endl;
                break;
            }
            case 3: {
                char nama_dicari[50];
                cout << "Masukkan nama kopi atau bahan yang dicari: ";
                cin >> nama_dicari;
                int posisi = BoyerMooreSearch(menuHead->data.nama_kopi, nama_dicari);
                if (posisi != -1)
                    cout << "Nama tersebut ditemukan." << endl;
                else
                    cout << "Nama tersebut tidak ditemukan." << endl;
                break;
            }
            default:
                cout << "Opsi Tidak Valid...Silahkan Coba Lagi...\n";
            }
            break;
        }

        case 0:
            cout << "Keluar dari Sistem...\n";
            break;
        default:
            cout << "Opsi Tidak Valid...Silahkan Coba Lagi...\n";
        }

    } while (pilihan != 0);

    return 0;
}
