/* eslint-disable @typescript-eslint/no-explicit-any */

import { RingBuffer } from '../src';

describe('RingBuffer', () => {
  it('позволяет добавлять элементы', () => {
    const ringBuffer = new (RingBuffer as any)(3);
    expect(ringBuffer.capacity).toBe(3);

    expect(ringBuffer.size).toBe(0);

    ringBuffer.push(1);
    ringBuffer.push(2);

    expect(ringBuffer.size).toBe(2);
  });

  it('позволяет получать элемент по индексу', () => {
    const ringBuffer = new (RingBuffer as any)(3);

    ringBuffer.push(1);
    ringBuffer.push(2);

    expect(ringBuffer.get(1)).toBe(2);
  });

  it('должен переполниться, если больше элементов, чем размер буфера', () => {
    const ringBuffer = new (RingBuffer as any)(3);

    ringBuffer.push(1);
    ringBuffer.push(2);
    ringBuffer.push(3);

    expect(ringBuffer.size).toBe(3);

    ringBuffer.push(4);

    expect(ringBuffer.size).toBe(3);
  });

  it('позволяет доставать элементы', () => {
    const ringBuffer = new (RingBuffer as any)(3);

    ringBuffer.push(1);
    ringBuffer.push(2);
    ringBuffer.push(3);
    ringBuffer.push(4);

    expect(ringBuffer.size).toBe(3);

    expect(ringBuffer.shift()).toBe(2);
    expect(ringBuffer.shift()).toBe(3);

    expect(ringBuffer.size).toBe(1);
  });
});
