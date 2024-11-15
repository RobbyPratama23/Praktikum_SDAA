#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <cstdlib>
using namespace std;

const int MAX_COFFEE = 100; // Maksimum jumlah kopi dalam menu
const int MAX_INGREDIENTS_PER_COFFE = 5; //Maksimum bahan baku per kopi

// Struktur untuk Bahan Baku
struct Ingredient {
    int id;
    string name;
    int stock;
    Ingredient* next;

    Ingredient(int i, string n, int s) : id(i), name(n), stock(s), next(nullptr) {}
};

// Struktur untuk Resep
struct Recipe {
    int ingredientId;
    int amount;
};

// Struktur untuk Menu Kopi
struct Coffee {
    int id;
    string name;
    double price;
    double discount; // Diskon, jika di isi 10 maka diskon 10%
    Recipe recipes[MAX_INGREDIENTS_PER_COFFE]; // Array resep bahan baku yang dibutuhkan
    int recipeCount; // Jumlah bahan baku yang di gunakan
};

// Struktur untuk Pesanan
struct Order {
    int id;
    string customerName;
    Coffee coffee;
    int quantity;
    double totalPrice;

    Order(int i, string name, Coffee c, int q)
        : id(i), customerName(name), coffee(c), quantity(q) {
        totalPrice = coffee.price * quantity;
    }
};

class CoffeeShopSystem {
private:
    Coffee coffeeMenu[MAX_COFFEE];
    int coffeeCount;
    Ingredient* ingredientHead;
    queue<Order> orderQueue;
    stack<Order> orderHistory;
    int nextOrderId;

    // Fungsi helper untuk mencari bahan baku berdasarkan ID
    Ingredient* findIngredient(int id) {
        Ingredient* current = ingredientHead;
        while (current != nullptr) {
            if (current->id == id) return current;
            current = current->next;
        }
        return nullptr;
    }

public:
    CoffeeShopSystem() : coffeeCount(0), ingredientHead(nullptr), nextOrderId(1) {}

    // Fungsi Admin: Menambah Kopi
    void addCoffee(string name, double price) {
        if (coffeeCount >= MAX_COFFEE) {
            cout << "Menu kopi sudah penuh.\n";
            return;
        }

        Coffee coffee;
        coffee.id = coffeeCount + 1;
        coffee.name = name;
        coffee.price = price;
        coffee.recipeCount = 0;

        // Menampilkan daftar bahan baku yang tersedia
        displayIngredients();

        cout << "Masukkan jumlah jenis bahan baku yang dibutuhkan: ";
        int numIngredients;
        cin >> numIngredients;

        if (numIngredients > MAX_INGREDIENTS_PER_COFFE) {
            cout << "Jumlah bahan baku melebihi batas maksimum.\n";
            return;
        }

        for (int i = 0; i < numIngredients; i++) {
            cout << "Masukkan ID bahan baku ke-" << (i + 1) << ": ";
            int ingredientId;
            cin >> ingredientId;

            cout << "Masukkan jumlah yang dibutuhkan: ";
            int amount;
            cin >> amount;

            // Validasi bahan baku
            if (findIngredient(ingredientId) == nullptr) {
                cout << "Bahan baku dengan ID " << ingredientId << " tidak ditemukan.\n";
                return;
            }

            coffee.recipes[i].ingredientId = ingredientId;
            coffee.recipes[i].amount = amount;
            coffee.recipeCount++;
        }

        coffeeMenu[coffeeCount++] = coffee;
        cout << "Kopi berhasil ditambahkan ke menu.\n";
    }

    // Fungsi Admin: Menampilkan Menu Kopi
    void displayCoffees() {
        if (coffeeCount == 0) {
            cout << "Menu kopi kosong.\n";
            return;
        }

        cout << "\n=== DAFTAR MENU KOPI ===\n";
        for (int i = 0; i < coffeeCount; ++i) {
            Coffee& coffee = coffeeMenu[i];
            double finalPrice = coffee.price;

            // Menghitung harga setelah diskon jika ada diskon
            if (coffee.discount > 0) {
                finalPrice = coffee.price * (1 - (coffee.discount / 100.0));
                cout << "ID Kopi: " << (i + 1) << "\n"
                    << "Nama Kopi: " << coffee.name << "\n"
                    << "Harga Asli: Rp " << coffee.price << "\n"
                    << "Diskon: " << coffee.discount << "%\n"
                    << "Harga Setelah Diskon: Rp " << finalPrice << "\n";
            }
            else {
                cout << "ID Kopi: " << (i + 1) << "\n"
                    << "Nama Kopi: " << coffee.name << "\n"
                    << "Harga: Rp " << coffee.price << "\n";
            }

            // Menampilkan bahan baku yang diperlukan
            cout << "Bahan Baku:\n";
            for (int j = 0; j < coffee.recipeCount; ++j) {
                Recipe recipe = coffee.recipes[j];
                Ingredient* ingredient = findIngredient(recipe.ingredientId);
                if (ingredient != nullptr) {
                    cout << "   - " << ingredient->name
                        << ": " << recipe.amount << " unit\n";
                }
            }
            cout << endl;
        }
    }

