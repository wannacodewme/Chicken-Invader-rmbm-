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

# 3. Các thành phần chính trong game: 
- Phi thuyền: là vật thể người chơi điều khiển xuyên suốt game.

   ![ship_sprite](https://github.com/user-attachments/assets/9d497b14-5da0-43d7-be1a-cf699e4bc644)

- Gà:  kẻ địch cần hạ trong màn chơi đầu.
  
   ![image](https://github.com/user-attachments/assets/a63e5a69-364e-4bdd-823e-bad1e9408cb5) 
  
- Các loại đạn và cấp độ của từng loại: các loại đạn mà phi thuyền có thể bắn
  
  ![image](https://github.com/user-attachments/assets/d24a6b74-772c-4212-9f22-af63585a669d)
  
- Khiên bảo vệ: người chơi va chạm hoặc trúng đạn sẽ hồi sinh với tấm khiên chắn mọi vật thể

  ![image](https://github.com/user-attachments/assets/c2d2b72c-da21-4645-8cb8-8c05ff547045)

- Thiên thạch: sẽ có một màn chơi với rất nhiều thiên thạch có kích cỡ khác nhau hướng về phía phi thuyền
  
  ![image](https://github.com/user-attachments/assets/4711f16f-3591-4f9f-b566-573b22e05018)

- Các hộp quà và mẫu phân tử: các hộp quà với màu sắc khác nhau là từng loại đạn khác nhau, mẫu phân tử dùng để tăng cấp đạn hiện tại.
   
  ![image](https://github.com/user-attachments/assets/ca7cb685-bed1-46df-9702-20f966793365)

- Trùm: là một dạng quái mạnh và ta cần bắn hạ
  
  ![image](https://github.com/user-attachments/assets/7641b003-75a4-4f57-82c2-0ff3b9b0aaf6)
 
- Đạn của trùm và quái thường: vật thể mà người chơi cần né tránh

  ![image](https://github.com/user-attachments/assets/d9222bd7-86e4-4023-97ae-26c0be352831)

- Meat: đơn vị tính điểm chính của trò chơi
  
  ![image](https://github.com/user-attachments/assets/efd5f6f6-3144-437d-9ccd-b3db632fd10d)

- Bảng điểm: lưu lại kết quả số điểm mà người chơi đạt được

  ![scoreboard](https://github.com/user-attachments/assets/cd57e264-6491-45e3-876e-11b5fae913ed)

- Dơi: xuất hiện ở màn chơi cuối thả đạn vào hướng phi thuyền
  
  ![bat](https://github.com/user-attachments/assets/89c07437-d1d7-4f7b-ab61-105eaf7c7a51)

  ![egg_1](https://github.com/user-attachments/assets/e64b0660-9b50-41de-be49-3dbfd054c8f7)


# 4. Cách chơi:
Người chơi sẽ click chuột trái để bắn đạn, di con trỏ chuột đến các vị trí vật phẩm rơi ra khi hạ gục quái để thu thập chúng, tránh đạn của đối phương và các vật thể khác bay đến gần phi thuyền, nếu không để trúng đạn của kẻ địch hoặc không va phải các vật thể khác quá 3 lần người chơi sẽ thắng và màn hình hiển thị

![win](https://github.com/user-attachments/assets/da317650-23be-47fd-9b1b-3768713d0702)

còn nếu để 1 trong 2 tình huống đã nêu trên xảy ra tức trúng đạn hoặc vật thể 3 lần, người chơi sẽ thua.

![image](https://github.com/user-attachments/assets/1562806b-e7be-4eeb-b69b-9bf0fbd83b6d)

Người chơi cũng có thể xem cách chơi tại mục "TUTORIAL" tại menu game khi mới bắt đầu chạy game

![image](https://github.com/user-attachments/assets/699b8b01-4cec-48ec-b69a-82453717aff4)

# 5. Source code:


