// Name id: Phạm Nhật Minh
// Studtent id: 20206295
// Class: 763964
#include "bits/stdc++.h"
#include <windows.h>
#include <limits>

using namespace std;

struct NgaySinh{
    int ngay;
    int thang;
    int nam;
};
// =========================================================
// 1. CẤU TRÚC DỮ LIỆU VÀ CÁC HÀM TƯƠNG ỨNG VỚI MỖI CẤU TRÚC
// =========================================================
// ==================== Cấu trúc lưu thông tin sinh viên ====================
struct SinhVien {
    string MSSV;
    string hoTen;
    string lop;
    NgaySinh ngaySinh;
    SinhVien* tiepTheo;

};
// Tạo sinh viên mới và điền thông tin
SinhVien* taoSinhVien(){
    SinhVien* sv = new SinhVien;
    cout << "Nhập thông tin sinh viên mới :\n";
    cout << "Nhập MSSV: ";  getline(cin, sv->MSSV);
    cout << "Nhập tên: "; getline(cin, sv->hoTen);
    cout << "Nhập lớp: "; getline(cin, sv->lop);
    cout << "Nhập ngày sinh "; cin >> sv->ngaySinh.ngay >> sv->ngaySinh.thang >> sv->ngaySinh.nam;
    cin.ignore();
    sv->tiepTheo = NULL;
    return sv;
}
//In sinh viên
void inSinhVien(SinhVien* sv){
    cout << sv->MSSV << " | " << sv->hoTen << " | "<< sv->lop << " | " << sv->ngaySinh.ngay << "-" << sv->ngaySinh.thang << "-" << sv->ngaySinh.nam << endl;
}

// ==================== Cấu trúc chứa danh sách các sinh viên ====================
struct DsSinhVien{
    SinhVien* svDau;
    SinhVien* svCuoi;
};
// Kiểm tra MSSV trong danh sách sinh viên
bool ktraSvTrongDsSv(DsSinhVien* dsSv, string mssv){
    SinhVien* sv = dsSv->svDau;

    while(sv != NULL){
        if(sv->MSSV == mssv){
            return TRUE;
        }
        sv = sv->tiepTheo;
    }

    return FALSE;
}
// Thêm sinh viên vào đầu danh sách sinh viên
void themSvMoi(DsSinhVien* dsSv) {
    SinhVien* sv = taoSinhVien();

    // Kiêm tra MSSV của sinh viên thêm mới trong Danh sách sinh viên
    if(ktraSvTrongDsSv(dsSv, sv->MSSV)){cout << "MSSV của sinh cần thêm mới đã có trong Danh sách sinh viên!\n"; return;}

    if (!dsSv->svDau) dsSv->svDau = dsSv->svCuoi = sv;
    else { dsSv->svCuoi->tiepTheo = sv; dsSv->svCuoi = sv; }

    return;
}
// Xoá sinh viên theo MSSV
void xoaSv(DsSinhVien* dsSv, string mssv){
    if(dsSv->svDau == NULL){
        cout << "Danh sách trống\n";
        return;
    }

    SinhVien* svDangXet = dsSv->svDau;
    SinhVien* svDaXet = NULL;

    // Tìm sinh viên có mssv cần xoá
    while(svDangXet != NULL && svDangXet->MSSV != mssv){
        svDaXet = svDangXet;
        svDangXet = svDangXet->tiepTheo;
    }

    // Các trường hợp khi xoá sinh viên
    if(svDangXet == NULL){
        cout << "Không tìm thấy sinh viên có MSSV tương ứng\n";
        return;
    }
    if(svDangXet == dsSv->svDau){
        dsSv->svDau = svDangXet->tiepTheo;
        if(dsSv->svDau == NULL){
            dsSv->svCuoi = NULL;
        }
    }
    else{
        svDaXet->tiepTheo = svDangXet->tiepTheo;
        if(svDangXet == dsSv->svCuoi){
            dsSv->svCuoi = svDaXet;
        }
    }
    delete svDangXet;
    cout << "Đã xoá sinh viên có MSSV: " << mssv << endl;
}
// Cập nhât sinh viên theo MSSV
void capNhatSv(DsSinhVien* dsSv, string mssv){
    SinhVien* sv = dsSv->svDau;

    // Tìm sinh viên có mssv cần cập nhật
    while(sv!=NULL ){
        if(sv->MSSV == mssv){
            cout << "Nhập thông tin sinh viên :\n";
            cout << "Nhập MSSV: ";  getline(cin, sv->MSSV);
            cout << "Nhập tên: "; getline(cin, sv->hoTen);
            cout << "Nhập lớp: "; getline(cin, sv->lop);
            cout << "Nhập ngày sinh "; cin >> sv->ngaySinh.ngay >> sv->ngaySinh.thang >> sv->ngaySinh.nam;
            cin.ignore();
            return;
        }
        sv = sv->tiepTheo;
    }

    cout << "Không tìm thấy sinh viên có MSSV: " << mssv << endl;
}
// In danh sách sinh viên
void inDanhSachSv(DsSinhVien* l){
    SinhVien* sv = l->svDau;

    cout << "-----Danh sách sinh viên-----\n";
    while(sv != NULL){
        inSinhVien(sv);
        sv = sv->tiepTheo;
    }

    cout << endl;

    return;
}

//==================== Cấu trúc học phần ====================
struct HocPhan{
    string maHocPhan;
    string tenHocPhan;
    float soTinChi;
    HocPhan* tiepTheo;
};
// Tạo học phần mới và điền thông tin
HocPhan* taoHocPhan(){
    HocPhan* hp = new HocPhan();

    cout << "Nhập thông tin học phần: \n";
    cout << "Nhập mã học phần: "; getline(cin, hp->maHocPhan);
    cout << "Nhập tên học phần: "; getline(cin, hp->tenHocPhan);
    cout << "Nhập số tín chỉ học phần: "; cin >> hp->soTinChi;
    cin.ignore();
    hp->tiepTheo = NULL;

    return hp;
}
//In học phần
void inHocPhan(HocPhan* hp){
    cout << hp->maHocPhan << " | " << hp->tenHocPhan << " | " << hp->soTinChi << endl;
}

