#include "header.h"
// KhachHang :
void KhachHang::showHistory () {
    for (int i = 0; i < this->history.size (); i ++) {
        cout << "***********************************************\n";
        cout << i + 1 << ". ";
        this->history[i].display ();
        cout << "Number : " << this->history[i].getSL () << "\n";
    }
}
void KhachHang::display () {
    cout << this->name << "\n";
    cout << this->diaChi << "\n";
}
void KhachHang::show () {
    cout << this->name << "\n";
    cout << this->username << "\n";
    cout << this->diaChi << "\n";
    cout << this->sdt << "\n";
    cout << "Danh sach mua hang: \n";
    this->showHistory ();
}
bool KhachHang::checkExist (string name) {
    if (this->name == name) return true;
    else return false;
}
bool KhachHang::changePassword (string newPass) {
    this->password = newPass;
    return true;
}
bool KhachHang::checkLogin (string tk, string mk) {
    if (tk == this->username && mk == this->password) return true;
    return false;
}
string KhachHang::getUsername () {
    return this->username;
}
// QuanLiKH :
QuanLiKH::QuanLiKH () {
    KhachHang x;
    string temp;
    ifstream file ("khachhang.txt");
    while (! file.eof ()) {
        getline (file, temp);
        x.name = temp.substr (3, 100);
        getline (file, temp);
        x.username = temp;
        getline (file, temp);
        x.password = temp;
        getline (file, temp);
        x.sdt = temp;
        getline (file, temp);
        x.diaChi = temp;
        getline (file, temp);
        this->listKH.push_back (x);
    }
    file.close ();
}
void QuanLiKH::show (int idx) {
    this->listKH[idx].show ();
}
void QuanLiKH::display () {
    for (int i = 0; i < this->listKH.size (); i ++) {
        cout << "******************************\n";
        cout << i + 1 << ". ";
        this->listKH[i].display () ;
    }
        
}
void QuanLiKH::del (int idx) {
    this->listKH.erase (listKH.begin () + idx);
}
vector<int> QuanLiKH::find (string name) {
    vector<int> x;
    bool check = false;
    name = Reference::lowerCase(name);
    Reference::clrscr();
    for (int i = 0; i < this->listKH.size (); i ++)
        if (Reference::lowerCase(this->listKH[i].name).find(name) != string::npos) {
            listKH[i].display ();
            x.push_back(i);
            check = true;
        }
    if (! check) cout << "We don't have this guest\n";
    return x;
}
void QuanLiKH::changeInfo (int idx) {
    cout << "Type infomation which you want to change: ";
    string choice;
    getline (cin, choice);      
    if (choice == "name") {
        cout << "Type new name: ";
        string name;
        getline (cin, name);
        this->listKH[idx].name = name;
    } else if (choice == "telephone") {
        cout << "Type new telephone: ";
        string tel;
        getline (cin, tel);
        this->listKH[idx].sdt = tel;
    } else if (choice == "address") {
        cout << "Type new address: ";
        string address;
        getline (cin, address);
        this->listKH[idx].diaChi = address;
    }
}
void QuanLiKH::add (KhachHang khachHang) {
    this->listKH.push_back (khachHang);
}
void QuanLiKH::buy (int idx, SanPham sanPham) {
    this->listKH[idx].gioHang.add (sanPham);
    this->listKH[idx].gioHang.chuanHoa ();
    this->listKH[idx].history.push_back (sanPham);
}
KhachHang& QuanLiKH::operator[] (int idx) {
    return this->listKH[idx];
}
int QuanLiKH::login (string tk, string mk) {
    for (int i = 0; i < this->listKH.size (); i ++)
        if (listKH[i].checkLogin (tk, mk)) return i;
    return -2;
}
int QuanLiKH::checkForget (string tk, string name, string sdt) {
    for (int i = 0; i < this->listKH.size (); i ++)
        if (listKH[i].name == name && listKH[i].username == tk && listKH[i].sdt == sdt) return i;
    return -1;
}
int QuanLiKH::size () {
    return this->listKH.size ();
}
void QuanLiKH::write () {
    ofstream file ("khachhang.txt");
    for (int i = 0; i < this->listKH.size (); i ++) {
        if (i != 0) file << "\n";
        file << i + 1 << ". ";
        file << this->listKH[i].name << "\n";
        file << this->listKH[i].username << "\n";
        file << this->listKH[i].password << "\n";
        file << this->listKH[i].sdt << "\n";
        file << this->listKH[i].diaChi << "\n";
    }
    file.close ();
}