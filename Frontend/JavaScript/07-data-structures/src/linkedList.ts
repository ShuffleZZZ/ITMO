class ListNode<T> {
  constructor(
    public value: T | undefined = undefined,
    public next: ListNode<T> | undefined = undefined,
    public prev: ListNode<T> | undefined = undefined
  ) {}
}

export class LinkedList<T> {
  private head: ListNode<T> | undefined;
  private tail: ListNode<T> | undefined;
  private pointer!: ListNode<T>;
  private _size!: number;

  constructor() {
    this.singleton();
  }

  get(index: number): T | undefined {
    if (index < 0 || index >= this.size) {
      return undefined;
    }

    let counter: number;
    let res: ListNode<T>;

    if (index < this.size / 2) {
      if (!this.head) {
        throw new Error('Unexpected value: head of non-empty list is undefined');
      }

      counter = 0;
      res = this.head;

      while (counter++ !== index) {
        if (!res.next) {
          throw new Error('Unexpected value: inner node is undefined');
        }

        res = res.next;
      }
    } else {
      if (!this.tail) {
        throw new Error('Unexpected value: tail of non-empty list is undefined');
      }

      counter = this.size - 1;
      res = this.tail;

      while (counter-- !== index) {
        if (!res.prev) {
          throw new Error('Unexpected value: inner node is undefined');
        }

        res = res.prev;
      }
    }

    return res.value;
  }

  push(element: T): void {
    if (this.isEmpty()) {
      this.singleton(element);
    } else {
      if (!this.tail) {
        throw new Error('Unexpected value: tail of non-empty list is undefined');
      }

      this.tail.next = new ListNode(element);
      this.tail.next.prev = this.tail;
      this.tail = this.tail.next;
    }
    this._size++;
  }

  unshift(element: T): void {
    if (this.isEmpty()) {
      this.singleton(element);
    } else {
      if (!this.head) {
        throw new Error('Unexpected value: head of non-empty list is undefined');
      }

      this.head.prev = new ListNode(element);
      this.head.prev.next = this.head;
      this.head = this.head.prev;
    }
    this._size++;
  }

  pop(): T | undefined {
    if (this.isEmpty()) {
      return undefined;
    }
    if (!this.tail) {
      throw new Error('Unexpected value: tail of non-empty list is undefined');
    }

    const res = this.tail.value;
    if (this.pointer === this.tail) {
      this.prev();
    }
    this.tail = this.tail.prev;
    this._size--;

    return res;
  }

  shift(): T | undefined {
    if (this.isEmpty()) {
      return undefined;
    }
    if (!this.head) {
      throw new Error('Unexpected value: head of non-empty list is undefined');
    }

    const res = this.head.value;
    if (this.pointer === this.head) {
      this.next();
    }
    this.head = this.head.next;
    this._size--;

    return res;
  }

  prev(): T | undefined {
    if (this.isEmpty()) {
      return undefined;
    }

    const res = this.pointer.value;
    if (this.pointer !== this.head) {
      if (!this.pointer.prev) {
        throw new Error("Unexpected value: inner node's value is undefined");
      }

      this.pointer = this.pointer.prev;
    }

    return res;
  }

  next(): T | undefined {
    if (this.isEmpty()) {
      return undefined;
    }

    const res = this.pointer.value;
    if (this.pointer !== this.tail) {
      if (!this.pointer.next) {
        throw new Error("Unexpected value: inner node's value is undefined");
      }

      this.pointer = this.pointer.next;
    }

    return res;
  }

  get size(): number {
    return this._size;
  }

  private singleton(element: T | undefined = undefined): void {
    const dummy = new ListNode<T>(element);
    this.head = dummy;
    this.tail = dummy;
    this.pointer = dummy;
    this._size = 0;
  }

  private isEmpty(): boolean {
    return this.size === 0;
  }
}