//==================== Cấu trúc danh sách học phần ====================
struct DsHocPhan{
    HocPhan* hpDau;
    HocPhan* hpCuoi;
};
// Kiểm tra mã hoc phần trong danh sách học phần
bool ktraHpTrongDsHp(DsHocPhan* dsHp, string maHp){
    HocPhan* hp = dsHp->hpDau;
    while(hp!=NULL){
        if(hp->maHocPhan == maHp){
            return TRUE;
        }
        hp = hp->tiepTheo;
    }

    return FALSE;
}
// Thêm học phần mới vào đầu danh sách học phần
void themHpMoi(DsHocPhan* dsHp) {
    HocPhan* hp = taoHocPhan();

    // Kiêm tra mã học phần thêm mới đã có trong Danh sách học phần chưa
    if(ktraHpTrongDsHp(dsHp,hp->maHocPhan)){cout << "Mã học phần cần thêm mới đã có trong Danh sách học phần!\n"; return;}

    if (!dsHp->hpDau) {dsHp->hpDau = dsHp->hpCuoi = hp;}
    else { dsHp->hpCuoi->tiepTheo = hp; dsHp->hpCuoi = hp; }

    cout << "Đã thêm học phần có Mã học phần " << hp->maHocPhan << "!\n";
}
// Xoá học phần theo mã học phần
void xoaHp(DsHocPhan* dsHp, string maHp){
    if(dsHp->hpDau == NULL){
        cout << "Danh sách trống!\n";
        return;
    }

    HocPhan* hpDangXet = dsHp->hpDau;
    HocPhan* hpDaXet = NULL;

    // Tìm học phần có mã học phần cần xoá
    while(hpDangXet != NULL && hpDangXet->maHocPhan != maHp){
        hpDaXet = hpDangXet;
        hpDangXet = hpDangXet->tiepTheo;
    }

    // Các trường hợp khi xoá học phần
    if(hpDangXet == NULL){
        cout << "Không tìm học phần có Mã học phần " << maHp <<"!\n";
        return;
    }
    if(hpDangXet == dsHp->hpDau){
        dsHp->hpDau = hpDangXet->tiepTheo;
        if(dsHp->hpDau == NULL){
            dsHp->hpCuoi = NULL;
        }
    }
    else{
        hpDaXet->tiepTheo = hpDangXet->tiepTheo;
        if(hpDangXet == dsHp->hpCuoi){
            dsHp->hpCuoi = hpDaXet;
        }
    }
    delete hpDangXet;

    cout << "Đã xoá học phần có Mã học phần " << maHp << "!\n";
}
// Cập nhât học phần theo Mã học phần
void capNhatHp(DsHocPhan* dsHp, string maHp){
    HocPhan* hp = dsHp->hpDau;

    // Tìm sinh viên có mssv cần cập nhật
    while(hp!=NULL ){
        if(hp->maHocPhan == maHp){
            cout << "Nhập thông tin học phần: \n";
            cout << "Nhập mã học phần: "; getline(cin, hp->maHocPhan);
            cout << "Nhập tên học phần: "; getline(cin, hp->tenHocPhan);
            cout << "Nhập số tín chỉ học phần: "; cin >> hp->soTinChi;
            cin.ignore();
            return;
        }
        hp = hp->tiepTheo;
    }

    cout << "Không tìm thấy học phần có Mã học phần " << maHp << "!\n";
}
// In danh sách học phần
void inDanhSachHp(DsHocPhan* dsHp){
    HocPhan* hp = dsHp->hpDau;

    cout << "-----Danh sách học phần-----\n";
    while(hp != NULL){
        inHocPhan(hp);
        hp = hp->tiepTheo;
    }

    cout << endl;

    return;
}
//Lấy số tín của mã học phần trong danh sách học phần
float soTinChiCuaMaHp(string maHp, DsHocPhan* dsHp){
    HocPhan* hp = dsHp->hpDau;

    while(hp!=NULL){
        if(hp->maHocPhan == maHp){
            return hp->soTinChi;
        }
        hp = hp->tiepTheo;
    }

    return 0;
}

//==================== Cấu trúc chứa thông tin của một sinh viên trong lớp học phần ====================
struct SvTrongLopHp{
    string MSSV;
    float diemHocPhan;
    SvTrongLopHp* tiepTheo;
};
// Hàm tạo sinh viên trong lớp học phần
SvTrongLopHp* taoSvTrongLopHp(){
    SvTrongLopHp* svLhp = new SvTrongLopHp();
    cout << "Nhập thông tin sinh viên đăng ký lớp học phần:\n";
    cout << "Nhập MSSV: "; getline(cin, svLhp->MSSV);
    svLhp ->diemHocPhan = 0;

    svLhp->tiepTheo = NULL;

    return svLhp;
}

