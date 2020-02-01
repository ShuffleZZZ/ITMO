/* eslint-disable @typescript-eslint/no-explicit-any */

import { HashTable } from '../src';

describe('HashTable', () => {
  it('позволяет добавлять элементы', () => {
    const hashTable = new (HashTable as any)();
    const object = {};

    expect(hashTable.size).toBe(0);

    hashTable.put(1, 1);
    hashTable.put('1', 2);
    hashTable.put(object, 3);

    expect(hashTable.size).toBe(3);
  });

  it('позволяет получать элемент по ключу', () => {
    const hashTable = new (HashTable as any)();
    const object = {};

    hashTable.put(1, 1);
    hashTable.put('1', 2);
    hashTable.put(object, 3);

    expect(hashTable.get(1)).toBe(1);
    expect(hashTable.get('1')).toBe(2);
    expect(hashTable.get(object)).toBe(3);
  });

  it('можно очистить', () => {
    const hashTable = new (HashTable as any)();
    const object = {};

    hashTable.put(1, 1);
    hashTable.put('1', 2);
    hashTable.put(object, 3);

    expect(hashTable.size).toBe(3);

    hashTable.clear();

    expect(hashTable.size).toBe(0);
  });
});
