#include <iostream>

using namespace std;

void Menara_Hanoi (int x, char awal, char tujuan, char sementara)
{

    if (x == 1)
    {
        cout << "Pindahkan piringan 1 dari " << awal << " ke " << tujuan << endl;

    } else
    {
        Menara_Hanoi (x-1, awal, sementara, tujuan);
        cout << "Pindahkan piringan " << x << " dari " << awal << " ke " << tujuan << endl;
        Menara_Hanoi (x-1, sementara, tujuan, awal);
    }
}

int main()
{
    int jumlah_piringan = 3;

    cout << "Perpindahan " << jumlah_piringan << " piringan dari A ke C dengan B sebagai perantara:" << endl;
    Menara_Hanoi (jumlah_piringan, 'A', 'C', 'B');
    return 0;
}
