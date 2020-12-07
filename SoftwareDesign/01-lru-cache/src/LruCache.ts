import { AssertionError } from 'assert';

import { HashMap } from './hashMap';

export class LruCache<K, V> {
  private head?: Node<K, V>;
  private tail?: Node<K, V>;

  private values = new HashMap<K, Node<K, V>>();

  constructor(private maxEntries: number = Infinity) {
    assert(maxEntries > 0, `Expected positive number of max entries, found ${maxEntries}`);
  }

  get(key: K): V | undefined {
    assert(this.values.size <= this.maxEntries);

    const node = this.values.get(key);

    if (node === undefined) {
      return node;
    }

    this.removeNode(node);
    this.putNode(node);

    assert(this.values.size <= this.maxEntries);
    assertIsDefined(this.head);
    assertIsDefined(this.tail);
    assert(this.head.key === key);

    return node.value;
  }

  put(key: K, value: V): void {
    assert(this.values.size <= this.maxEntries);

    const oldSize = this.values.size;

    const newNode = new Node<K, V>(key, value);

    if (!this.values.has(key)) {
      this.putNode(newNode);
      if (this.values.size === this.maxEntries) {
        assertIsDefined(this.tail);

        this.values.remove(this.tail.key);
        this.removeNode(this.tail);
      }
    } else {
      const nodeValue = this.values.get(key);
      assert(nodeValue !== undefined);

      this.removeNode(nodeValue);
      this.putNode(newNode);

      assert(this.values.size === oldSize);
    }

    this.values.put(key, newNode);

    assert(this.values.size <= this.maxEntries);
    assertIsDefined(this.head);
    assertIsDefined(this.tail);
    assert(this.values.size >= oldSize);
    assert(this.head.key === key);
    assert(this.head.value === value);
  }

  get capacity(): number {
    return this.maxEntries;
  }

  get size(): number {
    return this.values.size;
  }

  private putNode(node: Node<K, V>): void {
    node.prev = this.head;
    node.next = undefined;

    if (this.head) {
      this.head.next = node;
    }
    this.head = node;

    this.tail = this.tail ?? node;
  }

  private removeNode(node: Node<K, V>): void {
    if (node.prev) {
      node.prev.next = node.next;
    }
    if (node.next) {
      node.next.prev = node.prev;
    }

    if (this.head === node) {
      this.head = node.prev;
    }
    if (this.tail === node) {
      this.tail = node.next;
    }
  }
}


class Node<K, V> {
  next?: Node<K, V>;
  prev?: Node<K, V>;

  constructor(readonly key: K, readonly value: V) {}
}


/* eslint-disable @typescript-eslint/no-explicit-any */
function assert(condition: any, msg?: string): asserts condition {
  if (!condition) {
    throw new AssertionError({ message: msg });
  }
}

// function assertIsString(val: any): asserts val is string {
//   if (typeof val !== 'string') {
//     throw new AssertionError({ message: `Asserted value is not a string`, actual: val });
//   }
// }

function assertIsDefined<T>(val: T): asserts val is NonNullable<T> {
  if (val === undefined || val === null) {
    throw new AssertionError({
      message: `Expected 'val' to be defined, but received ${val}`,
      actual: val
    });
  }
}
