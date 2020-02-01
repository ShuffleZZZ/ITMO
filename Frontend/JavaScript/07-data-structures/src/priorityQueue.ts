enum Priority {
  Low = 1,
  Medium,
  High
}

class QueueNode<T> {
  constructor(
    public value: T | undefined = undefined,
    public priority: Priority = Priority.Low,
    public next: QueueNode<T> | undefined = undefined
  ) {}
}

export class PriorityQueue<T> {
  private head: QueueNode<T> | undefined;
  private tail!: QueueNode<T>;
  private _size!: number;

  constructor() {
    this.singleton();
  }

  enqueue(element: T, priority: Priority): void {
    if (this.isEmpty()) {
      this.singleton(element, priority);
    } else {
      this.tail.next = new QueueNode(element, priority);
      this.tail = this.tail.next;
    }
    this._size++;
  }

  dequeue(): T | undefined {
    if (this.isEmpty()) {
      return undefined;
    }

    const res = this.getDequeuePrev();
    const isNotPrev = res === this.head && res.priority >= (res.next?.priority || 0);
    let resValue: T | undefined;

    if (isNotPrev) {
      if (!this.head) {
        throw new Error('Unexpected value: head of non-empty queue is undefined');
      }

      this.head = this.head.next;
      resValue = res.value;
    } else {
      if (res.next === this.tail) {
        this.tail = res;
      }
      if (!res.next) {
        throw new Error('Unexpected value: next node of node before the dequeued one is undefined');
      }

      resValue = res.next.value;
      res.next = res.next.next;
    }

    this._size--;

    return resValue;
  }

  get size(): number {
    return this._size;
  }

  private singleton(element: T | undefined = undefined, priority: Priority = Priority.Low): void {
    const dummy = new QueueNode<T>(element, priority);
    this.head = dummy;
    this.tail = dummy;
    this._size = 0;
  }

  private getDequeuePrev(): QueueNode<T> {
    if (!this.head) {
      throw new Error('Unexpected value: head of non-empty queue is undefined');
    }

    let curNode: QueueNode<T> | undefined = this.head;
    let prevNode: QueueNode<T> | undefined;
    let mediumNode: QueueNode<T> | undefined;
    let lowNode: QueueNode<T> | undefined;

    do {
      if (!curNode) {
        throw new Error('Unexpected behavior: got undefined node during dequeue node search');
      }

      if (curNode.priority === Priority.High) {
        return prevNode || curNode;
      }

      if (!mediumNode && curNode.priority === Priority.Medium) {
        mediumNode = prevNode ? prevNode : curNode;
      } else if (!lowNode && curNode.priority === Priority.Low) {
        lowNode = prevNode ? prevNode : curNode;
      }

      prevNode = curNode;
    } while ((curNode = curNode.next));

    if (mediumNode) {
      return mediumNode;
    }

    if (!lowNode) {
      throw new Error("Unexpected behavior: couldn't find node of any priority in non-empty queue");
    }

    return lowNode;
  }

  private isEmpty(): boolean {
    return this.size === 0;
  }
}
