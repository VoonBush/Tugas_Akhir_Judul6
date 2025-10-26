#include <iostream>
using namespace std;

const int SIZE = 10;

struct Pasien {
    int ID;
    string nama, diagnosa;
    Pasien* next;
};

void initTable(Pasien* table[]) {
    for (int i = 0; i < SIZE; i++) {
        table[i] = nullptr;
    }
}

int hashFunction(int ID) {
    return (ID % SIZE + SIZE) % SIZE;
}

void insert(Pasien* table[], int ID, string nama, string diagnosa) {
    int index = hashFunction(ID);
    Pasien* cur = table[index];
    while (cur != nullptr) {
        if (cur->ID == ID) {
            cur->nama = nama;
            cur->diagnosa = diagnosa;
            return;
        }
        cur = cur->next;
    }
    Pasien* baru = new Pasien;
    baru->ID = ID;
    baru->nama = nama;
    baru->diagnosa = diagnosa;
    baru->next = table[index];
    table[index] = baru;
}

Pasien* search(Pasien* table[], int ID) {
    int index = hashFunction(ID);
    Pasien* cur = table[index];
    while (cur != nullptr) {
        if (cur->ID == ID) {
            return cur;
        }
        cur = cur->next;
    }
    return nullptr;
}

void removekey(Pasien* table[], int ID) {
    int index = hashFunction(ID);
    Pasien* cur = table[index];
    Pasien* prev = nullptr;
    while (cur != nullptr) {
        if (cur->ID == ID) {
            if (prev == nullptr) {
                table[index] = cur->next;
            } else {
                prev->next = cur->next;
            }
            delete cur;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

void display(Pasien* table[]) {
    cout << "\nList Data Pasien\n";
    for (int i = 0; i < SIZE; i++) {
        cout << i << ": ";
        Pasien* tmp = table[i];
        while (tmp != nullptr) {
            cout << "(ID: " << tmp->ID << ", Nama: " << tmp->nama << ", Diagnosa: " << tmp->diagnosa  << ") -> ";
            tmp = tmp->next;
        }
        cout << "NULL\n";
    }
}

int main(){
    Pasien* table[SIZE];
    initTable(table);
    int pilih,id;
    string name,diagnos;
    bool loop = true;
    while (loop) {
        cout << "\n ===MENU RUMAH SAKIT=== \n";
        cout << "1. Masukan Data Pasien\n";
        cout << "2. Cari Nama Pasien\n";
        cout << "3. Hapus Data Pasien\n";
        cout << "4. Tampilkan Seluruh Data Pasien\n";
        cout << "5. Keluar\n";
        cout << "Pilih :";
        cin >> pilih;
        cin.ignore();

        if(pilih == 1){
            cout << "Masukan ID Pasien :";
            cin >> id;
            cin.ignore();
            cout << "Masukan Nama Pasien : ";
            getline(cin, name);
            cout << "Masukan Penyakit Pasien : ";
            getline(cin, diagnos);
            insert(table, id, name, diagnos);
        } else if (pilih == 2){
            cout << "Masukan ID yang dicari : ";
            cin >> id;
            Pasien* hasil = search(table,id);
            if (hasil != nullptr){
                cout << "\n===ID DITEMUKAN===\n";
                cout << "-" << hasil->ID << endl;
                cout << "-" << hasil->nama << endl;
                cout << "-" << hasil->diagnosa << endl;
            }else{
            cout << "\nID tidak ditemukan...\n";
            }
        } else if (pilih == 3){
            cout << "Masukan ID yang ingin dihapus : ";
            cin >> id;
            removekey(table,id);
        } else if (pilih == 4){
            display(table);
        } else{
            loop = false;
        }
    }
    return 0;
}