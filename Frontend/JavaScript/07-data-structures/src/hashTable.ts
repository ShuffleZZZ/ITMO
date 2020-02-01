const HASH_START_VALUE = 5381;
const HASH_SHIFT = 5;

const TABLE_CAPACITY = 197;

const INNER_KEY = 0;
const INNER_VALUE = 1;

type Key = number | boolean | string | object;
type StorageItem<T> = [Key, T];
type CollidedStorageItems<T> = StorageItem<T>[];

export class HashTable<T> {
  private storage!: CollidedStorageItems<T>[];
  private _size!: number;

  constructor() {
    this.init();
  }

  get(key: Key): T | undefined {
    const index = HashTable.getDJB2Hash(key) % this.storage.length;
    const value = this.storage[index]?.find(element => element[INNER_KEY] === key);

    return value ? value[INNER_VALUE] : undefined;
  }

  put(key: Key, value: T): void {
    const index = HashTable.getDJB2Hash(key) % this.storage.length;

    if (!this.storage[index]) {
      this.storage[index] = [];
    }

    this.storage[index].push([key, value]);
    this._size++;
  }

  clear(): void {
    if (this.isEmpty()) {
      return;
    }

    this.init();
  }

  get size(): number {
    return this._size;
  }

  private init(): void {
    this.storage = Array<CollidedStorageItems<T>>(TABLE_CAPACITY);
    this._size = 0;
  }

  private static getDJB2Hash(object: any): number {
    if (!object) {
      return 0;
    }

    let hashSum = HASH_START_VALUE;

    if (typeof object === 'number') {
      return object;
    } else if (typeof object === 'boolean') {
      return 1;
    } else if (typeof object === 'string') {
      for (let i = 0; i < object.length; i++) {
        hashSum = (hashSum << HASH_SHIFT) + hashSum + object.charCodeAt(i);
      }
    } else {
      Object.entries(object).forEach(([key, value]) => {
        hashSum = (hashSum << HASH_SHIFT) + hashSum + this.getDJB2Hash(key);
        hashSum = (hashSum << HASH_SHIFT) + hashSum + this.getDJB2Hash(value);
      });
    }

    return hashSum;
  }

  private isEmpty(): boolean {
    return this.size === 0;
  }
}
