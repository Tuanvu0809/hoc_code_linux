# Bài tập 2

• Viết chương trình mà tiến trình cha thiết lập một biến môi trường (ví dụ:
MY_COMMAND=ls)

• Tiến trình con sẽ đọc biến môi trường này. Dựa vào giá trị đọc được, nó sẽ
dùng họ hàm exec() (ví dụ execlp()) để thực thi lệnh tương ứng (ls, date,...).

• Trong báo cáo, giải thích: Điều gì xảy ra với không gian địa chỉ và mã lệnh
của tiến trình con sau khi exec() được gọi thành công? 

Chương trình sẽ nhận tham số khi build target 
    **Target build sẽ có tên là process_exec**

Chương trình chính:

- Nhận tham số khi build *./process_exec* 
        
        + Nếu ko có tham số thì chương trình sẽ in ra lỗi  cần nhập tham số và thoát chương trình.
        + Nếu có tham số chương trình sẽ tạo ra tiến trình con và thực hiện câu lệnh tiếp theo.

- Tạo ra tiến trình con bằng *folk()* và gán cho biến pid

        + Nếu không tạo được tiến trình mới thì in ra thông báo lỗi và thoát chương trình.

- Đặt biến môi trường bằng lệnh *setenv()* : đặt biến môi trường *MY_COMMAND* và ghi đè lên biến này giá trị của tham số thứ 1.

- Kiểm tra *MY_COMMAND* và truyền các argv vào hàm *execvp* nếu thành công sẽ thực hiện các câu lệnh trong cmd.
        + Nếu *MY_COMMAND* đúng với hệ thống thì sẽ thực hiện yêu cầu không sẽ in ra thông báo lỗi.

- Tiến trình cha sẽ chờ tiến trình con kết thúc.  
