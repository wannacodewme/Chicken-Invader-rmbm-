# Chicken Invaders 2 - RMBM - NHT

- Thử nghiệm game:

# Giới thiệu game: 
Chicken Invader 2 là một trò chơi bắn súng không gian thuộc thể loại Space Shooter. Trong trò chơi người chơi sẽ điều khiển một phi thuyền bắn hạ các đợt gà ngoài hành tinh đang tấn công. Trò chơi có nhiều cấp độ khác nhau, mỗi cấp độ đưa ra những thách thức mới đòi hỏi sự khéo léo của người chơi.


 # 1. Cách tải game: (bao gồm code và có thể biên dịch)
  **Bước 1:** Chọn Code -> Download Zip 
  ![image](https://github.com/user-attachments/assets/1cccc36c-4c28-44c8-8cb8-fb0139d3c1ee)

  **Bước 2:** Cài đặt visual studio 2022 và thư viện SDL2 (tham khảo cài đặt thư viện SDL2 theo hướng dẫn trong đường link bên dưới)
  
 https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/msvc2019/index.php
  
  
 https://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/windows/msvc2019/index.php
  
  Lưu ý: Cài đặt theo cả 2 đường link 

**Bước 3:** Giải nén file Zip mới tải về vào một folder tùy ý, sau khi giải nén xong sẽ có 1 file solution (.sln), mở file đó bằng visual studio và chạy game

# 2. Bắt đầu game:
Chờ một chút rồi click vào dòng chữ "PLAY" để bắt đầu chơi game

![image](https://github.com/user-attachments/assets/85848aba-93c1-43c1-a133-1240291c9a5d)

Ngay sau đó sẽ có giao diện bắt đầu trò chơi:

![image](https://github.com/user-attachments/assets/1d6fbcbd-32ab-4fd8-aad5-c3f45a563bca)

# 3. Các thành phần trong game: 
- Phi thuyền: ![ship_sprite](https://github.com/user-attachments/assets/9d497b14-5da0-43d7-be1a-cf699e4bc644) là vật thể người chơi điều khiển xuyên suốt game.
- Gà: ![image](https://github.com/user-attachments/assets/a63e5a69-364e-4bdd-823e-bad1e9408cb5) kẻ địch cần hạ trong màn chơi đầu.
- Các loại đạn và cấp độ của từng loại: ![image](https://github.com/user-attachments/assets/0452b9b0-4066-40b6-8846-193b3aff498e) các loại đạn mà phi thuyền có thể bắn
 

# 4. Cách chơi:
Người chơi sẽ di con trỏ chuột để tránh đạn của đối phương và các vật thể khác bay đến gần phi thuyền, nếu không để trúng đạn của kẻ địch hoặc không va phải các vật thể khác quá 3 lần người chơi sẽ thắng và màn hình hiển thị

![win](https://github.com/user-attachments/assets/da317650-23be-47fd-9b1b-3768713d0702)
còn nếu để 1 trong 2 tình huống đã nêu trên xảy ra tức trúng đạn hoặc vật thể 3 lần, người chơi sẽ thua.



