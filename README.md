# RC4 – Mã hoá/Giải mã (C++ Header-only)

> **Lưu ý bảo mật:** RC4 đã lỗi thời và **không an toàn** cho hệ thống thực tế. Bài này phục vụ mục đích học thuật.

## Build

### CMake (khuyến nghị)
```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
# sinh ra 2 binary: ./encrypt và ./decrypt (hoặc .\Release\... trên Windows)
