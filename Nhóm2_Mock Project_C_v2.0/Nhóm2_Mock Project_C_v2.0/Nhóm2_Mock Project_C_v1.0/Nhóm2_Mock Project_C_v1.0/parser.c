#include <stdio.h>

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

/* Hàm phân tích một dòng S-record */
void parse_line(const char* line, FILE* output, int line_number, char* last_record_type, int* s1_s2_s3_count) {
    int return_flag = 0; // Biến để theo dõi lỗi
    int length;
    int expected_length;
    int actual_length;
    int address; // Khai báo biến address
    char data[256];
    int max;
    /* Đọc loại bản ghi */
    char record_type = line[1];

    // Kiểm tra ký tự không hợp lệ
    if (!kiem_tra_ky_tu_hop_le(line, line_number)) {
        return_flag = 1; // Đánh dấu lỗi nếu có ký tự không hợp lệ
    }

    /* Kiểm tra ký tự đầu tiên */
    if (line[0] != 'S') {
        fprintf(stderr, "Loi: Dong %d khong bat dau bang 'S'\n", line_number);
        return_flag = 1;
    }

    /* Kiểm tra chiều dài chuỗi giới hạn 78 ký tự */
    max = 0;
    while (line[max] != '\0') {
        max++;
    }
    /* Kiểm tra độ dài cho các dòng */
    if (max > 78) {
        fprintf(stderr, "Loi: Dong %d vuot qua chieu dai toi da 78 ky tu\n", line_number);
        return_flag = 1;
    }

    /* Kiểm tra S4 không hợp lệ */
    if (record_type == '4') {
        fprintf(stderr, "Loi: Loai ban ghi khong hop le %c tai dong %d\n", record_type, line_number);
        return_flag = 1;
    }

    /* Kiểm tra dòng S0 */
    if (record_type == '0') {
        /* Đọc địa chỉ từ dòng S0 */
        address = hex_sang_byte(&line[4]) << 8 | hex_sang_byte(&line[6]); // Lấy địa chỉ từ ký tự thứ 4 và 6

        /* Kiểm tra xem địa chỉ có phải là 0000 không */
        if (address != 0x0000) {
            fprintf(stderr, "Loi: Dia chi trong dong S0 tai dong %d khong hop le (Du kien: 0000, Thuc te: %04X)\n", line_number, address);
            return_flag = 1;
        }
    }

    length = hex_sang_byte(&line[2]); // Đọc độ dài (trong hex)
    address = hex_sang_byte(&line[4]) << 8 | hex_sang_byte(&line[6]); // Đọc địa chỉ

    /* Tính toán độ dài dự kiến */
    expected_length = length * 2;

    /* Kiểm tra độ dài */
    actual_length = 0;
    while (line[4 + actual_length] != '\n' && line[4 + actual_length] != '\0') {
        actual_length++;
    }

    if (actual_length != expected_length) {
        fprintf(stderr, "Loi: kich thuoc do dai dia chi và du lieu khong dung tai dong %d (Du kien: %d, Thuc te: %d)\n", line_number, expected_length, actual_length);
        return_flag = 1;
    }

    /* Chuyển dữ liệu sang chuỗi */
    for (int i = 0; i < expected_length; i++) {
        data[i] = line[8 + i];
    }
    data[expected_length] = '\0';

    /* Kiểm tra checksum */
    unsigned char expected_checksum, calculated_checksum;
    if (!kiem_tra_checksum(line, &expected_checksum, &calculated_checksum)) {
        fprintf(stderr, "Loi: Checksum khong dung tai dong %d (Du kien: %02X, Thuc te: %02X)\n", line_number, expected_checksum, calculated_checksum);
        return_flag = 1;
    }

    /* Kiểm tra tính hợp lệ của bản ghi S */
    if (!kiem_tra_tinh_hop_le_cua_srecord(line, line_number, last_record_type, s1_s2_s3_count)) {
        return_flag = 1; // Nếu không hợp lệ thì đánh dấu lỗi
    }

    /* Kiểm tra S5/S6 */
    if (record_type == '5' || record_type == '6') {
        int address_s5_s6 = address;
        if (record_type == '5' && (*s1_s2_s3_count > 65535)) {
            fprintf(stderr, "Loi: So luong S1/S2/S3 vuot qua 2^16-1 tai dong %d.\n", line_number);
            return_flag = 1;
        }
        else if (record_type == '6' && (*s1_s2_s3_count > 16777215)) {
            fprintf(stderr, "Loi: So luong S1/S2/S3 vuot qua 2^24-1 tai dong %d.\n", line_number);
            return_flag = 1;
        }
        else if (address_s5_s6 != *s1_s2_s3_count) {
            fprintf(stderr, "Loi: Dia chi cua S%d tai dong %d khong bang tong so luong S1/S2/S3.\n", record_type - '0', line_number);
            return_flag = 1;
        }
    }

    /* Ghi thông tin vào tệp đầu ra nếu không có lỗi */
    if (return_flag == 0) {
        fprintf(output, "%d %04X %s\n", line_number, address, data);
    }
}

/* Hàm phân tích cú pháp tệp S-record */
void parse_srecord_file(const char* filename) {
    int return_flag = 0; // Biến để theo dõi lỗi
    char line[256];
    int line_number = 1;
    char last_record_type = '0'; // Khởi tạo loại bản ghi trước đó
    int s1_s2_s3_count = 0; // Đếm số lượng bản ghi S1/S2/S3

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Loi mo tep");
        return_flag = 1;
    }

    FILE* output = fopen("Output.txt", "w");
    if (output == NULL) {
        perror("Loi mo tep dau ra");
        fclose(file);
        return_flag = 1;
    }

    while (fgets(line, sizeof(line), file)) {
        parse_line(line, output, line_number, &last_record_type, &s1_s2_s3_count);
        line_number++;
    }

    fclose(file);
    fclose(output);

    /* Xóa checksum trong tệp đầu ra nếu không có lỗi */
    if (return_flag == 0) {
        remove_last_two_chars_from_file("Output.txt");
    }
}
