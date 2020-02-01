'use strict';

/**
 * Если вы решили сделать дополнительное задание и реализовали функцию importFromDsv,
 * то выставьте значение переменной isExtraTaskSolved в true.
 */
const isExtraTaskSolved = true;

/**
 * Телефонная книга
 */
const phoneBook = {};
/**
 * Добавление записи в телефонную книгу
 * @param {string} phone
 * @param {string} [name]
 * @param {string} [email]
 * @returns {boolean}
 */
function add(phone, name, email) {
  if (!isCorrectPhone(phone) || !isNonEmptyString(name) || phoneBook[phone]) {
    return false;
  }
  phoneBook[phone] = { name: name, email: email };

  return true;
}

/**
 * Проверяет является ли аргумент непустой строкой
 * @param {string} string входные данные
 * @returns {boolean} удовлетворяет ли аргумент условиям
 */
function isNonEmptyString(string) {
  return typeof string === 'string' && string.length;
}

/**
 * Проверяет является ли аргумент корректным форматом номера
 * @param {string} phone входные данные
 * @returns {boolean} удовлетворяет ли аргумент условиям
 */
function isCorrectPhone(phone) {
  return typeof phone === 'string' && /^\d{10}$/.test(phone);
}

/**
 * Обновление записи в телефонной книге
 * @param {string} phone
 * @param {string} [name]
 * @param {string} [email]
 * @returns {boolean}
 */
function update(phone, name, email) {
  if (!isCorrectPhone(phone) || !isNonEmptyString(name) || !phoneBook[phone]) {
    return false;
  }
  phoneBook[phone].name = name;
  phoneBook[phone].email = email;

  return true;
}

/**
 * Поиск записей по запросу в телефонной книге
 * @param {string} query
 * @returns {string[]}
 */
function find(query) {
  if (typeof query !== 'string') {
    throw new TypeError(`Expected string, not ${query}`);
  }

  return outputFormat(findStringEntries(query)).sort();
}

/**
 * Находит все контакты, в информации которых содержится данная строка
 * @param {string} query строка, вхождения которой требуются
 * @returns {Object[]} все объекты с вхождением строки
 */
function findStringEntries(query) {
  if (query === '*') {
    return phoneBook;
  }
  const res = [];
  if (!query.length) {
    return res;
  }
  Object.entries(phoneBook).forEach(function([phone, value]) {
    if (
      phone.includes(query) ||
      value.name.includes(query) ||
      (value.email && value.email.includes(query))
    ) {
      res[phone] = phoneBook[phone];
    }
  });

  return res;
}

/**
 * Получает массив объектов и возвращает их информацию в виде массива строк
 * @param {Object[]} array объекты конвертируемые в строки
 * @returns {string[]} подходящие контакты в формате строк
 */
function outputFormat(array) {
  const output = [];
  Object.entries(array).forEach(function([phone, value]) {
    if (value.email) {
      output.push(`${value.name}, ${phoneOutputFormat(phone)}, ${value.email}`);
    } else {
      output.push(`${value.name}, ${phoneOutputFormat(phone)}`);
    }
  });

  return output;
}

function phoneOutputFormat(phoneString) {
  return `+7 (${phoneString.slice(0, 3)}) ${phoneString.slice(3, 6)}-${phoneString.slice(
    6,
    8
  )}-${phoneString.slice(8, 10)}`; // subjectively prettier.
}

/**
 * Удаление записей по запросу из телефонной книги
 * @param {string} query
 * @returns {number}
 */
function findAndRemove(query) {
  if (!isNonEmptyString(query)) {
    return 0;
  }
  let removedCounter = 0;
  const toRemove = findStringEntries(query);
  Object.keys(toRemove).forEach(function(key) {
    if (phoneBook[key]) {
      ++removedCounter;
      delete phoneBook[key];
    }
  });

  return removedCounter;
}

/**
 * Импорт записей из dsv-формата
 * @param {string} dsv
 * @returns {number} Количество добавленных и обновленных записей
 */
function importFromDsv(dsv) {
  let correctCounter = 0;
  dsv.split('\n').forEach(string => {
    const [name, phone, email] = string.split(';');
    if (update(phone, name, email) || add(phone, name, email)) {
      correctCounter++;
    }
  });

  return correctCounter;
}

module.exports = {
  add,
  update,
  find,
  findAndRemove,
  importFromDsv,

  isExtraTaskSolved
};
