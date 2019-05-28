const swap = typeof window === 'undefined' ? require('../helper').swap : swap;

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

function jsSelectionSort(ary) {
    const len = ary.length;
    for (let i = 0; i < len - 1; i++) {
        let minIndex = i;
        for (let j = i + 1; j < len; j++) {
            if (ary[minIndex] > ary[j]) {
                minIndex = j;
            }
        }
        swap(ary, i, minIndex);
    }
}

function heapFallAdjust(ary, parent, len) {
    let childIndex = parent * 2 + 1; // (parent + 1) * 2 - 1，设左节点为需要比较的节点
    const cur = ary[parent];
    while (childIndex < len) {
        if (childIndex + 1 < len && ary[childIndex + 1] > ary[childIndex]) { // 如果右节点存在且更大，将右节点设置为带比较的节点
            childIndex++;
        }
        if (cur >= ary[childIndex]) break; // 大于最大值
        ary[parent] = ary[childIndex]; // 标记下移
        parent = childIndex;
        childIndex = childIndex * 2 + 1;
    }
    ary[parent] = cur;
}

function jsHeapSort(ary) {
    const len = ary.length;
    for (let i = ((len - 1) / 2) | 0; i >= 0; i--) {
        heapFallAdjust(ary, i, len)
    }
    for (let i = len - 1; i > 0; i--) {
        swap(ary, 0, i);
        heapFallAdjust(ary, 0, i);
    }
}

function jsMergeSort(ary) {
    const len = ary.length;
    for (let i = 2; i / 2 <= len; i *= 2) { // 进行二叉树的自底向上遍历，i取值对子序列元素个数2, 4, 8
        const half = i / 2;
        for (let j = 0; j < len; j += i) {
            // 直接不停的取两部分的最小值进行空间换时间O(m + n)
            const left = ary.slice(j, j + half);
            const right = ary.slice(j + half, Math.min(j + i, len));
            let x = j;
            while (left.length && right.length) {
                ary[x++] = left[0] <= right[0] ? left.shift() : right.shift(); // 注意保持稳定性
            }
            while (left.length) {
                ary[x++] = left.shift();
            }
            while (right.length) {
                ary[x++] = right.shift();
            }
        }
    }
}

function jsMergeInsertionSort(ary) {
    const len = ary.length;
    for (let i = 2; i / 2 <= len; i *= 2) {
        const half = i / 2;
        for (let j = 0; j < len; j += i) {
            // 前半部分已有序，后半部分使用插排，时间换空间O(m * n)。
            for (let x = j + half; x < j + i && x < len; x++) {
                let cur = ary[x];
                let curIndex = x;
                while (cur < ary[curIndex - 1] && curIndex > j) {
                    ary[curIndex] = ary[curIndex - 1];
                    curIndex--;
                }
                ary[curIndex] = cur;
            }
        }
    }
}

const highWatermark = 1000;

// 感觉除非想分布式不然用处不大
function jsBucketShitSort(ary) {
    const len = ary.length;
    const bucketNum = ary < highWatermark ? len : highWatermark;
    const buckets = [];
    let min, max = min = ary[0];
    for (let i = 0; i < len; i++) {
        ary[i] < min && (min = ary[i]);
        ary[i] > max && (max = ary[i]);
    }
    let offset = (max - min + 1) / bucketNum;
    for (let i = 0; i < len; i++) {
        const index = ((ary[i] - min) / offset) | 0;
        if (buckets[index]) {
            buckets[index].push(ary[i]);
        } else {
            buckets[index] = [ary[i]];
        }
    }
    for (let i = 0; i < bucketNum; i++) {
        jsQuickSort(buckets[i]);
        ary.concat(buckets[i]);
    }
    ary.splice(0, len);
}

function jsBucketSort(ary) {
    const len = ary.length;
    let min, max = min = ary[0];
    let i = 0;
    for (; i < len; i++) {
        ary[i] < min && (min = ary[i]);
        ary[i] > max && (max = ary[i]);
    }
    const bucketLen = max - min + 1;
    const buckets = Array(bucketLen).fill(0);
    for (i = 0; i < len; i++) {
        buckets[i - min]++;
    }
    i = 0;
    while (buckets.length) {
        const num = buckets.shift();
        for (let j = 0; j < num; j++) {
            ary[i + j] = i + min;
        }
        i += num;
    }
}

function radixSort(ary) {
    const len = ary.length;
    const radix = 10;
    const buckets = [];
    let max = ary[0];
    let i = 0;
    for (; i < len; i++) {
        ary[i] > max && (max = ary[i]);
    }
    const maxRadix = 10 ** String(max).length;
    let prevRadix = 1;
    while (prevRadix < maxRadix) {
        const curRadix = prevRadix * radix;
        for (i = 0; i < ary.length; i++) {
            const curIndex = (ary[i] % curRadix / prevRadix) | 0;
            if (!buckets[curIndex]) buckets[curIndex] = [];
            buckets[curIndex].push(ary[i]);
        }
        i = 0;
        while (buckets.length) {
            const bucket = buckets.shift();
            ary.splice(i, bucket.length, ...bucket);
            i += bucket.length;
        }
        prevRadix = curRadix;
    }
}

if (typeof window === 'undefined') {
    module.exports = {
        jsInsertionSort,
        jsShellSort,
        jsQuickSort,
        jsSelectionSort,
        jsHeapSort,
        jsMergeSort,
        jsMergeInsertionSort,
        jsBucketShitSort,
        jsBucketSort,
        radixSort,
    };
}
