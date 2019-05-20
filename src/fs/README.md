## Usage

```bash
# 打包出index.data（多个文件时会设置每个文件的起止位置），并在wasm.js中的loadPackage引入
./make fs --preload-file fs/data
# 将文件编码为HEAP8视图（多个文件多个数组）
./make fs --embed-file fs/data
````