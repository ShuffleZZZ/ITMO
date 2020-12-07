/* eslint-disable @typescript-eslint/no-explicit-any */
import { HashMap } from '../src';

describe('HashMap', () => {
  it('HashMap.put', () => {
    const hashMap = new (HashMap as any)();
    const object = {};

    expect(hashMap.size).toBe(0);

    hashMap.put(1, 1);
    hashMap.put('1', 2);
    hashMap.put(object, 3);

    expect(hashMap.size).toBe(3);
  });

  it('HashMap stores unique keys', () => {
    const hashMap = new (HashMap as any)();

    expect(hashMap.size).toBe(0);

    hashMap.put(1, 1);
    hashMap.put(1, 2);

    expect(hashMap.get(1)).toBe(2);

    hashMap.put('1', '3');
    hashMap.put('1', '4');

    expect(hashMap.get('1')).toBe('4');
  });

  it('HashMap.get', () => {
    const hashMap = new (HashMap as any)();
    const object = {};

    hashMap.put(1, 1);
    hashMap.put('1', 2);
    hashMap.put(object, 3);

    expect(hashMap.get(1)).toBe(1);
    expect(hashMap.get('1')).toBe(2);
    expect(hashMap.get(object)).toBe(3);
  });

  it('HashMap.remove', () => {
    const hashMap = new (HashMap as any)();
    const object = {};

    hashMap.put(1, 1);
    hashMap.put('1', 2);
    hashMap.put(object, 3);

    expect(hashMap.size).toBe(3);

    hashMap.remove(1);
    expect(hashMap.size).toBe(2);
    hashMap.remove(object);
    expect(hashMap.size).toBe(1);
    hashMap.remove('1');
    expect(hashMap.size).toBe(0);
  });

  it('HashMap.clear', () => {
    const hashMap = new (HashMap as any)();
    const object = {};

    hashMap.put(1, 1);
    hashMap.put('1', 2);
    hashMap.put(object, 3);

    expect(hashMap.size).toBe(3);

    hashMap.clear();

    expect(hashMap.size).toBe(0);
  });
});
