#include "header.h"

void ThongSo::display () {
    cout << "Man hinh:      " << this->manHinh << "\n";
    cout << "He dieu hanh:  " << this->heDieuHanh << "\n";
    cout << "Camera truoc:  " << this->cameraTruoc << "\n";
    cout << "Camera sau:    " << this->cameraSau << "\n";
    cout << "Ram:           " << this->ram << "\n";
    cout << "Bo nho trong:  " << this->boNhoTrong << "\n";
    cout << "Dung luong pin:" << this->dungLuongPin << "\n";
}
void ThongSo::changeInfo() {
    cout << "New screen:            ";      getline(cin, this->manHinh);
    cout << "New operation system:  ";      getline(cin, this->heDieuHanh);
    cout << "New front camera:      ";      getline(cin, this->cameraTruoc);
    cout << "New rear camera:       ";      getline(cin, this->cameraSau);
    cout << "New ram:               ";      getline(cin, this->ram);
    cout << "New internal memory:   ";      getline(cin, this->boNhoTrong);
    cout << "New battery capacity:  ";      getline(cin, this->dungLuongPin);
}
// SanPham :
float SanPham::tinhTien () {
    return this->getSL() * this->gia;
}

void SanPham::display () {
    cout << this->ten << "     \n";
    cout << "Group:         " << this->group << "\n";
    cout << "Gia:           " << this->gia << " $\n";
    cout << "Danh gia:      " << this->danhGia << " *\n";
    cout << "Khuyen mai:    " << this->contentKM << "\n";
}
bool SanPham::checkPrice (float price) {
    if (price == this->gia) return true;
    return false;
}
void SanPham::show () {
    cout << "           " << this->ten << "\n";
    this->thongSo.display ();
    cout << "Group:         " << this->group << "\n";
    cout << "Gia:           " << this->gia << " $\n";
    cout << "Danh gia:      " << this->danhGia << " *\n";
    cout << "Khuyen mai:    " << this->contentKM << "\n";
}
void SanPham::setSL (int _soLuong) {
    this->soLuong = _soLuong;
}
int SanPham::getSL () {
    return this->soLuong;
}
string SanPham::getName () {
    return this->ten;
}
// Danh sach
void DanhSach::display (int x = 1) {
    if (x == 1) {
        for (int i = 0; i < this->listSP.size (); i ++) {
            cout << "***********************************************\n";
            cout << i + 1 << ". ";
            this->listSP[i].display ();
            cout << "\n";
        }
    } else {
        for (int i = 0; i < this->listSP.size (); i ++) {
            cout << "***********************************************\n";
            cout << i + 1 << ". ";
            cout << "Name :     " << this->listSP[i].getName () << "\n";
            cout << "   Number :   " << listSP[i].getSL () << "\n";
            cout << "\n";
        }
    }
}
void DanhSach::show (int idx) {
    this->listSP[idx].show ();
}
void DanhSach::del (int idx) {
    this->listSP.erase (listSP.begin () + idx);
}
void DanhSach::add (SanPham sanPham) {
    this->listSP.push_back (sanPham);
}
int DanhSach::getSL (int idx) {
    return this->listSP[idx].getSL ();
}
void DanhSach::setSL (int idx, int soLuong) {
    this->listSP[idx].setSL (soLuong);
}
int DanhSach::getSize () {
    return this->listSP.size ();
}
// GioHang
void GioHang::chuanHoa () {
    for (int i = 0; i < this->listSP.size () - 1; i ++) 
        for (int j = i + 1; j < this->listSP.size (); j ++)
            if (listSP[i].getName () == listSP[j].getName ()) {
                int soLuong = listSP[i].getSL () + listSP[j].getSL ();
                listSP[i].setSL (soLuong);
                this->listSP.erase (listSP.begin () + j);
                j --;
            } 
    for (int i = 0; i < this->listSP.size(); i ++)
        if (this->listSP[i].getSL() == 0) {
            this->listSP.erase(listSP.begin() + i);
            i --;
        }
}

float GioHang::tinhTien () {
    float tien = 0;
    for (int i = 0; i < this->listSP.size (); i ++)
        tien += this->listSP[i].tinhTien ();
    return tien;
}

