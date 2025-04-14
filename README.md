# Game-AdvP
 Game project for INT2215
 
Họ và tên: Nghiêm Thành Long

Mã sinh viên: 24021554

Mô tả game: Người chơi sẽ có 8 lượt đoán một từ vựng tiếng Anh có 6 chữ cái. Nếu chữ cái đó ở đúng vị trí của từ đáp án sẽ hiển thị màu xanh, nếu chữ cái có xuất hiện trong từ đó nhưng sai vị trí sẽ hiển thị màu vàng, nếu chữ cái không có trong từ đó sẽ không hiển thị màu (màu trắng)

Ngưỡng điểm mong muốn: 7-8

Checklist

- Các phần tự làm
    - Thuật toán cho game (tham khảo game Wordle sau đó xây dựng thuật toán)
    - Vẽ bảng
    - Hiển thị các text vào ô tương ứng
    - Trạng thái thắng/thua, nếu thắng in ra “Congratulations”, nếu thua in ra đáp án được highlight khác màu
    - Sinh ngẫu nhiên từ trong bộ từ điển
    - Xử lý input chữ cái để so sánh với đáp án trong bộ từ điển, từ điển chỉ chọn ra những từ hợp lệ, không nhận những input không phải chữ cái
    - Hiển thị số lần chơi, số lần chiến thắng
- Các nguồn tham khảo
    - Trò chơi Wordle: [https://wordly.org](https://wordly.org/#google_vignette)
    - Ảnh: https://unsplash.com/photos/photo-of-outer-space-Q1p7bh3SHj8
    - Tra cứu keycode: https://wiki.libsdl.org/SDL2/SDLKeycodeLookup
    - Hướng dẫn về SDL2 Keycode và event bàn phím
        
        https://www.youtube.com/watch?v=EBHmMmiVtCk
        
    - Sử dụng inline liên kết các biến trong file defs.h và các file khác
        
        https://stackoverflow.com/questions/38043442/how-do-inline-variables-work
        
    - Code mẫu của cô Châu (hình ảnh, font chữ, event bàn phím, lệnh vẽ hình)
        
        https://docs.google.com/document/d/1FZ3jTqHxtyZznNWiJmmve0zYu_aSliUqLP2OsMcdehQ/edit?tab=t.0#heading=h.n8fowkm18xov
        
    - Sử dụng AI tra cứu các hàm SDL cơ bản, cách liên kết các biến trong các file header và cpp bằng việc sử dụng inline
- Có sử dụng các lệnh vẽ hình
- Có sử dụng background
- Có sử dụng event bàn phím
- Có sử dụng font
- Có tính điểm (số lần thắng game, tổng số lần chơi)
