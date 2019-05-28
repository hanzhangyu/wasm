Module.onRuntimeInitialized = function () {
    const SIZE = 100;
    // region initialize
    const $result = document.getElementById('result');
    const INIT_ARRAY = shuffle(Array.from(Array(SIZE).keys()));
    // malloc -> run -> free
    const runCSort = (fn) => {
        const ptr = Module._malloc(4 * INIT_ARRAY.length);
        INIT_ARRAY.forEach((val, index) => Module.HEAP32[ptr / 4 + index] = val);
        fn(ptr, INIT_ARRAY.length);
        Module._free(ptr);
    };
    // endregion

    // region test
    const testTuple = [
        ['InsertionSort{JS}', function () {
            jsInsertionSort(INIT_ARRAY.slice());
        }],
        ['InsertionSort{C}', function () {
            runCSort(Module._insertionSortHandsome);
        }],
        ['ShellSort{JS}', function () {
            jsShellSort(INIT_ARRAY.slice());
        }],
        ['ShellSort{C}', function () {
            runCSort(Module._shellSort);
        }],
        ['QuickSort{JS}', function () {
            jsQuickSort(INIT_ARRAY.slice());
        }],
        ['QuickSort{C}', function () {
            runCSort(Module._quickSort);
        }],
        ['SelectionSort{JS}', function () {
            jsSelectionSort(INIT_ARRAY.slice());
        }],
        ['SelectionSort{C}', function () {
            runCSort(Module._selectionSort);
        }],
        ['HeapSort{JS}', function () {
            jsHeapSort(INIT_ARRAY.slice());
        }],
        ['HeapSort{C}', function () {
            runCSort(Module._heapSort);
        }]
    ];
    const result = [];
    (function runTuple(i) {
        if (i >= testTuple.length) {
            result.sort((a, b) => b.hz - a.hz);
            $result.innerHTML += '<hr>';
            $result.innerHTML += `<p>Fastest is ${result[0].name}</p>`;
            return;
        }
        const item = testTuple[i];
        new Benchmark.Suite().add(item[0], item[1]).on('cycle', function (event) {
            $result.innerHTML += `<p>${String(event.target)}</p>`;
            result.push(event.target);
        }).on('complete', function () {
            requestAnimationFrame(function () {
                runTuple(i + 1);
            });
        }).run();
    }(0));
    // endregion
};