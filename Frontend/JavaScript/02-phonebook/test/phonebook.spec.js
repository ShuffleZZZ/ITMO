'use strict';

describe('phonebook', () => {
  let phonebook = require('../src/phonebook');

  afterEach(() => {
    jest.resetModules();
    phonebook = require('../src/phonebook');
  });

  it('функция add должна добавлять записи', () => {
    expect(phonebook.add('5554440044', 'Григорий', 'grisha@example.com')).toBe(true);
    expect(phonebook.add('5552220022', 'Борис', 'boris@example.com')).toBe(true);
    expect(phonebook.add('5551110011', 'Алекс')).toBe(true);
    expect(phonebook.add('5553330033', 'Валерий', 'valera@example.com')).toBe(true);
  });

  it('функция add не должна добавлять неправильные записи', () => {
    expect(phonebook.add('3330033', 'Неизвестный', 'unknown@example.com')).toBe(false);
    expect(phonebook.add('abc5556660055', 'Николай', 'kolya@example.com')).toBe(false);
    expect(phonebook.add('5556660066abc', 'Герман', 'gera@example.com')).toBe(false);
    expect(phonebook.add('5555550055')).toBe(false);
  });

  it('функция update должна обновлять существующие записи', () => {
    phonebook.add('5551110011', 'Алекс');
    phonebook.add('5553330033', 'Валера');

    expect(phonebook.update('5551110011', 'Алексей', 'alex@example.com')).toBe(true);
    expect(phonebook.update('5553330033', 'Валерий')).toBe(true);
  });

  it('функция find должна найти соответствующие записи по запросу "222"', () => {
    phonebook.add('5551110011', 'Алексей', 'alex@example.com');
    phonebook.add('5552220022', 'Борис', 'boris@example.com');
    phonebook.add('5553330033', 'Валерий');
    phonebook.add('5552220044', 'Григорий', 'grisha@example.com');

    expect(phonebook.find('222')).toStrictEqual([
      'Борис, +7 (555) 222-00-22, boris@example.com',
      'Григорий, +7 (555) 222-00-44, grisha@example.com'
    ]);
  });

  it('функция find должна отдать все записи по запросу "*"', () => {
    phonebook.add('5551110011', 'Алексей', 'alex@example.com');
    phonebook.add('5552220022', 'Борис', 'boris@example.com');
    phonebook.add('5553330033', 'Валерий');
    phonebook.add('5554440044', 'Григорий', 'grisha@example.com');

    expect(phonebook.find('*')).toStrictEqual([
      'Алексей, +7 (555) 111-00-11, alex@example.com',
      'Борис, +7 (555) 222-00-22, boris@example.com',
      'Валерий, +7 (555) 333-00-33',
      'Григорий, +7 (555) 444-00-44, grisha@example.com'
    ]);
  });

  it('функция findAndRemove должна удалять контакты из телефонной книги', () => {
    phonebook.add('5551110011', 'Алексей', 'alex@example.com');
    phonebook.add('5552220022', 'Борис', 'boris@example.com');
    phonebook.add('5553330033', 'Валерий');
    phonebook.add('5552220044', 'Григорий', 'grisha@example.com');

    expect(phonebook.findAndRemove('@')).toBe(3);
  });

  if (phonebook.isExtraTaskSolved) {
    it('функция importFromDsv должна добавить контакты из DSV', () => {
      const dsv = [
        'Борис;5552220022;boris@example.com',
        'Григорий;5554440044;grisha@example.com',
        'Алексей;5551110011;alex@example.com',
        'Валерий;5553330033;valera@example.com',
        'Неизвестный;3330033;unknown@example.com'
      ].join('\n');

      expect(phonebook.importFromDsv(dsv)).toBe(4);
    });
  }
});