// ==================== Cấu trúc danh sách chứa các sinh viên trong một lớp học phần ====================
struct DsSvTrongLopHp{
    SvTrongLopHp* svDau;
    SvTrongLopHp* svCuoi;
};
// Xoá sinh viên trong lớp học phần
void xoaSvTrongLhp(DsSvTrongLopHp* dsSvTrongLhp, string mssv){
    if(dsSvTrongLhp->svDau == NULL){
        cout << "Danh sách trống!\n";
        return;
    }

    SvTrongLopHp* svLhpDangXet = dsSvTrongLhp->svDau;
    SvTrongLopHp* svLhpDaXet = NULL;

    // Tìm sinh viên theo mssv
    while(svLhpDangXet != NULL && svLhpDangXet->MSSV!= mssv){
        svLhpDaXet = svLhpDangXet;
        svLhpDangXet = svLhpDangXet->tiepTheo;
    }

    // Các trường hợp khi xoá sinh viên trong lớp học phần
    if(svLhpDangXet == NULL){
        cout << "Không tìm thấy sinh viên có MSSV "<< mssv << " trong lớp học phần!\n";
        return;
    }
    if(svLhpDangXet == dsSvTrongLhp->svDau){
        dsSvTrongLhp->svDau = svLhpDangXet->tiepTheo;
        if(dsSvTrongLhp->svDau == NULL){
            dsSvTrongLhp->svCuoi = NULL;
        }
    }
    else{
        svLhpDaXet->tiepTheo = svLhpDangXet->tiepTheo;
        if(svLhpDangXet == dsSvTrongLhp->svCuoi){
            dsSvTrongLhp->svCuoi = svLhpDaXet;
        }
    }
    delete svLhpDangXet;
    cout << "Đã xoá sinh viên có MSSV " << mssv << " trong lớp học phần!\n";

    return;
}
// Cập nhât sinh viên trong lớp học phần theo MSSV
void capNhatSvTrongLhp(DsSvTrongLopHp* dsSvTrongLhp, string mssv){
    SvTrongLopHp* svLhp = dsSvTrongLhp->svDau;

    // Tìm sinh viên trong lớp học phần có MSSV cần cập nhật
    while(svLhp!=NULL ){
        if(svLhp->MSSV == mssv){
            cout << "Nhập thông tin cập nhật sinh viên trong lớp học phần:\n";
            cout << "Nhập MSSV: "; getline(cin, svLhp->MSSV);
            cout << "Nhập điểm học phần:"; cin >> svLhp ->diemHocPhan;
            cin.ignore();

            cout << "Đã cập thông tin sinh viên trong lớp học phần!\n";
            return;
        }
        svLhp = svLhp->tiepTheo;
    }

    cout << "Không tìm thấy sinh viên có MSSV " << mssv << " trong lớp học phần!\n";

    return;
}

// ==================== Cấu trúc một lớp học phần ====================
struct LopHocPhan{
    string maLopHocPhan;
    string maHocPhan;
    string hocKy;
    DsSvTrongLopHp* dsSvLhp;
    LopHocPhan* tiepTheo;
};
// Hàm tạo một lớp học phần mới
LopHocPhan* taoLopHocPhan(){
    LopHocPhan* lhp = new LopHocPhan;
    cout << "Nhập thông tin lớp học phần mới:\n";
    cout << "Nhập mã lớp học phần: ";  getline(cin, lhp->maLopHocPhan);
    cout << "Nhập mã học phần: "; getline(cin, lhp->maHocPhan);
    cout << "Nhập học kỳ: "; getline(cin, lhp->hocKy);

    lhp->dsSvLhp = new DsSvTrongLopHp();
    lhp->dsSvLhp->svDau = NULL;
    lhp->dsSvLhp->svCuoi =NULL;

    lhp->tiepTheo = NULL;

    return lhp;
}
// In lớp học phần
void inLopHp(LopHocPhan* lhp){
    cout << lhp->maLopHocPhan << " | " << lhp->maHocPhan << " | " << lhp->hocKy << endl;
}
// ==================== Cấu trúc danh sách chứa các lớp học phần ====================
struct DsLopHocPhan { LopHocPhan* lhpDau; LopHocPhan* lhpCuoi; };
// Kiêm tra mã lớp học phần trong Danh sách lớp học phần
bool ktraLhpTrongDsLhp(DsLopHocPhan* dsLhp, string maLhp){
    LopHocPhan* lhp = dsLhp->lhpDau;

    while(lhp!= NULL){
        if(lhp->maLopHocPhan == maLhp) return TRUE;
        lhp = lhp->tiepTheo;
    }
    return FALSE;
}
// Thêm lớp học phần mới vào đầu danh sách lớp học phần
void themLhpMoi(DsLopHocPhan *dsLhp, DsHocPhan* dsHp){
    LopHocPhan* lhp = taoLopHocPhan();

    // Kiêm tra mã học phần của lớp học phần mới
    if(!ktraHpTrongDsHp(dsHp, lhp->maHocPhan)) {cout <<"Lớp học phần mới có mã học phần không có trong Danh sách học phần!\n"; return;}

    // Kiểm tra mã lớp học phần của lớp học phần mới
    if(ktraLhpTrongDsLhp(dsLhp, lhp->maLopHocPhan)){cout << "Lớp học phần có mã lớp học phần đã có trong Danh sách lớp học phần!\n"; return;}

    if(!dsLhp->lhpDau) dsLhp->lhpDau = dsLhp->lhpCuoi = lhp;
    else { dsLhp->lhpCuoi->tiepTheo = lhp; dsLhp->lhpCuoi = lhp; }
    cout << "Đã thêm lớp học phần có Mã lớp học phần " << lhp->maLopHocPhan << "!\n";

    return;
}
// Xoá lớp học phần theo mã lớp học phần
void xoaLhp(DsLopHocPhan* dsLhp, string maLhp){
    if(dsLhp->lhpDau == NULL){
        cout << "Danh sách trống!\n";
        return;
    }

    LopHocPhan* lhpDangXet = dsLhp->lhpDau;
    LopHocPhan* lhpDaXet = NULL;

    // Tìm lớp học phần có mã lớp học phần cần xoá
    while(lhpDangXet != NULL && lhpDangXet->maLopHocPhan != maLhp){
        lhpDaXet = lhpDangXet;
        lhpDangXet = lhpDangXet->tiepTheo;
    }

    // Các trường hợp khi xoá lớp học phần
    if(lhpDangXet == NULL){
        cout << "Không tìm thấy lớp học phần có Mã lớp học phần "<< maLhp <<"!\n";
        return;
    }
    if(lhpDangXet == dsLhp->lhpDau){
        dsLhp->lhpDau = lhpDangXet->tiepTheo;
        if(dsLhp->lhpDau == NULL){
            dsLhp->lhpCuoi = NULL;
        }
    }
    else{
        lhpDaXet->tiepTheo = lhpDangXet->tiepTheo;
        if(lhpDangXet == dsLhp->lhpCuoi){
            dsLhp->lhpCuoi = lhpDaXet;
        }
    }
    delete lhpDangXet;

    cout << "Đã xoá lớp học phần có Mã lớp học phần " << maLhp << "!\n";
}
// Cập nhât lớp học phần theo Mã lớp học phần
void capNhatLhp(DsLopHocPhan* dsLhp, string maLhp){
    LopHocPhan* lhp = dsLhp->lhpDau;

    // Tìm lớp học phần có mã lớp học phần cần cập nhật
    while(lhp!=NULL ){
        if(lhp->maLopHocPhan == maLhp){
            cout << "Nhập thông tin mới lớp học phần:\n";
            cout << "Nhập mã lớp học phần: ";  getline(cin, lhp->maLopHocPhan);
            cout << "Nhập mã học phần: "; getline(cin, lhp->maHocPhan);
            cout << "Nhập học kỳ: "; getline(cin, lhp->hocKy);
            cout << "Đã cập nhật thông tin lớp học phần có Mã lớp học phần "<< maLhp << "!\n";
            return;
        }
        lhp = lhp->tiepTheo;
    }

    cout << "Không tìm thấy học phần có Mã lớp học phần " << maLhp << "!\n";

    return;
}
// Xác định lớp học phần và xoá sinh viên trong lớp học phần đó
void xoaSvTheoMaLhp(DsLopHocPhan* dsLhp, string maLhp, string mssv){
    LopHocPhan* lhp = dsLhp->lhpDau;

    // Tim lớp học phần theo mã lớp học phần
    while(lhp != NULL){
        if(lhp->maLopHocPhan == maLhp){
            xoaSvTrongLhp(lhp->dsSvLhp, mssv);
            return;
        }
        lhp = lhp->tiepTheo;
    }
    if(lhp == NULL){cout << "Không tìm thấy lớp học phần có Mã lớp học phần " << maLhp << "!\n";}
}
// Xác định lớp học phần và cập nhật sinh viên trong lớp học phần đó
void capNhatSvTheoMaLhp(DsLopHocPhan* dsLhp, string maLhp, string mssv){
    // Tim lớp học phần theo mã lớp học phần
    LopHocPhan* lhp = dsLhp->lhpDau;
    while(lhp != NULL){
        if(lhp->maLopHocPhan == maLhp){
            capNhatSvTrongLhp(lhp->dsSvLhp, mssv);
            return;
        }
        lhp = lhp->tiepTheo;
    }

    if(lhp == NULL){cout << "Không tìm thấy lớp học phần có Mã lớp học phần " << maLhp <<"!\n";}

    return;
}
// In danh sách lớp học phần
void inDanhSachLhp(DsLopHocPhan* dsLhp){
    cout << "-----Danh sách lớp học phần-----\n";
    LopHocPhan* lhp = dsLhp->lhpDau;
    while(lhp != NULL){
        inLopHp(lhp);
        lhp = lhp->tiepTheo;
    }

    cout << endl;
    return;
}
// Tim lớp học phần theo mã lớp học phần
void inDanhSvTrongLhp(DsLopHocPhan* dsLhp, string maLhp){

    LopHocPhan* lhp = dsLhp->lhpDau;

    while(lhp != NULL){
        if(lhp->maLopHocPhan == maLhp){
            SvTrongLopHp* svLhp = lhp->dsSvLhp->svDau;
            while(svLhp != NULL){
                cout << svLhp->MSSV << " | " << svLhp->diemHocPhan << endl;
                svLhp = svLhp->tiepTheo;
            }
            return;
        }
        lhp = lhp->tiepTheo;
    }
}
// Kiểm tra sinh viên đã từng học học phần đó chưa
bool ktraSvDkiMaHp(DsLopHocPhan* dsLhp, string mssv, string maHp){
    LopHocPhan* lhp = dsLhp->lhpDau;
    while(lhp != NULL){
        if(lhp->maHocPhan == maHp){
            SvTrongLopHp* sv = lhp->dsSvLhp->svDau;
            while(sv!=NULL){
                if(sv->MSSV == mssv){
                    return TRUE;
                }
                sv = sv->tiepTheo;
            }
        }
        lhp = lhp->tiepTheo;
    }
    return FALSE;
}
//Sinh viên được thêm vào vị trí đầu tiên một lớp học phần theo MSSV
void svDkiLopHocPhan(DsLopHocPhan* dsLhp, string maLhp, DsSinhVien* dsSv){
    LopHocPhan* lhp = dsLhp->lhpDau;
    bool dKi = FALSE;

    // Tìm mã lớp học phần và kiểm tra với mã học phần tương ứng mã lớp đó, sinh viên đã đăng ký trước đây hay chưa
    while(lhp != NULL){
        if(lhp->maLopHocPhan == maLhp){
            SvTrongLopHp* svDki = taoSvTrongLopHp();
            //Kiểm tra MSSV của sinh viên đăng ký trong Danh sách sinh viên
            if(!ktraSvTrongDsSv(dsSv, svDki->MSSV)) {cout << "MSSV đăng ký không có trong Danh sách sinh viên!\n"; return;}
            if(ktraSvDkiMaHp(dsLhp,svDki->MSSV,lhp->maHocPhan)){cout << "Đăng ký không thành công!\n"; return;}

            dKi = TRUE;
            cout << "Đăng ký thành công!\n";
            // Thêm sinh viên vào vị trí đầu danh sách sinh viên của lớp học phần
            if(lhp->dsSvLhp->svDau == NULL){
                lhp->dsSvLhp->svDau= svDki;
                lhp->dsSvLhp->svCuoi = svDki;
            }else{
                svDki->tiepTheo = lhp->dsSvLhp->svDau;
                lhp->dsSvLhp->svDau = svDki;
            }
        }
        lhp = lhp->tiepTheo;
    }
    if(!dKi){
         cout << "Đăng ký không thành công!\n";
    }
    cout << "-----Danh sách sinh viên lớp học phần có Mã lớp học phần " << maLhp <<"-----\n";
    inDanhSvTrongLhp(dsLhp, maLhp);

    return;
}
// =========================================================
// 2. TÍNH NĂNG CỐT LÕI
// =========================================================
// Nhập điểm theo MSSV + Mã học phần
void capNhatDiemCuaSvTheoHp(DsLopHocPhan* dsLop, string mssv, string maHP, float diemMoiNhat) {
    LopHocPhan* lhp = dsLop->lhpDau;
    bool daNhapDuoc = false;

    // Duyệt qua tất cả các lớp học phần và tìm kiếm theo MSSV trong từng lớp học phần
    while (lhp != NULL) {
        if (lhp->maHocPhan == maHP) {
            SvTrongLopHp* svLhp = lhp->dsSvLhp->svDau;
            while (svLhp != NULL) {
                if (svLhp->MSSV == mssv) {
                    svLhp->diemHocPhan = diemMoiNhat;
                    cout << "Đã cập nhật điểm cho sinh viên " << mssv<< " trong lớp có Mã lớp học phần " << lhp->maLopHocPhan << "!\n";
                    daNhapDuoc = true;
                    break;
                }
                svLhp = svLhp->tiepTheo;
            }
        }
        if (daNhapDuoc) break;
        lhp = lhp->tiepTheo;
    }

    if (!daNhapDuoc) {
        cout << "Không tìm thấy sinh viên " << mssv << " đăng ký học phần có Mã hoc phần " << maHP << "!\n";
    }

    return;
}
// =========================================================
// 3. LOGIC NGHIỆP VỤ
// =========================================================
// Quy đổi hệ 10 sang hệ 4
float quyDoiHe4(float diemHe10) {
    if (diemHe10 >= 8.5) return 4.0;
    if (diemHe10 >= 8.0) return 3.5;
    if (diemHe10 >= 7.0) return 3.0;
    if (diemHe10 >= 6.5) return 2.5;
    if (diemHe10 >= 5.5) return 2.0;
    if (diemHe10 >= 5.0) return 1.5;
    if (diemHe10 >= 4.0) return 1.0;
    return 0.0;
}
// ==================== Tính điểm trung bình học kỳ hệ 4 của một sinh viên====================
void tinhGPATheoKy(string mssv, string hky, DsLopHocPhan* dsLop, DsHocPhan* dsHp) {
    float tongDiemGpaHe4 = 0;
    float tongTinChi = 0;

    // Tìm các lớp học phần mà sinh viên đã tham gia
    LopHocPhan* lhp = dsLop->lhpDau;
    while (lhp != NULL) {
        SvTrongLopHp* svLhp = lhp->dsSvLhp->svDau;
        while(svLhp != NULL){
            if(svLhp->MSSV == mssv && lhp->hocKy == hky){
                float soTinChiHp = soTinChiCuaMaHp(lhp->maHocPhan, dsHp);
                tongDiemGpaHe4 += quyDoiHe4(svLhp->diemHocPhan) * soTinChiHp;
                tongTinChi += soTinChiHp;
                break;
            }
            svLhp = svLhp->tiepTheo;
        }
        lhp = lhp->tiepTheo;
    }

    cout << "-----KẾT QUẢ HỌC TẬP CỦA SINH VIÊN----- " << mssv << endl;
    if (tongTinChi == 0) {
        cout << "Sinh viên chưa có điểm hoặc không tồn tại.\n";
    } else {
        float gpa4 = tongDiemGpaHe4 / tongTinChi;
        cout << "Tổng tín chỉ của kỳ " << hky << ": "   << tongTinChi << endl;
        cout << "Điểm trung bình: " << fixed << setprecision(2) << gpa4 << endl;

        cout << "Xếp loại học lực: ";
        if (gpa4 >= 3.6) cout << "Xuất sắc" << endl;
        else if (gpa4 >= 3.2) cout << "Giỏi" << endl;
        else if (gpa4 >= 2.5) cout << "Khá" << endl;
        else if (gpa4 >= 2.0) cout << "Trung bình" << endl;
        else cout << "Yếu" << endl;
    }
}
// ==================== Tính điểm tích luỹ hệ 4 của một sinh viên ====================
void tinhCPA(string mssv, DsLopHocPhan* dsLop, DsHocPhan* dsHp) {
    float tongDiemGpaHe4 = 0;
    float tongTinChi = 0;

    // Tìm các lớp học phần mà sinh viên đã tham gia
    LopHocPhan* lhp = dsLop->lhpDau;
    while (lhp != NULL) {
        SvTrongLopHp* svLhp = lhp->dsSvLhp->svDau;
        while(svLhp != NULL){
            if(svLhp->MSSV == mssv){
                int soTinChiHp = soTinChiCuaMaHp(lhp->maHocPhan, dsHp);
                tongDiemGpaHe4 += quyDoiHe4(svLhp->diemHocPhan) * soTinChiHp;
                tongTinChi += soTinChiHp;
                break;
            }
            svLhp = svLhp->tiepTheo;
        }
        lhp = lhp->tiepTheo;
    }

    cout << "-----KẾT QUẢ HỌC TẬP CỦA SINH VIÊN----- " << mssv << endl;
    if (tongTinChi == 0) {
        cout << "Sinh viên chưa có điểm hoặc không tồn tại." << endl;
    } else {
        float cpa4 = tongDiemGpaHe4 / tongTinChi;
        cout << "Tổng tín chỉ tích lũy: " << tongTinChi << endl;
        cout << "Điểm trung bình tích luỹ: " << fixed << setprecision(2) << cpa4 << endl;

        cout << "Xếp loại học lực: ";
        if (cpa4 >= 3.6) cout << "Xuất sắc" << endl;
        else if (cpa4 >= 3.2) cout << "Giỏi" << endl;
        else if (cpa4 >= 2.5) cout << "Khá" << endl;
        else if (cpa4 >= 2.0) cout << "Trung bình" << endl;
        else cout << "Yếu" << endl;
    }
    return;
}
// =========================================================
// 4.BÁO CÁO VÀ TÌM KIẾM
// =========================================================
// ==================== Tìm kiếm và hiển thị bảng điểm của một sinh viên ====================
void hienThiBangDiemCuaSinhVien(string mssv, DsLopHocPhan* dsLhp){
    // Tìm các lớp học phần mà sinh viên đã tham gia
    LopHocPhan* lhp = dsLhp->lhpDau;
    bool coHoc = FALSE;

    while (lhp != NULL) {
        SvTrongLopHp* svLhp = lhp->dsSvLhp->svDau;
        while(svLhp != NULL){
            if(svLhp->MSSV == mssv){
                cout << lhp->maHocPhan << " " << svLhp->diemHocPhan << endl;
                coHoc = TRUE;
            }
            svLhp = svLhp->tiepTheo;
        }
        lhp = lhp->tiepTheo;
    }

    if(!coHoc){
        cout << "Sinh viên chưa đăng ký học phần nào!\n" ;
    }

    return;
}
// ==================== In bảng điểm của lớp học phần ====================
void bangDiemCuaLopHocPhan(string maLopHp, DsLopHocPhan* dsLhp){
    LopHocPhan* lhp = dsLhp->lhpDau;
    bool coLhp = FALSE;

    while (lhp != NULL) {
        if(lhp->maLopHocPhan == maLopHp){
            SvTrongLopHp* svLhp = lhp->dsSvLhp->svDau;
            while(svLhp!= NULL){
                cout << svLhp->MSSV << " " << svLhp->diemHocPhan << endl;
                svLhp = svLhp->tiepTheo;
            }
            coLhp = TRUE;
        }
        lhp = lhp->tiepTheo;
    }

    if(!coLhp){
        cout << "Không tìm thấy lớp học phần có mã lớp học phần" << maLopHp << "!\n";
    }

    return;
}
// =========================================================
// 5. ĐỌC/GHI DỮ LIỆU TỪ/VÀO FILE
// =========================================================
// ==================== Đọc/Ghi danh sách sinh viên từ/vào file ====================
void ghiFileSinhVien(DsSinhVien* dsSv) {
    ofstream outFile("DsSinhVien.txt");
    if (!outFile) { cout << "Không thể tạo hoặc mở file DsSinhVien.txt!\n"; return; }

    SinhVien* sv = dsSv->svDau;
    while (sv != NULL) {
        outFile << sv->MSSV << "," << sv->hoTen << "," << sv->lop << ","
                << sv->ngaySinh.ngay << " " << sv->ngaySinh.thang << " " << sv->ngaySinh.nam << endl;
        sv = sv->tiepTheo;
    }

    outFile.close();
    cout << "Đã lưu danh sách sinh viên xuống file DsSinhVien.txt!\n";
    return;
}

