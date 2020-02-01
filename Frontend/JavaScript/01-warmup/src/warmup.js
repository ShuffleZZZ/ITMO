'use strict';

/**
 * Складывает два целых числа
 * @param {Number} a Первое целое
 * @param {Number} b Второе целое
 * @throws {TypeError} Когда в аргументы переданы не числа
 * @returns {Number} Сумма аргументов
 */
function abProblem(a, b) {
  if (typeof a !== 'number' || typeof b !== 'number') {
    throw new TypeError(`Expected numbers, not ${a} and ${b}`);
  }
  return a + b;
}

/**
 * Определяет век по году
 * @param {Number} year Год, целое положительное число
 * @throws {TypeError} Когда в качестве года передано не число
 * @throws {RangeError} Когда год – отрицательное значение
 * @returns {Number} Век, полученный из года
 */
function centuryByYearProblem(year) {
  if (typeof year !== 'number') {
    throw new TypeError(`Expected number, not ${year}`);
  }
  if (!Number.isInteger(year) || year <= 0) {
    throw new RangeError(`Expected positive integer value, not ${year}`);
  }
  return Math.ceil(year / 100);
}

/**
 * Переводит цвет из формата HEX в формат RGB
 * @param {String} hexColor Цвет в формате HEX, например, '#FFFFFF'
 * @throws {TypeError} Когда цвет передан не строкой
 * @throws {RangeError} Когда значения цвета выходят за пределы допустимых
 * @returns {String} Цвет в формате RGB, например, '(255, 255, 255)'
 */
function colorsProblem(hexColor) {
  if (typeof hexColor !== 'string') {
    throw new TypeError(`Expected string value, not ${hexColor}`);
  }
  let curIndex = 1;
  let step;
  if (hexColor.length === 4) {
    step = 1;
  } else if (hexColor.length === 7) {
    step = 2;
  } else {
    throw new RangeError(`Expected correct HEX color string, not ${hexColor}`);
  }
  const colors = [0, 0, 0];
  for (let i = 0; i < colors.length; ++i) {
    colors[i] = parseColor(hexColor, curIndex, step);
    curIndex += step;
  }
  if (!isCorrectRange(colors) || hexColor[0] !== '#') {
    throw new RangeError(`Expected correct HEX color string, not ${hexColor}`);
  }
  return `(${colors[0]}, ${colors[1]}, ${colors[2]})`;
}

/**
 * Переводит шестнадцатиричное число цвета в десятичное
 * @param {String} string изначальная строка
 * @param {number} ind левая граница вхождения значения в строку
 * @param {number} step колличество необходимых символов
 * @throws {RangeError} Когда значения цвета выходят за пределы допустимых
 * @returns {number} десятичное значение цвета
 */
function parseColor(string, ind, step) {
  const bufString = string.substring(ind, ind + step);
  if (step === 1) {
    if (/^[0-9a-fA-F]$/.test(bufString)) {
      return parseInt(`0x${bufString}${bufString}`, 16);
    } else {
      throw new RangeError(`Expected correct HEX color string, not ${string}`);
    }
  }
  if (/^[0-9a-fA-F]{2}$/.test(bufString)) {
    return parseInt(`0x${bufString}`, 16);
  } else {
    throw new RangeError(`Expected correct HEX color string, not ${string}`);
  }
}

/**
 * Проверяет удовлетворяют ли значения переданного массива цветовым(от 0 до 255)
 * @param {Array} array цвета для проверки
 * @returns {boolean} правильные ли значения цветов
 */
function isCorrectRange(array) {
  for (let i = 0; i < array.length; ++i) {
    if (array[i] < 0 || array[i] > 255) {
      return false;
    }
  }
  return true;
}

/**
 * Находит n-ое число Фибоначчи
 * @param {Number} n Положение числа в ряде Фибоначчи
 * @throws {TypeError} Когда в качестве положения в ряде передано не число
 * @throws {RangeError} Когда положение в ряде не является целым положительным числом
 * @returns {Number} Число Фибоначчи, находящееся на n-ой позиции
 */
function fibonacciProblem(n) {
  if (typeof n !== 'number') {
    throw new TypeError(`Expected number, not ${n}`);
  }
  if (!Number.isInteger(n) || n <= 0) {
    throw new RangeError(`Expected positive integer value, not ${n}`);
  }
  const start = [1, 1];
  for (let i = 0; i < n - 2; ++i) {
    const next = start[0] + start[1];
    start[0] = start[1];
    start[1] = next;
  }
  return start[1];
}

/**
 * Транспонирует матрицу
 * @param {(Any[])[]} matrix Матрица размерности MxN
 * @throws {TypeError} Когда в функцию передаётся не двумерный массив
 * @returns {(Any[])[]} Транспонированная матрица размера NxM
 */
