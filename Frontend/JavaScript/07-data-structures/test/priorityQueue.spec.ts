/* eslint-disable @typescript-eslint/no-explicit-any */

import { PriorityQueue } from '../src';

describe('PriorityQueue', () => {
  it('позволяет добавлять элементы', () => {
    const priorityQueue = new (PriorityQueue as any)();

    expect(priorityQueue.size).toBe(0);

    priorityQueue.enqueue(1, 3);
    priorityQueue.enqueue(2, 1);
    priorityQueue.enqueue(3, 2);

    expect(priorityQueue.size).toBe(3);
  });

  it('позволяет доставать элементы', () => {
    const priorityQueue = new (PriorityQueue as any)();

    priorityQueue.enqueue(1, 3);
    priorityQueue.enqueue(2, 1);
    priorityQueue.enqueue(3, 2);

    expect(priorityQueue.size).toBe(3);

    expect(priorityQueue.dequeue()).toBe(1);
    expect(priorityQueue.dequeue()).toBe(3);
    expect(priorityQueue.dequeue()).toBe(2);

    expect(priorityQueue.size).toBe(0);
  });
});
