function swap(ary, i, j) {
    let temp = ary[i];
    ary[i] = ary[j];
    ary[j] = temp;
}

function jsInsertionSort(ary) {
    const len = ary.length;
    for (let i = 1; i < len; i++) {
        if (ary[i] < ary[i - 1]) {
            const cur = ary[i];
            let j = i;
            while (cur < ary[j - 1] && j >= 1) {
                ary[j] = ary[--j];
            }
            ary[j] = cur;
        }
    }
}

function jsShellSort(ary) {
    const len = ary.length;
    let interval = 1;
    while (interval < len / 3) { // 让其每次分裂出两个子序列，最后一个子序列值可能偏大
        interval = interval * 3 + 1;
    }
    while (interval >= 1) {
        for (let i = interval; i < len; i++) { // 以interval为间隔插排，相当于多个子序列同时在进行插排（{0, interval, ...}, {1, interval+1, ...}, ...）
            const cur = ary[i];
            if (cur < ary[i - interval]) {
                let j = i;
                for (; j >= interval && cur < ary[j - interval]; j -= interval) {
                    ary[j] = ary[j - interval];
                }
                ary[j] = cur;
            }
        }
        interval = (interval - 1) / 3;
    }
}

function jsQuickSort(ary, start = 0, end = ary.length - 1) {
    if (start >= end) return;
    let low = start;
    let high = end;
    const pivotPoint = ary[low];
    while (low < high) {
        while (ary[high] >= pivotPoint && high > low) {
            high--;
        }
        ary[low] = ary[high];
        while (ary[low] <= pivotPoint && high > low) {
            low++;
        }
        ary[high] = ary[low]
    }
    ary[low] = pivotPoint;
    jsQuickSort(ary, start, low - 1);
    jsQuickSort(ary, low + 1, end);
}

// var a = [7, 2, 6, 8, 9, 1, 4, 3, 5];
// var a = Array.from(Array(100).keys()).reverse();
// jsShellSort(a);
// console.log(a);