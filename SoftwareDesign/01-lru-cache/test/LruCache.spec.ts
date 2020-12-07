/* eslint-disable @typescript-eslint/no-explicit-any */
import { LruCache } from '../src';

describe('LruCache', () => {
  const capacity = 2;

  it('LruCache.put, LruCache.size, LruCache.capacity', () => {
    const cache = new (LruCache as any)(capacity);
    const object = {};

    expect(cache.capacity).toBe(2);
    expect(cache.size).toBe(0);

    cache.put(1, 1);
    expect(cache.size).toBe(1);

    cache.put('1', 2);
    expect(cache.size).toBe(2);

    cache.put(object, 3);
    expect(cache.size).toBe(2);

    expect(cache.capacity).toBe(2);
    expect(cache.size).toBe(2);
  });

  it('LruCache.get', () => {
    const cache = new (LruCache as any)(capacity);
    const object = {};

    cache.put(1, 1);
    cache.put('1', 2);
    cache.put(object, 3);

    expect(cache.get(1)).toBeUndefined();
    expect(cache.get('1')).toBe(2);
    expect(cache.get(object)).toBe(3);
  });

  it('LruCache.get on repetitive keys', () => {
    const cache = new (LruCache as any)(capacity);

    cache.put(1, 1);
    expect(cache.get(1)).toBe(1);

    cache.put('1', 2);
    expect(cache.get('1')).toBe(2);

    cache.put(1, 2);
    expect(cache.get(1)).toBe(2);
    expect(cache.get('1')).toBe(2);

    cache.put(1, 3);
    expect(cache.get(1)).toBe(3);
    expect(cache.get('1')).toBe(2);

    cache.put('1', 3);
    expect(cache.get(1)).toBe(3);
    expect(cache.get('1')).toBe(3);
  });
});
