#include <stdio.h>
#include <string.h>
#include "../global.h"


int main() {
    printf("C{enter main}\n");
    // @formatter:off
    // region eval js in c by macro
    // 宏定义的js片段，会被嵌入wasm.js里面，（类似#define）
    EM_ASM( // 会被写入var ASM_CONSTS = [function(){...}]中
        var a='Emscripten';
        console.log('hello, ' + a)
    );
    int num = 1;
    num = EM_ASM_({return $0 + $1;}, num, 2); // 与IIFE很像，可以传入外部变量int
    printf("C{EM_ASM_: %d}\n", num);
    double db_num = EM_ASM_DOUBLE({return Array.from(arguments).reduce((sum, a) => sum + a, 0);}, 1.1121, 2.0);
    printf("C{EM_ASM_DOUBLE: %lf}\n", db_num);
    // num = EM_ASM_INT_V(return 42);
    // db_num = EM_ASM_DOUBLE_V(return 3.14159);
    // endregion

    // region eval js in c by eval
    // C的函数变为native函数，而这些eval的会由C中的调用者将指针传回JS，然后JS解析出string，最后调用eval
    emscripten_run_script("\
    function log(s) {\
        console.log(`C{JS{${s}}}`);\
    }\
    log('emscripten_run_script');\
    ");
    num = emscripten_run_script_int("1"); // 见wasm生成JS定义的_emscripten_run_script_int
    printf("C{emscripten_run_script_int: %d}\n", num);
    char *str = emscripten_run_script_string("'hello'");
    printf("C{emscripten_run_script_string: %s}\n", str);
    // endregion
    // @formatter:on

    // region timer
    void msg_loop();
    emscripten_set_main_loop(msg_loop, 1, 1);
    // endregion
    printf("C{exit main}\n");
    return 0;
}

// region 函数声明
EM_PORT_API(float) js_add(float a, float b);

EM_PORT_API(void) js_console_log_int(int param);
// endregion

// region 调用JS中的函数
EM_PORT_API(void) printfLike(int param) {
    js_console_log_int(param); // 不使用不会打包
    printf("hello printf:");
    printf("%d\n", param);
}

EM_PORT_API(float) add(float a, float b) {
    float i = js_add(a, b);
    return a + b + i;
}
// endregion

// region 地址访问
int g_int = -42;
double g_double = 3.1415926; // TODO 待验证，如果使用double会在64视图上面读写。
EM_PORT_API(int*)get_int_ptr() {
    printf("C{g_int_ptr:%d}\n", (int) &g_int);
    return &g_int; // 返回在HEAP中的位置
}

EM_PORT_API(double*)get_double_ptr() {
    printf("C{g_double_ptr:%d}\n", (int) &g_double);
    return &g_double;
}

EM_PORT_API(void) print_data() { // 获取被js修改的内存数据
    printf("C{g_int:%d}\n", g_int);
    printf("C{g_double:%lf}\n", g_double);
}
// endregion

// region 操作在JS中分配的内存
EM_PORT_API(int) sum_use_ptr(int *aryPtr, int count) {
    int total = 0;
    for (int i = 0; i < count; i++) {
        total += aryPtr[i];
    }
    return total;
}
// endregion

// region string
EM_PORT_API(const char*)get_string() {
    static const char str[] = "Hello, world! 你好，世界！";
    printf("C{%ld length: ", strlen(str));
    for (int i = 0; i < strlen(str); i++) {
        printf("%c", str[i]); // 连续输出是会合并字符
    }
    printf("}\n");
    return str;
}

EM_PORT_API(const char*)set_string(char *str) {
    printf("C{set_string: %s}\n", str);
    return str;
}
// endregion

// region timer
void msg_loop() {
    static int count = 0;
    printf("count:%d\n", count);
    count++;
}

EM_PORT_API(void) pause_main_loop() {
    emscripten_pause_main_loop();
    printf("C{pause_main_loop}\n");
}

EM_PORT_API(void) resume_main_loop() {
    emscripten_resume_main_loop();
    printf("C{resume_main_loop}\n");
}

EM_PORT_API(void) cancel_main_loop() {
    emscripten_cancel_main_loop();
    printf("C{cancel_main_loop}\n");
}
//