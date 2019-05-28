## Reflection
TL;DR
1. 希尔排序在一些情况下能压住快排，看来调用栈也很耗时间
2. 通过维护一个二叉堆使得堆排与选择排序相差甚远也是很有意思
3. js下的桶排复制所带来的耗时超出预期，对比jsBucketShitSort（桶内有多个元素比较蛋疼）发现concat+splice在大数组下性能显著提升

## JS

size: 90000

```text
[correct for jsInsertionSort] success  27577ms
[correct for jsShellSort] success  19ms
[correct for jsQuickSort] success  20ms
[correct for jsSelectionSort] success  5380ms
[correct for jsHeapSort] success  21ms
[correct for jsMergeSort] success  5323ms
[correct for jsMergeInsertionSort] success  28291ms
[correct for jsBucketShitSort] success  1851ms
[correct for jsBucketSort] success  4825ms
[correct for jsRadixSort] success  49ms
```

## C

size: 90000

```text
[correct for insertionSort] success 7759 ms
[correct for insertionSortHandsome] success 6070 ms
[correct for shellSort] success 23 ms
[correct for quickSort] success 13 ms
[correct for selectionSort] success 13228 ms
[correct for heapSort] success 16 ms
[correct for mergeSort] success 17 ms
[correct for bucketSort] success 1 ms
[correct for radixSort] success 28 ms
```

## Benchmark

CPU: Intel(R) Xeon(R) CPU E3-1220 v5 @ 3.00GHz<br/>
Memory: 16.0 GB<br/>
Chrome: 73.0.3683.86 (Official Build) (64-bit)

```text
Benchmark Result:
InsertionSort{JS} x 34,676 ops/sec ±1.47% (57 runs sampled)
InsertionSort{C} x 251,592 ops/sec ±1.19% (60 runs sampled)
ShellSort{JS} x 530,968 ops/sec ±11.56% (50 runs sampled)
ShellSort{C} x 641,344 ops/sec ±1.38% (58 runs sampled)
QuickSort{JS} x 449,575 ops/sec ±1.50% (60 runs sampled)
QuickSort{C} x 481,563 ops/sec ±2.13% (57 runs sampled)
SelectionSort{JS} x 205,333 ops/sec ±0.73% (61 runs sampled)
SelectionSort{C} x 126,808 ops/sec ±0.60% (61 runs sampled)
HeapSort{JS} x 522,701 ops/sec ±1.44% (61 runs sampled)
HeapSort{C} x 338,166 ops/sec ±3.30% (59 runs sampled)
MergeSort{JS} x 64,316 ops/sec ±1.01% (60 runs sampled)
MergeSort{C} x 51,255 ops/sec ±2.24% (58 runs sampled)
BucketSort{JS} x 157,886 ops/sec ±1.32% (61 runs sampled)
BucketSort{C} x 1,221,359 ops/sec ±3.03% (57 runs sampled)
RadixSort{JS} x 173,568 ops/sec ±1.07% (61 runs sampled)
RadixSort{C} x 209,063 ops/sec ±1.45% (62 runs sampled)

Fastest is BucketSort{C}
```
