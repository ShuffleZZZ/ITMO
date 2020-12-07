const HASH_START_VALUE = 5381;
const HASH_SHIFT = 5;

type StorageItem<K, V> = { key: K; value: V };
type CollidedStorageItems<K, V> = StorageItem<K, V>[];

export class HashMap<K, V> {
  private storage!: CollidedStorageItems<K, V>[];
  private _size!: number;

  constructor(capacity?: number) {
    this.init(capacity);
  }

  get(key: K): V | undefined {
    const index = HashMap.getDJB2Hash(key) % this.storage.length;
    const value = this.storage[index]?.find(element => element['key'] === key);

    return value ? value['value'] : undefined;
  }

  has(key: K): boolean {
    return this.get(key) !== undefined;
  }

  put(key: K, value: V): void {
    const index = HashMap.getDJB2Hash(key) % this.storage.length;

    if (!this.storage[index]) {
      this.storage[index] = [];
    }

    if (this.has(key)) {
      this.remove(key);
    }

    this.storage[index].push({ key, value });
    this._size++;
  }

  remove(key: K): void {
    const index = HashMap.getDJB2Hash(key) % this.storage.length;
    const storageItem = this.storage[index];
    const value = storageItem?.find(element => element['key'] === key);
    if (value) {
      if (!storageItem) {
        return;
      }
      storageItem.splice(storageItem.indexOf(value), 1);
      this._size--;
    }
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

  private init(capacity = 197): void {
    this.storage = Array<CollidedStorageItems<K, V>>(capacity);
    this._size = 0;
  }

  /* eslint-disable @typescript-eslint/no-explicit-any */
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
