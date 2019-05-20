/**
 * @file C调用该js函数，mergeInto之后的对象会被原样输出至载入WASM的js文件中
 */

let temp = 0;
const js_console_log_int = function(param) { // 初始化无法访问js环境变量
    // console.log(temp); // 无法访问
    return consoleLogInt(param); // 运行时可以
};
mergeInto(LibraryManager.library, {
    js_add: function (a, b) {
        console.log("js_add");
        return a + b;
    },
    js_console_log_int,
    // temp, // 挂载无效
});