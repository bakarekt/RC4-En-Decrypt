# RC4 – Mã hoá/Giải mã (C++ header-only, build bằng g++)

**Cảnh báo bảo mật**: RC4 đã lỗi thời và **không an toàn** cho hệ thống thực tế. Repo này phục vụ mục đích học thuật.

## Cấu trúc dự án
```
.
├─ include/
│  └─ rc4/
│     ├─ rc4.h
│     ├─ ksa.h
│     ├─ prga.h
│     └─ hex.h
├─ encrypt/
│  └─ main.cpp
├─ decrypt/
│  └─ main.cpp
└─ README.md
```

## Yêu cầu (chọn **một** trong hai)

### Cách A) MSYS2 + MinGW-w64 (khuyên dùng)
1. Cài MSYS2 (qua Microsoft Store/Winget).
2. Mở **MSYS2 UCRT64**.
3. Cập nhật và cài toolchain:
   ```bash
   pacman -Syu        # có thể phải mở lại terminal và chạy lại
   pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
   ```
4. Kiểm tra:
   ```bash
   g++ --version
   ```

### Cách B) WinLibs (GCC standalone, không cần MSYS2)
1. Tải gói WinLibs (GCC + MinGW-w64) bản 64-bit dạng `.zip`, giải nén, ví dụ: `C:\winlibs\`.
2. Thêm `C:\winlibs\mingw64\bin` vào **PATH** (System Properties → Environment Variables).
3. Mở PowerShell:
   ```powershell
   g++ --version
   ```

> Trên Linux/macOS, chỉ cần `g++` 7+ là đủ. Câu lệnh build tương tự (đổi dấu `\` thành `/` nếu cần).

---

## Build (biên dịch bằng g++)
Đứng tại thư mục gốc dự án:

- **Trong MSYS2 UCRT64:**
  ```bash
  cd /path/to/your/project
  g++ -std=c++17 -O2 -Iinclude encrypt/main.cpp -o encrypt.exe
  g++ -std=c++17 -O2 -Iinclude decrypt/main.cpp -o decrypt.exe
  ```

- **Trong PowerShell (WinLibs):**
  ```powershell
  cd <path>\to\your\project
  g++ -std=c++17 -O2 -Iinclude encrypt\main.cpp -o encrypt.exe
  g++ -std=c++17 -O2 -Iinclude decrypt\main.cpp -o decrypt.exe
  ```

Kết quả tạo ra 2 file: `encrypt.exe` và `decrypt.exe` ngay trong thư mục dự án.

---

## Cách chạy

- **Mã hoá** (có thể bỏ tham số để dùng mặc định):
  ```bash
  ./encrypt.exe
  ./encrypt.exe "HUST-2025" "Hanoi University of Science and Technology"
  ```

- **Giải mã** (bắt buộc truyền **key** và **cipher hex**):
  ```bash
  ./decrypt.exe "<key>" "<cipher_hex>"
  ```

> **Lưu ý:** Plaintext có dấu cách phải đặt trong **ngoặc kép**.  
> Chương trình dùng **UTF-8** cho chuỗi đầu vào.

---

## Test vectors

### TV1 – Bài yêu cầu
- **Key**: `HUST-2025`  
- **Plaintext**: `Hanoi University of Science and Technology`  
- **Cipher (hex)**:  
  `DB6D5EFDDB1320FC5D1D3631AAC70FCE217778E11C2C577DD07369E04F2D3C8120008BF83FE7DAE77096`

Chạy kiểm tra:
```bash
./encrypt.exe "HUST-2025" "Hanoi University of Science and Technology"
# -> in ra DB6D5EFD...

./decrypt.exe "HUST-2025" "DB6D5EFDDB1320FC5D1D3631AAC70FCE217778E11C2C577DD07369E04F2D3C8120008BF83FE7DAE77096"
# -> Hanoi University of Science and Technology
```

### TV2 – Kinh điển
- **Key**: `Key`  
- **Plaintext**: `Plaintext`  
- **Cipher (hex)**: `BBF316E8D940AF0AD3`

```bash
./encrypt.exe "Key" "Plaintext"        # -> BBF316E8D940AF0AD3
./decrypt.exe "Key" "BBF316E8D940AF0AD3"  # -> Plaintext
```

### TV3 – Wikipedia
- **Key**: `Wiki`  
- **Plaintext**: `pedia`  
- **Cipher (hex)**: `1021BF0420`

```bash
./encrypt.exe "Wiki" "pedia"        # -> 1021BF0420
./decrypt.exe "Wiki" "1021BF0420"   # -> pedia
```

## Khắc phục sự cố
- `g++: command not found` → Cài MSYS2 toolchain hoặc WinLibs và kiểm tra PATH.  
- `No such file or directory` khi biên dịch → kiểm tra lại **đường dẫn** `-Iinclude` và có đủ file trong `include/rc4/`.  
- Decrypt sai kết quả → đảm bảo **đưa vào đúng chuỗi hex** (không có khoảng trắng/thừa ký tự).
