#include <stdio.h>

/* Hàm kiểm tra ký tự không hợp lệ */
int kiem_tra_ky_tu_hop_le(const char* line, int line_number) {
    for (int i = 1; line[i] != '\0'; i++) { // Bỏ qua ký tự đầu tiên
        char c = line[i];
        if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f') || (c == '\n') || (c == ' '))) {
            fprintf(stderr, "Loi: Ky tu khong hop le '%c' tai dong %d.\n", c, line_number);
            return 0; // Trả về 0 nếu có ký tự không hợp lệ
        }
    }
    return 1; // Trả về 1 nếu tất cả các ký tự hợp lệ
}

/* Hàm chuyển đổi chuỗi hex thành byte */
unsigned char hex_sang_byte(const char* hex_str) {
    unsigned char byte = 0;
    int i;
    for (i = 0; i < 2; i++) {
        char c = hex_str[i];
        byte <<= 4;
        if (c >= '0' && c <= '9') {
            byte |= c - '0';
        }
        else if (c >= 'A' && c <= 'F') {
            byte |= c - 'A' + 10;
        }
        else if (c >= 'a' && c <= 'f') {
            byte |= c - 'a' + 10;
        }
    }
    return byte;
}

/* Hàm tính toán checksum */
unsigned char tinh_checksum(const char* line) {
    unsigned int sum = 0;
    int i = 2;
    /* Tính chiều dài của chuỗi thủ công */
    int length = 0;
    while (line[length] != '\0') {
        length++;
    }

    /* Tính từ vị trí thứ 2 đến trước 2 ký tự cuối */
    while (i < length - 3) { // Chạy đến vị trí trước 2 ký tự cuối
        sum += hex_sang_byte(&line[i]);
        i += 2;
    }

    /* Bỏ byte cao nhất và lấy byte thấp nhất (LSB) */
    unsigned char lsb = sum & 0xFF;

    /* Tính checksum bằng cách lấy bổ sung của LSB */
    unsigned char checksum = 0xFF - lsb;
    return checksum;
}

/* Hàm kiểm tra checksum */
int kiem_tra_checksum(const char* line, unsigned char* expected_checksum, unsigned char* calculated_checksum) {
    int result = 1; // Mặc định ban đầu là đúng
    int len = 0;
    while (line[len] != '\0') {
        len++;
    }

    /* Kiem tra do dài dòng truoc khi truy cap */
    if (len < 3) {
        result = 0; // Không du chieu dài cho checksum
    }
    else {
        *expected_checksum = hex_sang_byte(&line[len - 3]);
        *calculated_checksum = tinh_checksum(line);
        result = (*expected_checksum == *calculated_checksum) ? 1 : 0;
    }

    return result; // Tra ve ket qua
}

/* Hàm xóa checksum của mỗi dòng trong tệp đầu ra */
void remove_last_two_chars_from_file(const char* filename) {
    int error_occurred = 0; // Biến cờ để theo dõi lỗi
    char buffer[256];
    /* Tạo tệp tạm thời để ghi dữ liệu đã chỉnh sửa */
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Loi mo tep dau ra");
        error_occurred = 1; // Ghi nhận lỗi
    }
    else {
        FILE* temp_file = fopen("Temp.txt", "w");
        if (temp_file == NULL) {
            perror("Loi mo tep tam thoi");
            fclose(file);
            error_occurred = 1;
        }
        else {
            while (fgets(buffer, sizeof(buffer), file)) {
                int len = 0;
                while (buffer[len] != '\0') {
                    len++;
                }
                if (len > 2) {
                    buffer[len - 3] = '\0'; // Xóa hai ký tự cuối cùng
                }
                fputs(buffer, temp_file);
            }
            fclose(temp_file);
        }
        fclose(file);
    }

    /* Xóa tệp cũ và đổi tên tệp tạm thời thành tệp gốc */
    if (!error_occurred) {
        if (remove(filename) != 0 || rename("Temp.txt", filename) != 0) {
            perror("Loi cap nhat tep");
        }
    }
    else {
        remove("Temp.txt"); // Xóa tệp tạm thời nếu có lỗi
    }
}
