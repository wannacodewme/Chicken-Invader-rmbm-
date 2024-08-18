# Chicken Invaders 2 - RMBM - NHT

# Giới thiệu bản thân:

Họ và tên: Nguyễn Huy Trà

Mã sinh viên: 22025524

Lớp: K67-N-CLC


# Thử nghiệm game: https://drive.google.com/drive/u/0/folders/1kXSCHKido4qmxt_vd1QJMSdnjqyLmlGE

# Giới thiệu game: 
Chicken Invader 2 là một trò chơi bắn súng không gian thuộc thể loại Space Shooter. Trong trò chơi người chơi sẽ điều khiển một phi thuyền bắn hạ các đợt gà ngoài hành tinh đang tấn công. Trò chơi có nhiều cấp độ khác nhau, mỗi cấp độ đưa ra những thách thức mới đòi hỏi sự khéo léo của người chơi.

- [1. Cách tải game](#1-cách-tải-game)
    * [a. Cách 1: Bao gồm code và có thể biên dịch.](#a-cách-1-bao-gồm-code-và-có-thể-biên-dịch)
    * [b. Cách 2: Không bao gồm code.](#b-cách-2-không-bao-gồm-code)
- [2. Bắt đầu game](#2-bắt-đầu-game)
- [3. Các thành phần chính trong game](#3-các-thành-phần-chính-trong-game)
- [4. Cách chơi](#4-cách-chơi)
- [5. Source code](#5-source-code)
- [6. Nguồn tham khảo](#6-nguồn-tham-khảo)


 # 1. Cách tải game 
 
 ## a. Cách 1: Bao gồm code và có thể biên dịch:
 
  **Bước 1:** Chọn Code -> Download Zip 
  ![image](https://github.com/user-attachments/assets/1cccc36c-4c28-44c8-8cb8-fb0139d3c1ee)

  **Bước 2:** Cài đặt visual studio 2022 và thư viện SDL2 (tham khảo cài đặt thư viện SDL2 theo hướng dẫn trong đường link bên dưới)
  
 https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/msvc2019/index.php
  
  
 https://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/windows/msvc2019/index.php
  
  Lưu ý: Cài đặt theo cả 2 đường link 

**Bước 3:** Giải nén file Zip mới tải về vào một folder tùy ý, sau khi giải nén xong sẽ có 1 file solution (.sln), mở file đó bằng visual studio và chạy game

## b. Cách 2: Không bao gồm code:

 Tải file Release.zip tại đường link: https://github.com/wannacodewme/Chicken-Invader-rmbm-/releases/tag/demo
 
 Khi tải xong giải nén vào 1 folder và click vào file exe để bắt đầu game.
 
# 2. Bắt đầu game

Chờ một chút rồi click vào dòng chữ "PLAY" để bắt đầu chơi game

![image](https://github.com/user-attachments/assets/85848aba-93c1-43c1-a133-1240291c9a5d)

Ngay sau đó sẽ có giao diện bắt đầu trò chơi:

![image](https://github.com/user-attachments/assets/1d6fbcbd-32ab-4fd8-aad5-c3f45a563bca)

# 3. Các thành phần chính trong game

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


# 4. Cách chơi
Người chơi sẽ click chuột trái để bắn đạn, di con trỏ chuột đến các vị trí vật phẩm rơi ra khi hạ gục quái để thu thập chúng, tránh đạn của đối phương và các vật thể khác bay đến gần phi thuyền, nếu không để trúng đạn của kẻ địch hoặc không va phải các vật thể khác quá 3 lần người chơi sẽ thắng và màn hình hiển thị

![win](https://github.com/user-attachments/assets/da317650-23be-47fd-9b1b-3768713d0702)

còn nếu để 1 trong 2 tình huống đã nêu trên xảy ra tức trúng đạn hoặc vật thể 3 lần, người chơi sẽ thua.

![image](https://github.com/user-attachments/assets/1562806b-e7be-4eeb-b69b-9bf0fbd83b6d)

Người chơi cũng có thể xem cách chơi tại mục "TUTORIAL" tại menu game khi mới bắt đầu chạy game

![image](https://github.com/user-attachments/assets/699b8b01-4cec-48ec-b69a-82453717aff4)

# 5. Source code

- Header: folder chung của các file header.
  
- SDL for VSC: thư viện SDL.
  
- Font: font chữ chung cho các ký tự trong game.
  
- Image: các hình ảnh dùng trong game.
  
- Sound: quản lý các audio chung, âm thanh cho các hành động tương ứng trong game.
  
- Các file .cpp:
  
  - Asteroid: tạo hiệu ứng chuyển động và xuất hiện ngẫu nhiên của các thiên thạch.
    
  - BaseObject: quản lý các đối tượng hình ảnh trong game (tải ảnh, xử lý ảnh, ...).
    
  - Bat: điều khiển, quản lý hành vi của dơi trong trò chơi như di chuyển, thả đạn, hiển thị hoạt ảnh.
    
  - Boss: điều khiển hành vi của trùm trong game, bao gồm di chuyển, thả trứng, hiển thị hoạt ảnh, và hiển thị thanh máu.
    
  - Bullet: quản lý đạn trong game, bao gồm việc tải hình ảnh tương ứng, xử lý di chuyển và trạng thái của viên đạn.
    
  - Chicken: quản lý các đối tượng gà trong trò chơi (việc di chuyển, bắn trứng, hiển thị hình ảnh gà...)
    
  - CommomFunction: xử lý va chạm và chuyển đổi hình ảnh.
    
  - Egg: các thuộc tính cơ bản của quả trứng, bao gồm tốc độ di chuyển và trạng thái di chuyển.
    
  - EggBreak: xử lý các hiệu ứng phá vỡ trứng trong trò chơi, thiết lập và hiển thị các khung hình của hiệu ứng.
    
  - Explosion: quản lý và hiển thị các hiệu ứng nổ trong trò chơi.
    
  - GameManagement: quản lý, điều khiển chung các hành động, đối tượng của game (hình ảnh, âm thanh, font chữ, asteroid, bat, boss, ...)
    
  - Gift: quản lý đối tượng quà tặng, lớp này xử lý việc di chuyển, hiển thị và tải hình ảnh của hộp quà tức chức năng chuyển đạn bắn trong game.
    
  - Main: khởi tạo và điều hành trò chơi.
    
  - MainObject: thiết lập vị trí, kích thước, và các thuộc tính, xử lý các hoạt động của đối tượng chính, bao gồm việc điều khiển, bắn đạn, quản lý cấp độ đạn, ...
    
  - Meat: đại diện cho loại đối tượng thịt di chuyển xuống từ trên xuống dưới màn hình, là cơ chế tính điểm của trò chơi khi người chơi ăn vật phẩm này.
    
  - Menu: quản lý giao diện menu trong trò chơi.
    
  - Shield: cung cấp khả năng hiển thị lá chắn.
    
  - Text: quản lý việc hiển thị văn bản trên màn hình.
    
# 6. Nguồn tham khảo
- Tham khảo cấu trúc game và cách thức làm theo game bắn máy bay trên kênh youtube của Phát Triển Phần Mềm 123AZ
  
  https://www.youtube.com/playlist?list=PLR7NDiX0QsfQQ2iFXsXepwH46wf3D4Y4C
  
- Tham khảo trên trang lazyfoo
  
  https://lazyfoo.net/tutorials/SDL/

- Hình ảnh, âm thanh lấy từ game gốc Chicken Invaders của InterAction.