void themSinhVienDocTuFile(DsSinhVien* dsSv, SinhVien* sv) {
    if (!dsSv->svDau) dsSv->svDau = dsSv->svCuoi = sv;
    else { dsSv->svCuoi->tiepTheo = sv; dsSv->svCuoi = sv; }
}

void docFileSinhVien(DsSinhVien* dsSv) {
    ifstream inFile("DsSinhVien.txt");
    if (!inFile) { cout << "Không tìm thấy file DsSinhVien.txt để đọc!\n"; return; }

    dsSv->svDau = dsSv->svCuoi = NULL;
    string mssv, hoten, lop;
    int d, m, y;

    while (getline(inFile, mssv, ',')) {
        getline(inFile, hoten, ',');
        getline(inFile, lop, ',');
        inFile >> d >> m >> y;
        inFile.ignore();

        SinhVien* sv = new SinhVien();
        sv->MSSV = mssv;
        sv->hoTen = hoten;
        sv->lop = lop;
        sv->ngaySinh.ngay = d;
        sv->ngaySinh.thang = m;
        sv->ngaySinh.nam = y;
        sv->tiepTheo = NULL;

        themSinhVienDocTuFile(dsSv, sv);
    }

    inFile.close();
    cout << "Đã đọc danh sách sinh viên từ file DsSinhVien.txt!\n";
    return;
}
// ==================== Đọc/ghi danh sách học phần từ/vào file ====================
void ghiFileDsHocPhan(DsHocPhan* dsHp) {
    ofstream outFile("DsHocPhan.txt");
    if (!outFile) { cout << "Không thể tạo hoặc mở file DsHocPhan.txt!\n"; return; }

    HocPhan* hp = dsHp->hpDau;
    while (hp != NULL) {
        outFile << hp->maHocPhan << "," << hp->tenHocPhan << "," << hp->soTinChi << endl;
        hp = hp->tiepTheo;
    }

    outFile.close();
    cout << "Đã ghi danh sách học phần vào file DsHocPhan.txt!\n";
    return;
}

