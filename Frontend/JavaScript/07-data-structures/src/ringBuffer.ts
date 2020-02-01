class BufferNode<T> {
  constructor(
    public value: T | undefined = undefined,
    public next: BufferNode<T> | undefined = undefined
  ) {}
}

export class RingBuffer<T> {
  private head: BufferNode<T> | undefined;
  private tail!: BufferNode<T>;
  private _size!: number;

  constructor(private readonly _capacity: number) {
    this.singleton();
  }

  get(index: number): T | undefined {
    if (index < 0 || index >= this.size) {
      return undefined;
    }
    if (!this.head) {
      throw new Error('Unexpected value: head of non-empty buffer ring is undefined');
    }

    let counter = 0;
    let res = this.head;

    while (counter++ !== index) {
      if (!res.next) {
        throw new Error('Unexpected value: inner node of non-empty buffer ring is undefined');
      }

      res = res.next;
    }

    return res.value;
  }

  push(element: T): void {
    if (this.isFull()) {
      if (this.shift() === undefined) {
        return;
      }
      this.push(element);
      this._size--;
    } else if (this.isEmpty()) {
      this.singleton(element);
    } else {
      this.tail.next = new BufferNode(element);
      this.tail = this.tail.next;
    }
    this._size++;
  }

  shift(): T | undefined {
    if (this.isEmpty()) {
      return undefined;
    }
    if (!this.head) {
      throw new Error('Unexpected value: head of non-empty buffer ring is undefined');
    }

    const res = this.head.value;
    this.head = this.head.next;
    this._size--;

    return res;
  }

  get size(): number {
    return this._size;
  }

  get capacity(): number {
    return this._capacity;
  }

  static concat(...buffers: RingBuffer<any>[]): RingBuffer<any> {
    let newCapacity = 0;
    buffers.map(buffer => (newCapacity += buffer.capacity));
    const newBuffer = new RingBuffer(newCapacity);

    buffers.map(buffer => {
      for (let i = 0; i < buffer.size; i++) {
        newBuffer.push(buffer.get(i));
      }
    });

    return newBuffer;
  }

  private singleton(element: T | undefined = undefined): void {
    const dummy = new BufferNode<T>(element);
    this.head = dummy;
    this.tail = dummy;
    this._size = 0;
  }

  private isEmpty(): boolean {
    return this.size === 0;
  }

  private isFull(): boolean {
    return this.size === this.capacity;
  }
}
