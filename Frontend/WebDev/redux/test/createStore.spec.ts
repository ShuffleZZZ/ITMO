import { AnyAction, AnyState, Reducer, Store, StoreCreator, TEnhancerTuple } from '../src/types';
import { actions, reducers } from '../src/helpers';
import { createStore } from '../src/redux';

describe('createStore', () => {
  it('exposes the public API', () => {
    const store = createStore(reducers.default);

    const methods = Object.keys(store);

    expect(methods).toContain('subscribe');
    expect(methods).toContain('dispatch');
    expect(methods).toContain('getState');
  });

  it('throws if reducer is not a function', () => {
    expect(() => createStore(('test' as unknown) as Reducer)).toThrow();

    expect(() => createStore(({} as unknown) as Reducer)).toThrow();

    expect(() => createStore(() => ({}))).not.toThrow();
  });

  it('passes the initial state', () => {
    const store = createStore(reducers.default, [
      {
        id: 1,
        text: 'Hello'
      }
    ]);
    expect(store.getState()).toEqual([
      {
        id: 1,
        text: 'Hello'
      }
    ]);
  });

  it('applies the reducer to the previous state', () => {
    const store = createStore(reducers.counter);
    expect(store.getState()).toEqual({ count: 0 });

    store.dispatch({ type: 'UNKNOWN' });
    expect(store.getState()).toEqual({ count: 0 });

    store.dispatch({ type: 'INCREASE' });
    expect(store.getState()).toEqual({ count: 1 });
  });

  it('applies the reducer to the initial state', () => {
    const store = createStore(reducers.counter, { count: 42 });
    expect(store.getState()).toEqual({ count: 42 });

    store.dispatch({ type: 'UNKNOW ' });
    expect(store.getState()).toEqual({ count: 42 });

    store.dispatch({ type: 'INCREASE' });
    expect(store.getState()).toEqual({ count: 43 });
  });

  it('supports multiple subscriptions', () => {
    const store = createStore(reducers.counter);
    const listenerA = jest.fn();
    const listenerB = jest.fn();

    let unsubscribeA = store.subscribe(listenerA);
    store.dispatch(actions.unknown());
    expect(listenerA.mock.calls).toHaveLength(1);
    expect(listenerB.mock.calls).toHaveLength(0);

    store.dispatch(actions.unknown());
    expect(listenerA.mock.calls).toHaveLength(2);
    expect(listenerB.mock.calls).toHaveLength(0);

    const unsubscribeB = store.subscribe(listenerB);
    expect(listenerA.mock.calls).toHaveLength(2);
    expect(listenerB.mock.calls).toHaveLength(0);

    store.dispatch(actions.unknown());
    expect(listenerA.mock.calls).toHaveLength(3);
    expect(listenerB.mock.calls).toHaveLength(1);

    unsubscribeA();
    expect(listenerA.mock.calls).toHaveLength(3);
    expect(listenerB.mock.calls).toHaveLength(1);

    store.dispatch(actions.unknown());
    expect(listenerA.mock.calls).toHaveLength(3);
    expect(listenerB.mock.calls).toHaveLength(2);

    unsubscribeB();
    expect(listenerA.mock.calls).toHaveLength(3);
    expect(listenerB.mock.calls).toHaveLength(2);

    store.dispatch(actions.unknown());
    expect(listenerA.mock.calls).toHaveLength(3);
    expect(listenerB.mock.calls).toHaveLength(2);

    unsubscribeA = store.subscribe(listenerA);
    expect(listenerA.mock.calls).toHaveLength(3);
    expect(listenerB.mock.calls).toHaveLength(2);

    store.dispatch(actions.unknown());
    expect(listenerA.mock.calls).toHaveLength(4);
    expect(listenerB.mock.calls).toHaveLength(2);
  });

  it('only removes listener once when unsubscribe is called', () => {
    const store = createStore(reducers.counter);
    const listenerA = jest.fn();
    const listenerB = jest.fn();

    const unsubscribeA = store.subscribe(listenerA);
    store.subscribe(listenerB);

    unsubscribeA();
    unsubscribeA();

    store.dispatch(actions.unknown());
    expect(listenerA.mock.calls).toHaveLength(0);
    expect(listenerB.mock.calls).toHaveLength(1);
  });

  it('only removes relevant listener when unsubscribe is called', () => {
    const store = createStore(reducers.counter);
    const listener = jest.fn();

    store.subscribe(listener);
    const unsubscribeSecond = store.subscribe(listener);

    unsubscribeSecond();
    unsubscribeSecond();

    store.dispatch(actions.unknown());
    expect(listener.mock.calls).toHaveLength(1);
  });

  it('supports removing a subscription within a subscription', () => {
    const store = createStore(reducers.counter);
    const listenerA = jest.fn();
    const listenerB = jest.fn();
    const listenerC = jest.fn();

    store.subscribe(listenerA);
    const unSubB = store.subscribe(() => {
      listenerB();
      unSubB();
    });
    store.subscribe(listenerC);

    store.dispatch(actions.unknown());
    store.dispatch(actions.unknown());

    expect(listenerA.mock.calls).toHaveLength(2);
    expect(listenerB.mock.calls).toHaveLength(1);
    expect(listenerC.mock.calls).toHaveLength(2);
  });

  it('notifies all subscribers about current dispatch regardless if any of them gets unsubscribed in the process', () => {
    const store = createStore(reducers.counter);

    type TUnsubscriber = () => void;

    const unsubscribeHandles: TUnsubscriber[] = [];
    const doUnsubscribeAll = (): void =>
      unsubscribeHandles.forEach((unsubscribe: TUnsubscriber) => unsubscribe());

    const listener1 = jest.fn();
    const listener2 = jest.fn();
    const listener3 = jest.fn();

    unsubscribeHandles.push(store.subscribe(() => listener1()));
    unsubscribeHandles.push(
      store.subscribe(() => {
        listener2();
        doUnsubscribeAll();
      })
    );
    unsubscribeHandles.push(store.subscribe(() => listener3()));

    store.dispatch(actions.unknown());
    expect(listener1.mock.calls).toHaveLength(1);
    expect(listener2.mock.calls).toHaveLength(1);
    expect(listener3.mock.calls).toHaveLength(1);

    store.dispatch(actions.unknown());
    expect(listener1.mock.calls).toHaveLength(1);
    expect(listener2.mock.calls).toHaveLength(1);
    expect(listener3.mock.calls).toHaveLength(1);
  });

  it('notifies only subscribers active at the moment of current dispatch', () => {
    const store = createStore(reducers.counter);

    const listener1 = jest.fn();
    const listener2 = jest.fn();
    const listener3 = jest.fn();

    let listener3Added = false;
    const maybeAddThirdListener = (): void => {
      if (!listener3Added) {
        listener3Added = true;
        store.subscribe(() => listener3());
      }
    };

    store.subscribe(() => listener1());
    store.subscribe(() => {
      listener2();
      maybeAddThirdListener();
    });

    store.dispatch(actions.unknown());
    expect(listener1.mock.calls).toHaveLength(1);
    expect(listener2.mock.calls).toHaveLength(1);
    expect(listener3.mock.calls).toHaveLength(0);

    store.dispatch(actions.unknown());
    expect(listener1.mock.calls).toHaveLength(2);
    expect(listener2.mock.calls).toHaveLength(2);
    expect(listener3.mock.calls).toHaveLength(1);
  });

  it('provides an up-to-date state when a subscriber is notified', () => {
    return new Promise(done => {
      const store = createStore(reducers.counter);
      store.subscribe(() => {
        expect(store.getState()).toEqual({ count: 1 });

        done();
      });

      store.dispatch(actions.increase());
    });
  });

  it('recovers from an error within a reducer', () => {
    const store = createStore(reducers.error);
    expect(() => store.dispatch(actions.error())).toThrow();

    expect(() => store.dispatch(actions.unknown())).not.toThrow();
  });

  it('throws if action type is missing', () => {
    const store = createStore(reducers.counter);

    expect(() => store.dispatch({} as AnyAction)).toThrow(
      /Actions may not have an undefined "type" property/
    );
  });

  it('throws if action type is undefined', () => {
    const store = createStore(reducers.counter);
    expect(() => store.dispatch({ type: undefined })).toThrow(
      /Actions may not have an undefined "type" property/
    );
  });

  it('does not throw if action type is falsy', () => {
    const store = createStore(reducers.counter);
    expect(() => store.dispatch({ type: false })).not.toThrow();
    expect(() => store.dispatch({ type: 0 })).not.toThrow();
    expect(() => store.dispatch({ type: null })).not.toThrow();
    expect(() => store.dispatch({ type: '' })).not.toThrow();
  });

  it('accepts enhancer as the third argument', () => {
    const initialState = { count: 0 };

    const spyEnhancer = (vanillaCreateStore: StoreCreator) => (...args: TEnhancerTuple): Store => {
      expect(args[0]).toBe(reducers.counter);
      expect(args[1]).toBe(initialState);
      expect(args).toHaveLength(2);

      const vanillaStore = vanillaCreateStore(args[0], args[1]);

      return {
        ...vanillaStore,
        dispatch: jest.fn(vanillaStore.dispatch)
      };
    };

    const store = createStore(reducers.counter, initialState, spyEnhancer as any);

    const action = actions.increase();

    store.dispatch(action);
    expect(store.dispatch).toHaveBeenCalledWith(action);
    expect(store.getState()).toEqual({ count: 1 });
  });

  it('accepts enhancer as the second argument if initial state is missing', () => {
    const spyEnhancer = (vanillaCreateStore: StoreCreator) => (...args: TEnhancerTuple): Store => {
      expect(args[0]).toBe(reducers.counter);
      expect(args[1]).toBeUndefined();
      expect(args).toHaveLength(2);
      const vanillaStore = vanillaCreateStore(args[0], args[1]);

      return {
        ...vanillaStore,
        dispatch: jest.fn(vanillaStore.dispatch)
      };
    };

    const store = createStore(reducers.counter, spyEnhancer as any);

    const action = actions.increase();

    store.dispatch(action);
    expect(store.dispatch).toHaveBeenCalledWith(action);
    expect(store.getState()).toEqual({ count: 1 });
  });

  it('throws if enhancer is neither undefined nor a function', () => {
    expect(() => createStore(reducers.counter, undefined, {} as AnyState)).toThrow();

    expect(() => createStore(reducers.counter, undefined, [] as AnyState)).toThrow();

    expect(() => createStore(reducers.counter, undefined, null as AnyState)).toThrow();

    expect(() => createStore(reducers.counter, undefined, false as AnyState)).toThrow();

    expect(() => createStore(reducers.counter, undefined, undefined)).not.toThrow();

    expect(() => createStore(reducers.counter, undefined, (x: any) => x)).not.toThrow();

    expect(() => createStore(reducers.counter, (x: any) => x)).not.toThrow();

    expect(() => createStore(reducers.counter, { count: 0 })).not.toThrow();

    expect(() => createStore(reducers.counter)).not.toThrow();
  });

  it('throws if listener is not a function', () => {
    const store = createStore(reducers.counter);

    expect(() => store.subscribe(('' as unknown) as () => void)).toThrow();

    expect(() => store.subscribe((null as unknown) as () => void)).toThrow();

    expect(() => store.subscribe((undefined as unknown) as () => void)).toThrow();
  });
});
