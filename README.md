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