    void displayCoffeesNoDetail() {
        if (coffeeCount == 0) {
            cout << "Menu kopi kosong.\n";
            return;
        }

        cout << "\n=== DAFTAR MENU KOPI ===\n";
        for (int i = 0; i < coffeeCount; ++i) {
            Coffee& coffee = coffeeMenu[i];
            double finalPrice = coffee.price;

            // Menghitung harga setelah diskon jika ada diskon
            if (coffee.discount > 0) {
                finalPrice = coffee.price * (1 - (coffee.discount / 100.0));
                cout << "ID Kopi: " << (i + 1) << "\n"
                    << "Nama Kopi: " << coffee.name << "\n"
                    << "Harga Asli: Rp " << coffee.price << "\n"
                    << "Diskon: " << coffee.discount << "%\n"
                    << "Harga Setelah Diskon: Rp " << finalPrice << "\n";
            }
            else {
                cout << "ID Kopi: " << (i + 1) << "\n"
                    << "Nama Kopi: " << coffee.name << "\n"
                    << "Harga: Rp " << coffee.price << "\n";
            }
            cout << endl;
        }
    }



    // Fungsi Admin: Menambah Bahan Baku
    void addIngredient(string name, int stock) {
        int id = 1;
        Ingredient* current = ingredientHead;
        while (current != nullptr) {
            id++;
            current = current->next;
        }

        Ingredient* newIngredient = new Ingredient(id, name, stock);
        if (ingredientHead == nullptr) {
            ingredientHead = newIngredient;
        }
        else {
            current = ingredientHead;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newIngredient;
        }
        cout << "Bahan baku berhasil ditambahkan.\n";
    }

    // Fungsi Admin: Menampilkan Bahan Baku
    void displayIngredients() {
        if (ingredientHead == nullptr) {
            cout << "Belum ada bahan baku.\n";
            return;
        }

        cout << "\n=== STOK BAHAN BAKU ===\n";
        Ingredient* current = ingredientHead;
        while (current != nullptr) {
            cout << current->id << ". "
                << current->name << " - Stok: "
                << current->stock << endl;
            current = current->next;
        }
    }

    // Fungsi Pelanggan: Menambah Pesanan
    void addOrder(string customerName, int coffeeId, int quantity) {
        if (coffeeId < 1 || coffeeId > coffeeCount) {
            cout << "Kopi tidak ditemukan.\n";
            return;
        }

        Coffee selectedCoffee = coffeeMenu[coffeeId - 1];

        // Cek ketersediaan bahan baku
        for (int i = 0; i < selectedCoffee.recipeCount; i++) {
            Recipe recipe = selectedCoffee.recipes[i];
            Ingredient* ingredient = findIngredient(recipe.ingredientId);

            if (ingredient == nullptr || ingredient->stock < recipe.amount * quantity) {
                cout << "Stok bahan baku " << (ingredient ? ingredient->name : "tidak ditemukan")
                    << " tidak mencukupi untuk pesanan ini.\n";
                return;
            }
        }

        // Kurangi stok bahan baku
        for (int i = 0; i < selectedCoffee.recipeCount; i++) {
            Recipe recipe = selectedCoffee.recipes[i];
            Ingredient* ingredient = findIngredient(recipe.ingredientId);
            if (ingredient != nullptr) {
                ingredient->stock -= recipe.amount * quantity;
            }
        }

        // Buat pesanan dan tambahkan ke antrean dan riwayat
        Order newOrder(nextOrderId++, customerName, selectedCoffee, quantity);
        orderQueue.push(newOrder);
        orderHistory.push(newOrder); // Langsung menambah ke riwayat pesanan sebagai selesai

        cout << "Pesanan berhasil dibuat:\n";
        cout << "Nomor Pesanan: #" << newOrder.id << endl;
        cout << "Total: Rp" << newOrder.totalPrice << endl;
    }

