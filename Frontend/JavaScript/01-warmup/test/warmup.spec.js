'use strict';

const assert = require('assert');

const {
  abProblem,
  centuryByYearProblem,
  colorsProblem,
  fibonacciProblem,
  matrixProblem,
  numberSystemProblem,
  phoneProblem,
  smilesProblem,
  ticTacToeProblem
} = require('../src/warmup');

describe('A+B problem', () => {
  it('Должна вернуть `2`', () => {
    assert.strictEqual(abProblem(1, 1), 2);
  });
});

describe('Century by year problem', () => {
  it('Должна вернуть `21`', () => {
    assert.strictEqual(centuryByYearProblem(2018), 21);
  });
});

describe('Colors problem', function() {
  it('Должна вернуть (255, 255, 255)', function() {
    assert.strictEqual(colorsProblem('#FFFFFF'), '(255, 255, 255)');
  });
});

describe('Fibonacci problem', () => {
  it('Для n=1 должна вернуть `1`', () => {
    assert.strictEqual(fibonacciProblem(1), 1);
  });
});

describe('Matrix problem', () => {
  it('Должна транспонировать квадратную матрицу 3x3', () => {
    // prettier-ignore
    assert.deepStrictEqual(matrixProblem(
    [
      [1, 2, 3],
      [4, 5, 6],
      [7, 8, 9]
    ]),
    [
      [1, 4, 7],
      [2, 5, 8],
      [3, 6, 9]
    ]);
  });
});

describe('Number System Problem', () => {
  it('Должна вернуть "101"', () => {
    assert.strictEqual(numberSystemProblem(5, 2), '101');
  });
});

describe('Phone problem', () => {
  it('Для "8-800-333-51-73" должна вернуть `true`', () => {
    assert.strictEqual(phoneProblem('8-800-333-51-73'), true);
  });
});

describe('Smiles problem', () => {
  it('Должна вернуть `1`', () => {
    assert.strictEqual(smilesProblem(':-)'), 1);
  });
});

describe('Tic-tac-toe problem', () => {
  it('Должна вернуть "x"', () => {
    // prettier-ignore
    assert.strictEqual(ticTacToeProblem([
      ['x', 'x', 'x'],
      ['o', 'o', 'x'],
      ['o', 'x', 'o']
    ]), 'x');
  });
});
