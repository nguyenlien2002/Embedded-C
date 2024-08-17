#include <stdio.h>

/* Hàm in hướng dẫn sử dụng */
void help(void) { /* Nếu chương trình chạy không đúng dòng cuối, thì hãy thêm kí tự xuống dòng (/n) vào vị trí cuối của dòng cuối cùng */
    printf("Cach su dung: Nhom2_Mock Project_C_v1.0 <Duong dan tep S-Record>\n");
    printf("Chuong trinh nay phan tich cu phap tep S-record va xuat thong tin vao Output.txt.\n");
    printf("Neu khong co loi hien thi nghia la du lieu da duoc chuyen vao Output.txt theo cau truc cua de bai\n");
    printf("Luu y!!! Neu dong cuoi cung chay khong dung kich ban, hay them ky tu xuong dong (//n) hoac khoang trang (//0) vao dong cuoi.\n");
}

int main(int argc, char* argv[]) {
    int return_code = 0; // Biến cờ để theo dõi trạng thái kết thúc
    const char* filename = argv[1];
    help(); /* gọi help() để hiển thị thông tin trợ giúp */

    if (argc != 2) {
        return_code = 1; /* Ghi nhận lỗi nếu số lượng tham số không đúng */
    }
    else {
        parse_srecord_file(filename);
    }
    return return_code; // Trả về mã kết thúc
}