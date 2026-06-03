#include <iostream>
#include <fstream>
using namespace std;

struct Mahasiswa {
    string namaMahasiswa;
    string nim;
    string prodi;
    string fakultas;
    float ipk;
};

void tambahData() {
    ofstream file("dataMahasiswa.txt", ios::app);

    int banyakData;
    cout<<"Banyak data yang ingin ditambah: ";
    cin>>banyakData;
    cin.ignore();
    
    Mahasiswa m;
    for (int i = 0; i < banyakData; i++) 
    {
        cout<<"Data ke-"<<i+1<<endl;
        cout<<"Nama Mahasiswa: ";
        getline(cin, m.namaMahasiswa);

        cout<<"Nim           : ";
        getline(cin, m.nim);

        cout<<"Prodi         : ";
        getline(cin, m.prodi);
        cout<<"Fakultas      : ";
        getline(cin, m.fakultas);

        cout<<"IPK      : ";
        cin>>m.ipk;
        cin.ignore();

        file<<m.namaMahasiswa<<"|";
        file<<m.nim<<"|";
        file<<m.prodi<<"|";
        file<<m.fakultas<<"|";
        file<<m.ipk<<endl;
    }
    file.close();
    cout<<"Data Berhasil Disimpan"<<endl;
}

int hitungData() {
    ifstream file("dataMahasiswa.txt");
    
    if (!file) 
    {
        return 0;
    }

    string temp;
    int count = 0;
    
    while (getline(file,temp))
    {
        count++;
    }
    file.close();
    return count;
}

void muatData(Mahasiswa m[], int &n) { 
    ifstream file("dataMahasiswa.txt");

    if (!file)
    {
        n = 0;
        return;
    }
    n = 0;

    while(getline(file, m[n].namaMahasiswa, '|'))
    {
        getline(file, m[n].nim, '|');
        getline(file, m[n].prodi, '|');
        getline(file, m[n].fakultas, '|');

        file >> m[n].ipk;
        file.ignore();

        n++;
    }
    file.close();
}

void tampilkanData() {
    ifstream file("dataMahasiswa.txt");
    if (!file || file.peek() == EOF)
    {
        cout<<"File belum ada atau data masih kosong."<<endl;
        return;
    }
    Mahasiswa m;
    int no = 1;

    while (getline(file, m.namaMahasiswa, '|'))
    {
        getline(file, m.nim, '|');
        getline(file, m.prodi, '|');
        getline(file, m.fakultas, '|');
        file >> m.ipk;
        file.ignore();

        cout<<"Data ke-"<< no++ << endl;
        cout<<"Nama Mahasiswa   : "<<m.namaMahasiswa<<endl;
        cout<<"Nim              : "<<m.nim<<endl;
        cout<<"Prodi            : "<<m.prodi<<endl;
        cout<<"Fakultas         : "<<m.fakultas<<endl;
        cout<<"IPK              : "<<m.ipk<<endl;
        cout<<endl;
    }
    file.close();
}

int partitionNim(Mahasiswa m[], int low, int high, bool ascending) {
    string pivot = m[high].nim;

    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (
            (ascending && m[j].nim < pivot) ||
            (!ascending && m[j].nim > pivot)
           )
        {
            i++;

            Mahasiswa temp = m[i];
            m[i] = m[j];
            m[j] = temp;
        }
    }

    Mahasiswa temp = m[i + 1];
    m[i + 1] = m[high];
    m[high] = temp;

    return i + 1;
}

void quickSort(Mahasiswa m[], int low, int high, bool ascending) {
    if (low < high)
    {
        int pi = partitionNim(m, low, high, ascending);

        quickSort(m, low, pi - 1, ascending);
        quickSort(m, pi + 1, high, ascending);
    }
}

void sortingNim() {
    Mahasiswa m[100];
    int n;

    muatData(m, n);

    if(n == 0)
    {
        cout << "Data kosong!" << endl;
        return;
    }

    int pilihan;

    cout<<endl;
    cout<<"Pilih Urutan : " <<endl;
    cout<<"1. Ascending" <<endl;
    cout<<"2. Descending" <<endl;
    cout<<"Pilihan: ";
    cin>>pilihan;

    bool ascending = (pilihan == 1);

    if (pilihan != 1 && pilihan != 2)
    {
        cout<<"Pilihan tidak valid!"<<endl;
        return;
    }

    quickSort(m, 0, n - 1, ascending);

    cout<<endl;
    cout<<"=== HASIL SORTING NIM ==="<<endl;
    
    for(int i = 0; i < n; i++)
    {
        cout<<"Data ke-" << i + 1 <<endl;
        cout<<"Nama Mahasiswa : " <<m[i].namaMahasiswa << endl;
        cout<<"NIM            : " <<m[i].nim << endl;
        cout<<"Prodi          : " <<m[i].prodi << endl;
        cout<<"Fakultas       : " <<m[i].fakultas<<endl;
        cout<<"IPK            : " <<m[i].ipk << endl;
        cout<<endl;
    }
}

string hurufKecil(string teks) {
    for(int i = 0; i < teks.length(); i++)
    {
        teks[i] = tolower(teks[i]);
    }

    return teks;
}