    // Fungsi Admin: Memperbarui Stok Bahan Baku
    void updateIngredientStock() {
        if (ingredientHead == nullptr) {
            cout << "Belum ada bahan baku untuk diperbarui.\n";
            return;
        }

        displayIngredients();
        cout << "\nMasukkan ID bahan baku yang stoknya ingin ditambah: ";
        int ingredientId;
        cin >> ingredientId;

        Ingredient* ingredient = findIngredient(ingredientId);
        if (ingredient == nullptr) {
            cout << "Bahan baku dengan ID " << ingredientId << " tidak ditemukan.\n";
            return;
        }

        cout << "Masukkan jumlah stok yang akan ditambah untuk " << ingredient->name << ": ";
        int additionalStock;
        cin >> additionalStock;

        ingredient->stock += additionalStock;
        cout << "Stok untuk " << ingredient->name << " berhasil diperbarui menjadi " << ingredient->stock << ".\n";
    }

    // Fungsi Perbarui Kopi
    void updateCoffee() {
        displayCoffees();
        cout << "\nMasukkan ID kopi yang ingin diperbarui: ";
        int coffeeId;
        cin >> coffeeId;

        if (coffeeId < 1 || coffeeId > coffeeCount) {
            cout << "Kopi tidak ditemukan.\n";
            return;
        }

        Coffee& coffee = coffeeMenu[coffeeId - 1];

        cout << "Nama kopi saat ini: " << coffee.name << "\nMasukkan nama baru: ";
        cin.ignore();
        getline(cin, coffee.name);

        cout << "Harga saat ini: Rp" << coffee.price << "\nMasukkan harga baru: ";
        cin >> coffee.price;

        // Memperbarui resep bahan baku
        cout << "Apakah ingin memperbarui resep? (1 = Ya, 0 = Tidak): ";
        int updateRecipe;
        cin >> updateRecipe;

        if (updateRecipe == 1) {
            coffee.recipeCount = 0;
            displayIngredients();

            cout << "Masukkan jumlah jenis bahan baku yang dibutuhkan: ";
            int numIngredients;
            cin >> numIngredients;

            for (int i = 0; i < numIngredients; i++) {
                cout << "Masukkan ID bahan baku ke-" << (i + 1) << ": ";
                int ingredientId;
                cin >> ingredientId;

                cout << "Masukkan jumlah yang dibutuhkan: ";
                int amount;
                cin >> amount;

                coffee.recipes[i].ingredientId = ingredientId;
                coffee.recipes[i].amount = amount;
                coffee.recipeCount++;
            }
        }

        cout << "Kopi berhasil diperbarui.\n";
    }

    // Fungsi Menghapus Menu Kopi
    void deleteCoffee() {
        displayCoffees();
        cout << "\nMasukkan ID kopi yang ingin dihapus: ";
        int coffeeId;
        cin >> coffeeId;

        if (coffeeId < 1 || coffeeId > coffeeCount) {
            cout << "Kopi tidak ditemukan.\n";
            return;
        }

        // Geser semua elemen setelah kopi yang dihapus untuk menutupi slot kosong
        for (int i = coffeeId - 1; i < coffeeCount - 1; i++) {
            coffeeMenu[i] = coffeeMenu[i + 1];
        }
        coffeeCount--;
        cout << "Kopi berhasil dihapus dari menu.\n";
    }

    // Fungsi untuk Menambahkan atau Mengubah Diskon pada Kopi
    void setDiscount(int coffeeId, double discount) {
        if (coffeeId < 1 || coffeeId > coffeeCount) {
            cout << "Kopi tidak ditemukan.\n";
            return;
        }

        Coffee& coffee = coffeeMenu[coffeeId - 1];
        coffee.discount = discount; // Tetapkan diskon baru
        cout << "Diskon sebesar " << discount << "% berhasil ditambahkan untuk kopi " << coffee.name << ".\n";
    }

    // Fungsi untuk Menghapus Diskon dari Kopi
    void removeDiscount(int coffeeId) {
        if (coffeeId < 1 || coffeeId > coffeeCount) {
            cout << "Kopi tidak ditemukan.\n";
            return;
        }

        Coffee& coffee = coffeeMenu[coffeeId - 1];
        coffee.discount = 0; // Setel diskon menjadi 0 untuk menghapusnya
        cout << "Diskon pada kopi " << coffee.name << " berhasil dihapus.\n";
    }