void themHocPhanDocTuFile(DsHocPhan* dsHp, HocPhan* hp) {
    if (!dsHp->hpDau) dsHp->hpDau = dsHp->hpCuoi = hp;
    else { dsHp->hpCuoi->tiepTheo = hp; dsHp->hpCuoi = hp; }
}

void docFileDsHocPhan(DsHocPhan* dsHp) {
    ifstream inFile("DsHocPhan.txt");
    if (!inFile) { cout << "Không tìm thấy file DsHocPhan.txt để đọc!\n"; return; }

    dsHp->hpDau = dsHp->hpCuoi = NULL;
    string maHp, tenHp;
    float stc;

    while (getline(inFile, maHp, ',')) {
        getline(inFile, tenHp, ',');
        inFile >> stc;
        inFile.ignore();

        HocPhan* hp = new HocPhan();
        hp->maHocPhan = maHp;
        hp->tenHocPhan = tenHp;
        hp->soTinChi = stc;
        hp->tiepTheo = NULL;

        themHocPhanDocTuFile(dsHp, hp);
    }

    inFile.close();
    cout << "Đã đọc danh sách học phần từ file DsHocPhan.txt!\n";
    return;
}

// ==================== Đọc/ghi một lớp học phần từ/vào file ====================
void ghiFileLopHocPhan(LopHocPhan* lopHp) {
    string tenFile = "Lop_" + lopHp->maLopHocPhan + ".txt";
    ofstream outFile(tenFile);
    if (!outFile) { cout << " Không thể tạo file cho lớp học phần " << tenFile << "!\n"; return; }

    SvTrongLopHp* svLhp = lopHp->dsSvLhp->svDau;
    while (svLhp != NULL) {
        outFile << svLhp->MSSV << "," << svLhp->diemHocPhan << endl;
        svLhp = svLhp->tiepTheo;
    }

    outFile.close();
     cout << " Đã ghi file cho lớp học phần " << tenFile << "!\n";
     return;
}

