/**
 * @link https://emscripten.org/docs/api_reference/module.html
 * @param e
 */

// 会被插入在最前面的Module之后，覆盖原生的方法
Module.print = function(e) {
    console.log(`JS{overwrite print ${e}}`);
};