    int fibonacciSearch(string coffeeName) {
        int fibM2 = 0; // (m-2)'th Fibonacci No.
        int fibM1 = 1; // (m-1)'th Fibonacci No.
        int fibM = fibM2 + fibM1; // m'th Fibonacci

        while (fibM < coffeeCount) {
            fibM2 = fibM1;
            fibM1 = fibM;
            fibM = fibM2 + fibM1;
        }

        int offset = -1;

        while (fibM > 1) {
            int i = min(offset + fibM2, coffeeCount - 1);

            if (coffeeMenu[i].name < coffeeName) {
                fibM = fibM1;
                fibM1 = fibM2;
                fibM2 = fibM - fibM1;
                offset = i;
            }
            else if (coffeeMenu[i].name > coffeeName) {
                fibM = fibM2;
                fibM1 = fibM1 - fibM2;
                fibM2 = fibM - fibM1;
            }
            else {
                return i; // Ditemukan
            }
        }

        if (fibM1 && coffeeMenu[offset + 1].name == coffeeName) {
            return offset + 1;
        }

        return -1; // Tidak ditemukan
    }

    // Fungsi pencarian menggunakan Jump Search berdasarkan nama kopi
    int jumpSearch(string coffeeName) {
        int step = sqrt(coffeeCount);
        int prev = 0;

        while (coffeeMenu[min(step, coffeeCount) - 1].name < coffeeName) {
            prev = step;
            step += sqrt(coffeeCount);
            if (prev >= coffeeCount) return -1;
        }

        while (coffeeMenu[prev].name < coffeeName) {
            prev++;
            if (prev == min(step, coffeeCount)) return -1;
        }

        if (coffeeMenu[prev].name == coffeeName) return prev;
        return -1;
    }

    // Fungsi pencarian Boyer-Moore untuk substring dalam nama kopi
    int boyerMooreSearch(string pattern) {
        int m = pattern.length();
        vector<int> badChar(256, -1);

        for (int i = 0; i < m; i++) {
            badChar[(int)pattern[i]] = i;
        }

        int s = 0;
        while (s <= (coffeeCount - m)) {
            int j = m - 1;

            while (j >= 0 && pattern[j] == coffeeMenu[s + j].name[j]) {
                j--;
            }

            if (j < 0) {
                return s;
                s += (s + m < coffeeCount) ? m - badChar[coffeeMenu[s + m].name[0]] : 1;
            }
            else {
                s += max(1, j - badChar[coffeeMenu[s + j].name[j]]);
            }
        }
        return -1;
    }

    // Fungsi untuk menampilkan hasil pencarian
    void searchCoffee(string coffeeName, int method) {
        int index = -1;
        switch (method) {
        case 1:
            index = fibonacciSearch(coffeeName);
            break;
        case 2:
            index = jumpSearch(coffeeName);
            break;
        case 3:
            index = boyerMooreSearch(coffeeName);
            break;
        default:
            cout << "Metode pencarian tidak valid.\n";
            return;
        }

        if (index != -1) {
            cout << "Kopi ditemukan:\n";
            cout << "Nama Kopi: " << coffeeMenu[index].name << "\n";
            cout << "Harga: Rp " << coffeeMenu[index].price << "\n";
        }
        else {
            cout << "Kopi tidak ditemukan.\n";
        }
    }