void themSvLopHocPhanDocTuFile(LopHocPhan* lopHp, SvTrongLopHp* svLhp) {
    if (!lopHp->dsSvLhp->svDau) lopHp->dsSvLhp->svDau = lopHp->dsSvLhp->svCuoi = svLhp;
    else { lopHp->dsSvLhp->svCuoi->tiepTheo = svLhp; lopHp->dsSvLhp->svCuoi = svLhp; }
}

void docFileLopHocPhan(LopHocPhan* lopHp) {
    string tenFile = "Lop_" + lopHp->maLopHocPhan + ".txt";
    ifstream inFile(tenFile);
    if (!inFile) return;

    lopHp->dsSvLhp->svDau = lopHp->dsSvLhp->svCuoi = NULL;
    string mssv;
    float diem;

    while (getline(inFile, mssv, ',')) {
        inFile >> diem;
        inFile.ignore();

        SvTrongLopHp* svLhp = new SvTrongLopHp();
        svLhp->MSSV = mssv;
        svLhp->diemHocPhan = diem;
        svLhp->tiepTheo = NULL;

        themSvLopHocPhanDocTuFile(lopHp, svLhp);
    }
    inFile.close();
    cout << "Đã đọc danh sách học phần từ file " << tenFile << "!\n";
}
// ==================== Đọc/ghi danh sách lớp học phần và mỗi lớp học phần từ/vào file ====================
void ghiFileDsLopHocPhan(DsLopHocPhan* dsLhp) {
    ofstream outFile("DsLopHocPhan.txt");
    if (!outFile) { cout << "Không thể tạo file DsLopHocPhan.txt!\n"; return; }

    LopHocPhan* lhp = dsLhp->lhpDau;
    while (lhp != NULL) {
        outFile << lhp->maLopHocPhan << "," << lhp->maHocPhan << "," << lhp->hocKy << endl;

        ghiFileLopHocPhan(lhp);

        lhp = lhp->tiepTheo;
    }
    outFile.close();
    cout << "Đã ghi danh sách các lớp học phần vào file DsLopHocPhan.txt!\n";
}

void themLopHocPhanDocTuFile(DsLopHocPhan* dsLhp, LopHocPhan* lhp) {
    if (!dsLhp->lhpDau) dsLhp->lhpDau = dsLhp->lhpCuoi = lhp;
    else { dsLhp->lhpCuoi->tiepTheo = lhp; dsLhp->lhpCuoi = lhp; }
}

void docFileDsLopHocPhan(DsLopHocPhan* dsLhp) {
    ifstream inFile("DsLopHocPhan.txt");
    if (!inFile) { cout << "Không tìm thấy file DsLopHocPhan.txt để đọc!\n"; return; }

    dsLhp->lhpDau = dsLhp->lhpCuoi = NULL;
    string maLhp, maHp, hky;

    while (getline(inFile, maLhp, ',')) {
        getline(inFile, maHp, ',');
        getline(inFile, hky);

        LopHocPhan* lhp = new LopHocPhan();
        lhp->maLopHocPhan = maLhp;
        lhp->maHocPhan = maHp;
        lhp->hocKy = hky;

        lhp->dsSvLhp = new DsSvTrongLopHp();
        lhp->dsSvLhp->svDau = NULL;
        lhp->dsSvLhp->svCuoi = NULL;
        lhp->tiepTheo = NULL;

        docFileLopHocPhan(lhp);

        themLopHocPhanDocTuFile(dsLhp, lhp);
    }
    inFile.close();
    cout << "Đã đọc danh sách lớp học phần và mỗi lớp học phần từ file DsLopHocPhan.txt!\n";
}