void cariData() {
    Mahasiswa m[100];
    int n;

    muatData(m, n);

    if(n == 0)
    {
        cout << "Data kosong!" << endl;
        return;
    }

    int pilihan;

    cout<<endl;
    cout<<"Cari Berdasarkan:"<<endl;
    cout<<"1. Nama Mahasiswa"<<endl;
    cout<<"2. NIM" << endl;
    cout<<"Pilihan: ";
    cin>>pilihan;
    cin.ignore();

    string cari;

    cout<<"Masukkan kata yang ingin dicari: ";
    getline(cin, cari);

    cari = hurufKecil(cari);

    int kiri = 0;
    int kanan = n - 1;
    int tengah;
    int found = -1;

    while(kiri <= kanan)
    {
        tengah = (kiri + kanan) / 2;

        string dataCari;

        if(pilihan == 1)
        {
            dataCari = hurufKecil(m[tengah].namaMahasiswa);
        }
        else if(pilihan == 2)
        {
            dataCari = hurufKecil(m[tengah].nim);
        }
        else
        {
            cout << "Pilihan tidak valid!" << endl;
            return;
        }

        if(dataCari == cari)
        {
            found = tengah;
            break;
        }
        else if(dataCari < cari)
        {
            kiri = tengah + 1;
        }
        else
        {
            kanan = tengah - 1;
        }
    }

    if(found == -1)
    {
        cout << "Data tidak ditemukan!" << endl;
        return;
    }
    cout<<endl;
    cout << "Data ditemukan!" << endl;
    cout << "Nama Mahasiswa : " << m[found].namaMahasiswa << endl;
    cout << "NIM            : " << m[found].nim << endl;
    cout << "Prodi          : " << m[found].prodi << endl;
    cout << "Fakultas       : " << m[found].fakultas << endl;
    cout << "IPK            : " << m[found].ipk << endl;
}

void simpanData(Mahasiswa m[], int n)
{
    ofstream file("dataMahasiswa.txt");

    for(int i = 0; i < n; i++)
    {
        file << m[i].namaMahasiswa << "|";
        file << m[i].nim << "|";
        file << m[i].prodi << "|";
        file << m[i].ipk << endl;
    }

    file.close();
}

void ubahData()
{
    Mahasiswa m[100];
    int n;

    muatData(m, n);

    if(n == 0)
    {
        cout << "Data kosong!" << endl;
        return;
    }

    cout << "\n=== DAFTAR DATA ===\n";

    for(int i = 0; i < n; i++)
    {
        cout << i + 1 << ". "
             << m[i].namaMahasiswa
             << " | " << m[i].nim
             << " | " << m[i].prodi
             << " | " << m[i].ipk
             << endl;
    }

    int pilihData;

    cout << "\nPilih nomor data yang ingin diubah: ";
    cin >> pilihData;
    cin.ignore();

    if(pilihData < 1 || pilihData > n)
    {
        cout << "Nomor data tidak valid!" << endl;
        return;
    }

    int index = pilihData - 1;

    cout << "\n=== INPUT DATA BARU ===\n";

    cout << "Nama Mahasiswa : ";
    getline(cin, m[index].namaMahasiswa);

    cout << "NIM            : ";
    getline(cin, m[index].nim);

    cout << "Prodi          : ";
    getline(cin, m[index].prodi);

    cout << "IPK            : ";
    cin >> m[index].ipk;

    simpanData(m, n);

    cout << "\nData berhasil diubah!" << endl;
}

void hapusData()
{
    Mahasiswa m[100];
    int n;

    muatData(m, n);

    if(n == 0)
    {
        cout << "Data kosong!" << endl;
        return;
    }

    cout << "\n=== DAFTAR DATA ===\n";

    for(int i = 0; i < n; i++)
    {
        cout << i + 1 << ". "
             << m[i].namaMahasiswa
             << " | " << m[i].nim
             << " | " << m[i].prodi
             << " | " << m[i].ipk
             << endl;
    }

    int pilihData;

    cout << "\nPilih nomor data yang akan dihapus: ";
    cin >> pilihData;

    if(pilihData < 1 || pilihData > n)
    {
        cout << "Nomor data tidak valid!" << endl;
        return;
    }

    int index = pilihData - 1;

    for(int i = index; i < n - 1; i++)
    {
        m[i] = m[i + 1];
    }

    n--;

    simpanData(m, n);

    cout << "\nData berhasil dihapus!" << endl;
}

int main() {
    int pilih;
    do{

        cout<<"============================================"<<endl;
        cout<<"               DATA MAHASISWA               "<<endl;
        cout<<"============================================"<<endl;
        cout<<"1. Tambah Data Mahasiswa"<<endl;
        cout<<"2. Tampilkan Data Mahasiswa"<<endl;
        cout<<"3. Sorting Berdasarkan Nim"<<endl;
        cout<<"4. Cari Data Mahasiswa"<<endl;
        cout<<"5. Ubah Data Mahasiswa"<<endl;
        cout<<"6. Hapus Data Mahasiswa"<<endl;
        cout<<"============================================"<<endl;
        cout<<"Pilih Menu (1-?): ";
        cin>>pilih;

        switch (pilih)
        {
        case 1:
            tambahData();
            break;
        case 2:
            tampilkanData();
            break;
        case 3:
            sortingNim();
            break;
        case 4:
            cariData();
            break;
        case 5:
            ubahData();
            break;
        case 6:
            hapusData();
            break;
        case 7:
            cout<<"Kamu sudah keluar dari program!!";
            exit;
        default:
            cout<<"Pilihan Tidak Valid"<<endl;
            break;
        }
    } while(pilih !=7);
    return 0;
}
