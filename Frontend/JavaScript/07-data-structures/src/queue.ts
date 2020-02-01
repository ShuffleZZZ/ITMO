class QueueNode<T> {
  constructor(
    public value: T | undefined = undefined,
    public next: QueueNode<T> | undefined = undefined
  ) {}
}

export class Queue<T> {
  private head: QueueNode<T> | undefined;
  private tail!: QueueNode<T>;
  private _size!: number;

  constructor() {
    this.singleton();
  }

  get(index: number): T | undefined {
    if (index < 0 || index >= this.size) {
      return undefined;
    }
    if (!this.head) {
      throw new Error('Unexpected value: head of non-empty queue is undefined');
    }

    let counter = this.size - 1;
    let res = this.head;

    while (counter-- !== index) {
      if (!res.next) {
        throw new Error('Unexpected value: inner node of non-empty queue is undefined');
      }

      res = res.next;
    }

    return res.value;
  }

  enqueue(element: T): void {
    if (this.isEmpty()) {
      this.singleton(element);
    } else {
      this.tail.next = new QueueNode(element);
      this.tail = this.tail.next;
    }
    this._size++;
  }

  dequeue(): T | undefined {
    if (this.isEmpty()) {
      return undefined;
    }
    if (!this.head) {
      throw new Error('Unexpected value: head of non-empty queue is undefined');
    }

    const res = this.head.value;
    this.head = this.head.next;
    this._size--;

    return res;
  }

  get size(): number {
    return this._size;
  }

  private singleton(element: T | undefined = undefined): void {
    const dummy = new QueueNode<T>(element);
    this.head = dummy;
    this.tail = dummy;
    this._size = 0;
  }

  private isEmpty(): boolean {
    return this.size === 0;
  }
}
