function TEST(title, fn) {
    let msg = `[${title}]`;
    let color;
    const start = Date.now();
    try {
        fn();
        msg += ' success ';
        color = '\x1b[36m%s\x1b[0m';
    } catch (err) {
        msg += ` failed: ${err.message} `;
        color = '\x1b[31m';
    } finally {
        const end = Date.now();
        msg += ` ${end - start}ms`;
        console.log(color, msg);
    }
}

function shuffle(ary) {
    let m = ary.length, t, i;
    while (m) {
        i = Math.floor(Math.random() * m--);
        t = ary[m];
        ary[m] = ary[i];
        ary[i] = t;
    }
    return ary;
}

function swap(ary, i, j) {
    if (i === j) return;
    let temp = ary[i];
    ary[i] = ary[j];
    ary[j] = temp;
}


if (typeof window === 'undefined') {
    module.exports = {
        shuffle,
        swap,
        TEST,
    };
}