int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    DsSinhVien* dsSv = new DsSinhVien();
    dsSv->svDau = NULL;
    dsSv->svCuoi = NULL;

    DsHocPhan* dsHp = new DsHocPhan();
    dsHp->hpDau = NULL;
    dsHp->hpCuoi = NULL;

    DsLopHocPhan* dsLhp = new DsLopHocPhan();
    dsLhp->lhpDau = NULL;
    dsLhp->lhpCuoi = NULL;

    while(1){
        cout << "----------------MENU----------------\n";
        cout << "----------Danh sách sinh viên-------\n";
        cout << "1. Thêm sinh viên vào danh sách lớp\n";
        cout << "2. Duyệt danh sách sinh viên\n";
        cout << "3. Xoá sinh viên khỏi danh sách sinh viên\n";
        cout << "4. Cập nhât thông tin sinh viên trong danh sách sinh viên\n";
        cout << "----------Danh sách học phần---------\n";
        cout << "5. Thêm học phần mới vào danh sách học phần\n";
        cout << "6. Duyệt danh sách học phần\n";
        cout << "7. Xoá học phần khỏi danh học phần\n";
        cout << "8. Cập nhật thông tin học phần trong danh sách học phần\n";
        cout << "----------Danh sách lớp học phần-------\n";
        cout << "9. Thêm lớp học phần mới vào danh sách lớp học phần\n";
        cout << "10. Duyệt danh sách lớp học phần\n";
        cout << "11. Xoá lớp học phần khỏi danh sách lớp học phần\n";
        cout << "12. Cập nhật thông tin lớp học phần trong danh sách lớp học phần\n";
        cout << "13. Sinh viên đăng ký lớp học phần\n";
        cout << "14. Xoá sinh viên theo MSSV khỏi lớp học phần\n";
        cout << "15. Cập nhật thông tin sinh viên theo MSSV trong lớp học phần\n";
        cout << "16. Cập nhật điểm sinh viên theo MSSV và Mã học phần\n";
        cout << "----------Logic nghiệp vụ và báo cáo tìm kiếm-----------\n";
        cout << "17. Hiển thị bảng điểm của sinh viên theo MSSV\n";
        cout << "18. Hiển thị bảng điểm của lớp học phần theo Mã lớp HP\n";
        cout << "19. Tính điểm GPA học kỳ của sinh viên\n";
        cout << "20. Tính điểm CPA tích lũy của sinh viên\n";
        cout << "----------Đọc ghi file-----------------\n";
        cout << "21. Ghi vào file chứa danh sách sinh viên\n";
        cout << "22. Đọc file chứa danh sách sinh viên\n";
        cout << "0. Thoát chương trình\n";
        cout << "------------------------------------\n";
        cout << "Nhập lựa chọn :";
        int lc; cin >> lc;
        cin.ignore();

        if(lc == 1){
            themSvMoi(dsSv);
            inDanhSachSv(dsSv);
        }else if(lc == 2){
            inDanhSachSv(dsSv);
        }else if(lc == 3){
            string mssv;
            cout << "Nhập MSSV cần xoá: "; getline(cin, mssv);
            xoaSv(dsSv, mssv);
            inDanhSachSv(dsSv);
        }else if(lc == 4){
            string mssv;
            cout << "Nhập MSSV cần cập nhật: "; getline(cin, mssv);
            capNhatSv(dsSv, mssv);
            inDanhSachSv(dsSv);
        }else if(lc == 5){
            themHpMoi(dsHp);
            inDanhSachHp(dsHp);
        }else if(lc == 6){
            inDanhSachHp(dsHp);
        }else if(lc == 7){
            string maHp;
            cout << "Nhập Mã học phần cần xoá: "; getline(cin, maHp);
            xoaHp(dsHp, maHp);
            inDanhSachHp(dsHp);
        }else if(lc == 8){
            string maHp;
            cout << "Nhập Mã học phần cần cập nhật: "; getline(cin, maHp);
            capNhatHp(dsHp, maHp);
            inDanhSachHp(dsHp);
        }else if(lc == 9){
            themLhpMoi(dsLhp, dsHp);
            inDanhSachLhp(dsLhp);
        }else if(lc == 10){
            inDanhSachLhp(dsLhp);
        }else if(lc == 11){
            string maLhp;
            cout << "Nhập Mã lớp học phần cần xoá: "; getline(cin, maLhp);
            xoaLhp(dsLhp, maLhp);
            inDanhSachLhp(dsLhp);
        }else if(lc == 12){
            string maLhp;
            cout << "Nhập Mã lớp học phần cần cập nhật: "; getline(cin, maLhp);
            capNhatLhp(dsLhp, maLhp);
            inDanhSachLhp(dsLhp);
        }else if(lc == 13){
            string maLhp;
            cout << "Nhập mã lớp học phần muốn đăng ký: "; getline(cin, maLhp);
            svDkiLopHocPhan(dsLhp, maLhp, dsSv);
        }else if(lc == 14){
            string mssv, maLhp;
            cout << "Nhập MSSV cần xoá: "; getline(cin, mssv);
            cout << "Nhập Mã lớp học phần cần tìm: "; getline(cin, maLhp);
            xoaSvTheoMaLhp(dsLhp, maLhp,mssv);
        }else if(lc == 15){
            string mssv, maLhp;
            cout << "Nhập MSSV cần cập nhật: "; getline(cin, mssv);
            cout << "Nhập Mã lớp học phần cần tìm: "; getline(cin, maLhp);
            capNhatSvTheoMaLhp(dsLhp, maLhp, mssv);
        }else if(lc == 16){
            string MSSV, maHp;
            float diemMoi;
            cout << "Nhập MSSV: "; getline(cin, MSSV);
            cout << "Nhập Mã học phần: "; getline(cin, maHp);
            cout << "Nhập điểm mới nhất: "; cin >> diemMoi;
            cin.ignore();
            capNhatDiemCuaSvTheoHp(dsLhp, MSSV, maHp, diemMoi);
        }else if(lc == 17){
            string mssv;
            cout << "Nhập MSSV cần hiển thị bảng điểm: "; getline(cin, mssv);
            hienThiBangDiemCuaSinhVien(mssv, dsLhp);
        }else if(lc == 18){
            string maLopHp;
            cout << "Nhập Mã lớp học phần cần hiển thị bảng điểm: "; getline(cin, maLopHp);
            bangDiemCuaLopHocPhan(maLopHp, dsLhp);
        }else if(lc == 19){
            string mssv, hky;
            cout << "Nhập MSSV: "; getline(cin, mssv);
            cout << "Nhập học kỳ: "; getline(cin, hky);
            tinhGPATheoKy(mssv, hky, dsLhp, dsHp);
        }else if(lc == 20){
            string mssv;
            cout << "Nhập MSSV: "; getline(cin, mssv);
            tinhCPA(mssv, dsLhp, dsHp);
        }else if(lc == 21){
            cout << "Ghi tất cả danh sách vào file: " << endl;
            ghiFileSinhVien(dsSv);
            ghiFileDsLopHocPhan(dsLhp);
            ghiFileDsHocPhan(dsHp);
        }else if(lc == 22){
            cout << "Đọc tất cả danh sách từ file: " << endl;
            docFileSinhVien(dsSv);
            docFileDsLopHocPhan(dsLhp);
            docFileDsHocPhan(dsHp);
        }else if(lc == 0){
            break;
        }
    }

    return 0;
}
