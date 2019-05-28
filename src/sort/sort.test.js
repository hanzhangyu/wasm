const assert = require('assert');
const {TEST, shuffle} = require('../helper');
const Sort = require('./sort');

const SIZE = 90000;
const assertAsc = (ary) => assert.ok(ary.every((val, index) => index === 0 || val > ary[index - 1]));

const CORRECT_TEST = [
    'jsInsertionSort',
    'jsShellSort',
    'jsQuickSort',
    'jsSelectionSort',
    'jsHeapSort',
    'jsMergeSort',
    'jsMergeInsertionSort',
    'jsBucketShitSort',
    'jsBucketSort',
    'jsRadixSort',
];

const TEMPLATE_ARRAY = shuffle(Array.from(Array(SIZE).keys()));
CORRECT_TEST.forEach((name) => {
    const ary = TEMPLATE_ARRAY.slice();
    TEST(`correct for ${name}`, () => {
        Sort[name](ary);
        assertAsc(ary);
    });
});