void GioHang::clear () {
    this->listSP.resize (0);
}
string GioHang::getName(int idx) {
    return this->listSP[idx].getName();
}
// QuanLiSP
QuanLiSP::QuanLiSP () {
    string temp;
    SanPham x;
    ThongSo ts;
    ifstream file ("sanpham.txt");
    while (! file.eof ()) {
        getline (file, temp);
        x.ten = temp.substr (3, 100);
        getline (file, ts.manHinh);
        getline (file, ts.heDieuHanh);
        getline (file, ts.cameraTruoc);
        getline (file, ts.cameraSau);
        getline (file, ts.ram);
        getline (file, ts.boNhoTrong);
        getline (file, ts.dungLuongPin);
        x.thongSo = ts;
        getline (file, temp);
        x.group = temp;
        getline (file, temp);
        x.gia = stof (temp);
        getline (file, temp);
        x.danhGia = stof (temp);
        getline (file, temp);
        x.soLuong = stoi (temp);
        getline (file, temp);
        x.soLuongKM = stoi (temp);
        getline (file, temp);
        x.contentKM = temp;
        this->listSP.push_back (x);
        getline (file, temp);
    }
    file.close ();
}
vector<int> QuanLiSP::findN (string name) {
    vector<int> x;
    name = Reference::lowerCase (name);

    Reference::clrscr ();
    bool check = false;
    for (int i = 0; i < this->listSP.size (); i ++)
        if (Reference::lowerCase (this->listSP[i].ten).find (name) != string::npos) {
            cout << "***********************************************\n";
            cout << i + 1 << ". ";
            listSP[i].display ();
            cout << "\n";
            x.push_back (i);
            check = true;
        }
    if (! check) cout << "Sorry ! We don't have this product :((\n";
    Sleep (2000);
    return x;
}
vector<int> QuanLiSP::findG (string name) {
    vector<int> x;
    name = Reference::lowerCase (name);

    Reference::clrscr ();
    bool check = false;
    for (int i = 0; i < this->listSP.size (); i ++)
        if (Reference::lowerCase (this->listSP[i].group).find (name) != string::npos) {
            cout << "***********************************************\n";
            cout << i + 1 << ". ";
            listSP[i].display ();
            cout << "\n";
            x.push_back (i);
            check = true;
        }
    if (! check) cout << "Sorry ! We don't have this kind of product :((\n";
    Sleep (2000);
    return x;
}
vector<int> QuanLiSP::find (float price) {
    vector<int> x;
    Reference::clrscr ();
    bool check = false;
    for (int i = 0; i < this->listSP.size (); i ++)
        if (listSP[i].gia == price) {
            cout << "***********************************************\n";
            cout << i + 1 << ". ";
            listSP[i].display ();
            cout << "\n";
            check = true;
            x.push_back(i);
        }
    if (! check) cout << "Sorry ! We don't have this product :((\n";
    Sleep (2000);
    return x;
}
vector<int> QuanLiSP::locSP (float begin, float end) {
    Reference::clrscr();
    bool check = false;
    vector<int> x;
    for (int i = 0; i < this->listSP.size (); i ++)
        if (listSP[i].gia >= begin && listSP[i].gia <= end) {
            cout << "***********************************************\n";
            cout << i + 1 << ". ";
            listSP[i].display ();
            cout << "\n";
            check = true;
            x.push_back(i);
        }
    if (! check) cout << "Sorry ! We don't have this product :((\n";
    Sleep (2000);
    return x;
}
void QuanLiSP::changeInfo (int idx) {
    cout << "What infomation do you want to change ? \n";
    cout << "Your choice: ";
    string choice;
    getline (cin, choice);     
    if (choice == "name") {
        cout << "Type new name: ";
        string name;
        getline (cin, name);   
        listSP[idx].ten = name;
    } else if (choice == "group") {
        cout << "Type new group: ";
        string group;
        getline (cin, group);   
        listSP[idx].group = group;
    } else if (choice == "price") {
        cout << "Type new price: ";
        float price;
        cin >> price;    cin.ignore ();
        listSP[idx].gia = price;
    } else if (choice == "number") {
        cout << "Type new number: ";
        int number;
        cin >> number;    cin.ignore ();
        listSP[idx].soLuong = number;
    }
}
float QuanLiSP::thongKe () {
    float tien = 0;
    int soLuong = 0;
    int tienSanPham;
    for (int i = 0; i < this->listSP.size (); i ++) {
        soLuong = 50 - this->listSP[i].soLuong;
        tienSanPham = this->listSP[i].gia * soLuong;
        tien += tienSanPham;
        cout << "       *************************************************\n";
        cout << "       " << i + 1 << ". " << this->listSP[i].ten << "\n";
        cout << "       So luong da ban:   " << soLuong << "\n";
        cout << "       Tong:              " << tienSanPham << "\n";
    }
    cout << "\n\n";
    cout << "           Tong doanh thu: " << tien;
    return tien;       
}
SanPham QuanLiSP::getSP (int idx) {
    return this->listSP[idx];
}

int QuanLiSP::getIndex (string name) {
    for (int i = 0; i < this->listSP.size (); i ++) {
        if (name == this->listSP[i].getName ()) return i;
    }
}
void QuanLiSP::write () {
    ofstream file ("sanpham.txt");
    for (int i = 0; i < this->listSP.size (); i ++) {
        if (i != 0) file << "\n";
        file << i + 1 << ". ";
        file << this->listSP[i].ten << "\n";
        file << this->listSP[i].thongSo.manHinh << "\n";
        file << this->listSP[i].thongSo.heDieuHanh << "\n";
        file << this->listSP[i].thongSo.cameraTruoc << "\n";
        file << this->listSP[i].thongSo.cameraSau << "\n";
        file << this->listSP[i].thongSo.ram << "\n";
        file << this->listSP[i].thongSo.boNhoTrong << "\n";
        file << this->listSP[i].thongSo.dungLuongPin << "\n";
        file << this->listSP[i].group << "\n";
        file << this->listSP[i].gia << "\n";
        file << this->listSP[i].danhGia << "\n";
        file << this->listSP[i].soLuong << "\n";
        file << this->listSP[i].soLuongKM << "\n";
        file << this->listSP[i].contentKM << "\n";
    }
    file << ".";
    file.close ();
}
SanPham& QuanLiSP::operator[] (int idx) {
    return this->listSP[idx];
}