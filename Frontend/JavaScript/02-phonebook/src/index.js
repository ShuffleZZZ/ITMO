'use strict';

const phonebook = require('./phonebook');

// Эти записи добавятся, вернется `true`
console.info(phonebook.add('5554440044', 'Григорий', 'grisha@example.com'));
console.info(phonebook.add('5552220022', 'Борис', 'boris@example.com'));
console.info(phonebook.add('5551110011', 'Алекс'));
console.info(phonebook.add('5553330033', 'Валерий', 'valera@example.com'));

// Эти записи не добавятся, вернется `false`
console.info(phonebook.add('3330033', 'Неизвестный', 'unknown@example.com'));
console.info(phonebook.add('5551110011', 'Алексей'));
console.info(phonebook.add('5555550055'));

// Обновление ранее добавленных записей
phonebook.update('5551110011', 'Алексей', 'alex@example.com');
phonebook.update('5553330033', 'Валерий');

// В следующих примерах вернутся все записи
console.info(phonebook.find('*'));
console.info(phonebook.find('555'));
// В обоих случаях вывод будет следующий
// [
//   'Алексей, +7 (555) 111-00-11, alex@example.com',
//   'Борис, +7 (555) 222-00-22, boris@example.com',
//   'Валерий, +7 (555) 333-00-33',
//   'Григорий, +7 (555) 444-00-44, grisha@example.com'
// ]

// Удаление записей, содержащих '@', вернется `3`
console.info(phonebook.findAndRemove('@'));

if (phonebook.isExtraTaskSolved) {
  const dsv = [
    'Борис;5552220022;boris@example.com',
    'Григорий;5554440044;grisha@example.com',
    'Алексей;5551110011;alex@example.com',
    'Валерий;5553330033;valera@example.com',
    'Неизвестный;3330033;unknown@example.com'
  ].join('\n');

  // Импорт записей из dsv, вернется `4`
  console.info(phonebook.importFromDsv(dsv));
  console.info(phonebook.find('*'));
}