function matrixProblem(matrix) {
  if (matrix.length === 0 || matrix[0].length === 0) {
    throw new TypeError(`Expected 2d non-empty array`);
  }
  if (!Array.isArray(matrix)) {
    throw new TypeError(`Expected array, not ${matrix}`);
  }
  for (let i = 0; i < matrix.length; ++i) {
    if (!Array.isArray(matrix[i]) || matrix[i].length !== matrix[0].length) {
      throw new TypeError(`Expected 2D-array, found ${matrix[i]} at ${i}`);
    }
  }
  const TransMatrix = Array(matrix[0].length);
  for (let j = 0; j < matrix[0].length; ++j) {
    TransMatrix[j] = Array(matrix.length);
    for (let i = 0; i < matrix.length; ++i) {
      TransMatrix[j][i] = matrix[i][j];
    }
  }
  return TransMatrix;
}

/**
 * Переводит число в другую систему счисления
 * @param {Number} n Число для перевода в другую систему счисления
 * @param {Number} targetNs Система счисления, в которую нужно перевести (Число от 2 до 36)
 * @throws {TypeError} Когда переданы аргументы некорректного типа
 * @throws {RangeError} Когда система счисления выходит за пределы значений [2, 36]
 * @returns {String} Число n в системе счисления targetNs
 */
function numberSystemProblem(n, targetNs) {
  if (typeof n !== 'number' || typeof targetNs !== 'number') {
    throw new TypeError(`Expected 2 numbers, not ${n} and ${targetNs}`);
  }
  if (!Number.isInteger(targetNs) || targetNs < 2 || targetNs > 36) {
    throw new RangeError(`Expected number system in [2, 36] range, not ${targetNs}`);
  }
  return n.toString(targetNs);
}

/**
 * Проверяет соответствие телефонного номера формату
 * @param {String} phoneNumber Номер телефона в формате '8–800–xxx–xx–xx'
 * @throws {TypeError} Когда в качестве аргумента передаётся не строка
 * @returns {Boolean} Если соответствует формату, то true, а иначе false
 */
function phoneProblem(phoneNumber) {
  if (typeof phoneNumber !== 'string') {
    throw new TypeError(`Expected string, not ${phoneNumber}`);
  }
  return /^8-800-\d{3}(-\d{2}){2}$/.test(phoneNumber);
}

/**
 * Определяет количество улыбающихся смайликов в строке
 * @param {String} text Строка в которой производится поиск
 * @throws {TypeError} Когда в качестве аргумента передаётся не строка
 * @returns {Number} Количество улыбающихся смайликов в строке
 */
function smilesProblem(text) {
  if (typeof text !== 'string') {
    throw new TypeError(`Expected string, not ${text}`);
  }
  const left = text.match(/:-\)/g) || [];
  const right = text.match(/\(-:/g) || [];
  return left.length + right.length;
}

/**
 * Определяет победителя в игре "Крестики-нолики"
 * Тестами гарантируются корректные аргументы.
 * @param {(('x' | 'o')[])[]} field Игровое поле 3x3 завершённой игры
 * @returns {'x' | 'o' | 'draw'} Результат игры
 */
function ticTacToeProblem(field) {
  for (let i = 0; i < field.length; ++i) {
    const row = field[i][0];
    let isWinningRow = true;
    for (let j = 1; j < field.length; ++j) {
      if (field[i][j] !== row) {
        isWinningRow = false;
      }
    }
    if (isWinningRow) {
      return row;
    }
  }
  for (let i = 0; i < field.length; ++i) {
    const row = field[0][i];
    let isWinningColumn = true;
    for (let j = 1; j < field.length; ++j) {
      if (field[j][i] !== row) {
        isWinningColumn = false;
      }
    }
    if (isWinningColumn) {
      return row;
    }
  }
  let isWinningDiagonal = true;
  for (let i = 1; i < field.length; ++i) {
    if (field[i][i] !== field[0][0]) {
      isWinningDiagonal = false;
    }
  }
  if (isWinningDiagonal) {
    return field[0][0];
  }
  let isWinningRevDiagonal = true;
  for (let i = 1; i < field.length; ++i) {
    if (field[field.length - 1 - i][i] !== field[field.length - 1][0]) {
      isWinningRevDiagonal = false;
    }
  }
  if (isWinningRevDiagonal) {
    return field[field.length - 1][0];
  }
  return 'draw';
}

module.exports = {
  abProblem,
  centuryByYearProblem,
  colorsProblem,
  fibonacciProblem,
  matrixProblem,
  numberSystemProblem,
  phoneProblem,
  smilesProblem,
  ticTacToeProblem
};
