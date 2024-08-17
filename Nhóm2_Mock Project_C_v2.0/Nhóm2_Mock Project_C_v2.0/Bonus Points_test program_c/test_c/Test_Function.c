#include <stdio.h>

/* Hàm chuyển đổi từ chuỗi hex thành byte */
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
    int result = 1;
    int len = 0;
    while (line[len] != '\0') {
        len++;
    }
    if (len < 3) {
        result = 0;
    }
    else {
        *expected_checksum = hex_sang_byte(&line[len - 3]);
        *calculated_checksum = tinh_checksum(line);
        result = (*expected_checksum == *calculated_checksum) ? 1 : 0;
    }
    return result;
}

/* Hàm kiểm tra tính hợp lệ của các bản ghi S */
int kiem_tra_tinh_hop_le_cua_srecord(const char* line, int line_number, char* last_record_type, int* s1_s2_s3_count) {
    int valid = 1; // Biến tạm để theo dõi tính hợp lệ

    if (line[0] != 'S') {
        valid = 0; // Không phải dòng S-record
    }
    else {
        char current_record_type = line[1];
        // Kiểm tra nếu dòng trước đó là S1
        if (*last_record_type == '1') {
            if (current_record_type == '2' || current_record_type == '3') {
                fprintf(stderr, "Loi: Khong hop le, khong the co S%d sau S1 tai dong %d.\n", current_record_type - '0', line_number);
                valid = 0; // Không hợp lệ
            }
        }
        // Kiểm tra nếu dòng trước đó là S2
        else if (*last_record_type == '2') {
            if (current_record_type == '1' || current_record_type == '3') {
                fprintf(stderr, "Loi: Khong hop le, khong the co S%d sau S2 tai dong %d.\n", current_record_type - '0', line_number);
                valid = 0; // Không hợp lệ
            }
        }
        // Kiểm tra nếu dòng trước đó là S3
        else if (*last_record_type == '3') {
            if (current_record_type == '1' || current_record_type == '2') {
                fprintf(stderr, "Loi: Khong hop le, khong the co S%d sau S3 tai dong %d.\n", current_record_type - '0', line_number);
                valid = 0; // Không hợp lệ
            }
        }

        // Cập nhật loại bản ghi trước đó
        *last_record_type = current_record_type;

        // Đếm số lượng S1/S2/S3
        if (current_record_type >= '1' && current_record_type <= '3') {
            (*s1_s2_s3_count)++;
        }
    }
    return valid; // Trả về kết quả hợp lệ
}

// Hàm kiểm tra hex_sang_byte
void test_hex_sang_byte() {
    const char* test_hex = "3F";
    unsigned char result = hex_sang_byte(test_hex);
    printf("Test hex_sang_byte: %02X (Expected: 3F)\n", result);
}

// Hàm kiểm tra tinh_checksum
void test_tinh_checksum() {
    const char* test_line = "S1130000F00000FC\n";
    unsigned char result = tinh_checksum(test_line);
    printf("Test tinh_checksum: %02X (Expected: F1)\n", result);
}

// Hàm kiểm tra kiem_tra_checksum
void test_kiem_tra_checksum() {
    const char* test_line = "S1130000F00000FC\n";
    unsigned char expected_checksum, calculated_checksum;
    int result = kiem_tra_checksum(test_line, &expected_checksum, &calculated_checksum);
    printf("Test kiem_tra_checksum: %d (Expected: 1)\n", result);
    printf("Expected checksum: %02X, Calculated checksum: %02X\n", expected_checksum, calculated_checksum);
}

// Hàm kiểm tra kiem_tra_tinh_hop_le_cua_srecord
void test_kiem_tra_tinh_hop_le_cua_srecord() {
    const char* test_lines[] = {
        "S1130000F00000F1",
        "S1130000F00000FC",
        "S5030006F6",
        "S9030000FC"
    };
    char last_record_type = '0';
    int s1_s2_s3_count = 0;
    int i;
    int result = 1;

    for (i = 0; i < 4; i++) {
        if (!kiem_tra_tinh_hop_le_cua_srecord(test_lines[i], i + 1, &last_record_type, &s1_s2_s3_count)) {
            result = 0;
            break;
        }
    }

    printf("Test kiem_tra_tinh_hop_le_cua_srecord: %d (Expected: 1)\n", result);
}


int main() {
    printf("Chay cac kiem tra:\n");

    test_hex_sang_byte();
    test_tinh_checksum();
    test_kiem_tra_checksum();
    test_kiem_tra_tinh_hop_le_cua_srecord();

    return 0;
}
