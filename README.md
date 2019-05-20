# Test For Webassembly

## Prepare
### emscripten

I tried to build it in my Win10 and WSL, and it worked.

But when I use `emcc hello.c`, it seems to be deadlocked.

So use docker `trzeci/emscripten`.

## Usage
run in wsl
```bash
./make -h # print the help
./make <folder> # build folder
```

## Links
- http://note.youdao.com/noteshare?id=5a463b5081e2b5b856eb723c08dfca0f&sub=F46B2556DD6A46B9A51124A7BB3F4A6D
- https://github.com/3dgen/cppwasm-book
- https://github.com/chai2010/awesome-wasm-zh