    // Fungsi untuk menggabungkan dua sub-array berdasarkan nama untuk Merge Sort
    void mergeByName(Coffee arr[], int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        Coffee* L = new Coffee[n1];
        Coffee* R = new Coffee[n2];

        for (int i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i].name <= R[j].name) {
                arr[k] = L[i];
                i++;
            }
            else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }

        delete[] L;
        delete[] R;
    }

    void mergeSortByName(Coffee arr[], int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSortByName(arr, left, mid);
            mergeSortByName(arr, mid + 1, right);
            mergeByName(arr, left, mid, right);
        }
    }

    // Quick Sort berdasarkan harga kopi
    int partitionByPrice(Coffee arr[], int low, int high) {
        float pivot = arr[high].price;
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++) {
            if (arr[j].price < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return (i + 1);
    }

    void quickSortByPrice(Coffee arr[], int low, int high) {
        if (low < high) {
            int pi = partitionByPrice(arr, low, high);
            quickSortByPrice(arr, low, pi - 1);
            quickSortByPrice(arr, pi + 1, high);
        }
    }

    // Fungsi untuk menampilkan menu setelah diurutkan
    void displaySortedCoffees() {
        // Membuat salinan sementara dari coffeeMenu
        Coffee* tempMenu = new Coffee[coffeeCount];
        for (int i = 0; i < coffeeCount; i++) {
            tempMenu[i] = coffeeMenu[i];
        }

        cout << "Pilih metode pengurutan berdasarkan harga:\n1. Merge Sort (Nama)\n2. Quick Sort (Harga)\n";
        cout << "Pilihan :"
        int choice;
        cin >> choice;

        if (choice == 1) {
            mergeSortByName(tempMenu, 0, coffeeCount - 1);
            cout << "\nMenu kopi setelah diurutkan (Merge Sort - Nama):\n";
        }
        else if (choice == 2) {
            quickSortByPrice(tempMenu, 0, coffeeCount - 1);
            cout << "\nMenu kopi setelah diurutkan (Quick Sort - Harga):\n";
        }
        else {
            cout << "Pilihan tidak valid.\n";
            delete[] tempMenu;
            return;
        }

        // Menampilkan menu kopi yang sudah diurutkan berdasarkan harga
        for (int i = 0; i < coffeeCount; i++) {
            cout << i + 1 << ". " << tempMenu[i].name << " - Rp " << tempMenu[i].price << endl;
        }

        // Membersihkan memori yang digunakan oleh salinan sementara
        delete[] tempMenu;
    }





    // Menu Admin
    void adminMenu() {
        while (true) {
            cout << "\n==================================\n";
            cout << "           MENU ADMIN\n";
            cout << "==================================\n";
            cout << "1. Kelola Menu Kopi\n";
            cout << "2. Kelola Bahan Baku\n";
            cout << "3. Kelola Promosi Kopi\n";
            cout << "4. Lihat Riwayat Pesan\n";
            cout << "5. Cari Kopi\n";
            cout << "6. Urutkan Menu Kopi\n";
            cout << "7. Kembali\n";
            cout << "----------------------------------\n";
            cout << "Pilih menu: ";

            int choice;
            cin >> choice;

            string name;
            double price;
            int stock;
            int coffeeId;
            double discount;

            if (cin.fail() || choice < 1 || choice > 7) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("cls");
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
                continue;
            }


            switch (choice) {
            case 1:
                system("cls");

                cout << "\n======================================\n";
                cout << "           KELOLA MENU KOPI\n";
                cout << "======================================\n";
                cout << "1. Tambah Kopi\n";
                cout << "2. Lihat Menu Kopi\n";
                cout << "3. Perbarui Kopi\n";
                cout << "4. Hapus Kopi\n";
                cout << "5. Kembali\n";
                cout << "--------------------------------------\n";
                cout << "Pilih aksi: ";
                cin >> choice;

                if (cin.fail() || choice < 1 || choice > 5) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    system("cls");
                    cout << "Pilihan tidak valid. Silakan coba lagi.\n";
                    continue;
                }


                switch (choice) {
                case 1:
                    cout << "Nama kopi: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Harga: ";
                    cin >> price;
                    addCoffee(name, price);
                    break;
                case 2:
                    displayCoffees();
                    break;
                case 3:
                    updateCoffee();
                    break;
                case 4:
                    deleteCoffee();
                    break;
                case 5:
                    return;
                default:
                    cout << "Pilihan tidak valid.\n";
                } break;

            case 2:
                system("cls");

                cout << "\n======================================\n";
                cout << "           KELOLA BAHAN KOPI\n";
                cout << "======================================\n";
                cout << "1. Tambah Bahan Baku\n";
                cout << "2. Lihat Stok Bahan Baku\n";
                cout << "3. Perbarui Stok Bahan Baku\n";
                cout << "4. Kembali\n";
                cout << "--------------------------------------\n";
                cout << "Pilih aksi: ";

                cin >> choice;

                if (cin.fail() || choice < 1 || choice > 4) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    system("cls");
                    cout << "Pilihan tidak valid. Silakan coba lagi.\n";
                    continue;
                }


                switch (choice) {
                case 1:
                    cout << "Nama bahan: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Stok: ";
                    cin >> stock;
                    addIngredient(name, stock);
                    break;
                case 2:
                    displayIngredients();
                    break;
                case 3:
                    updateIngredientStock();
                    break;
                case 4:
                    return;
                default:
                    cout << "Pilihan tidak valid.\n";
                } break;

            case 3:
                system("cls");

                cout << "\n======================================\n";
                cout << "           KELOLA PROMOSI KOPI\n";
                cout << "======================================\n";
                cout << "1. Tambah atau Ubah Diskon pada Kopi\n";
                cout << "2. Hapus Diskon dari Kopi\n";
                cout << "3. Kembali\n";
                cout << "--------------------------------------\n";
                cout << "Pilih aksi: ";

                cin >> choice;

                if (cin.fail() || choice < 1 || choice > 3) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    system("cls");
                    cout << "Pilihan tidak valid. Silakan coba lagi.\n";
                    continue;
                }


                switch (choice) {
                case 1:
                    displayCoffees();
                    cout << "\nMasukkan ID kopi yang ingin ditambahkan atau diubah diskonnya: ";
                    cin >> coffeeId;
                    cout << "Masukkan diskon (dalam %): ";
                    cin >> discount;
                    setDiscount(coffeeId, discount);
                    break;
                case 2:
                    displayCoffees();
                    cout << "\nMasukkan ID kopi yang ingin dihapus diskonnya: ";
                    cin >> coffeeId;
                    removeDiscount(coffeeId);
                    break;
                case 3:
                    return;
                default:
                    cout << "Pilihan tidak valid.\n";
                } break;

            case 4:
                system("cls");
                displayOrderHistory();
                break;

            case 5:
                system("cls");

                cout << "Masukkan nama kopi yang dicari: ";
                cin.ignore();
                getline(cin, name);
                cout << "Pilih metode pencarian:\n1. Fibonacci Search\n2. Jump Search\n3. Boyer-Moore Search\n";
                cout << "Pilihan :";
                int method;
                cin >> method;
                searchCoffee(name, method);
                break;
                
            case 6:
                system("cls");

                displaySortedCoffees();
                break;

            case 7:
                system("cls");
                return;

            default :
                cout << "Pilihan tidak valid.\n";
            }


        }
    }



    // Menu Pelanggan
    void customerMenu() {
        while (true) {
            cout << "\n======================================\n";
            cout << "            MENU PELANGGAN\n";
            cout << "======================================\n";
            cout << "1. Lihat Menu Kopi\n";
            cout << "2. Urutkan Menu Kopi\n";
            cout << "3. Pesan Kopi\n";
            cout << "4. Kembali\n";
            cout << "--------------------------------------\n";
            cout << "Pilih aksi: ";

            int choice;
            cin >> choice;

            if (cin.fail() || choice < 1 || choice > 4) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("cls");
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
                continue;
            }


            string customerName;
            int coffeeId, quantity;

            switch (choice) {
            case 1:
                displayCoffeesNoDetail();
                break;
            case 2:
                displaySortedCoffees();
            case 3:
                displayCoffeesNoDetail();
                cout << "\nMasukkan nama Anda: ";
                cin.ignore();
                getline(cin, customerName);
                cout << "Pilih nomor kopi: ";
                cin >> coffeeId;
                cout << "Jumlah: ";
                cin >> quantity;
                addOrder(customerName, coffeeId, quantity);
                break;
            case 4:
                system("cls");
                return;
            default:
                cout << "Pilihan tidak valid.\n";
            }
        }
    }

    // Fungsi Admin: Menampilkan Riwayat Pesanan
    void displayOrderHistory() {
        if (orderHistory.empty()) {
            cout << "Belum ada riwayat pesanan.\n";
            return;
        }

        cout << "\n=== RIWAYAT PESANAN ===\n";
        stack<Order> tempHistory = orderHistory;
        while (!tempHistory.empty()) {
            Order order = tempHistory.top();
            tempHistory.pop();
            cout << "Pesanan #" << order.id << ": " << order.customerName
                << " - " << order.coffee.name << " x" << order.quantity
                << " - Total: Rp" << order.totalPrice << endl;
        }
    }
};

int main() {
    CoffeeShopSystem coffeeShop;
    int userType;

    while (true) {
        cout << "\n======================================\n";
        cout << "           SISTEM KEDAI KOPI\n";
        cout << "======================================\n";
        cout << "1. Admin\n";
        cout << "2. Pelanggan\n";
        cout << "3. Keluar\n";
        cout << "--------------------------------------\n";
        cout << "Pilih tipe pengguna: ";

        cin >> userType;

        if (cin.fail() || userType < 1 || userType > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
            continue;
        }


        switch (userType) {
        case 1:
            system("cls");

            coffeeShop.adminMenu();
            break;
        case 2:
            system("cls");

            coffeeShop.customerMenu();
            break;
        case 3:
            cout << "Terima kasih telah menggunakan sistem.\n";
            return 0;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    }
}
