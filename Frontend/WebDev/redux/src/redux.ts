import { AnyState, Reducer, Store, Unsubscribe } from './types';

const createStore = (reducer: Reducer, initialState?: AnyState, enhancer?: any): Store => {
  if (typeof reducer !== 'function') {
    throw new Error('Reducer is not a function');
  }

  if (typeof enhancer !== 'function' && typeof enhancer !== 'undefined') {
    throw new Error('Enhancer is neither a function nor undefined');
  }

  if (typeof enhancer === 'undefined' && typeof initialState === 'function') {
    enhancer = initialState;
    initialState = undefined;
  }

  if (enhancer) {
    return enhancer(createStore)(reducer, initialState);
  }

  const callbacks = new Map();
  let state: AnyState = initialState || reducer(initialState, { type: undefined });

  return {
    dispatch: (action: AnyState): void => {
      if (typeof action.type === 'undefined') {
        throw new Error('Actions may not have an undefined "type" property');
      }

      state = reducer(state, action);
      [...callbacks.values()].forEach(item => item());
    },
    getState: (): AnyState => state,
    subscribe: (listener: () => void): Unsubscribe => {
      if (typeof listener !== 'function') {
        throw new Error('Listener is not a function');
      }

      const ind = callbacks.size;
      callbacks.set(ind, listener);

      return (): boolean => callbacks.delete(ind);
    }
  };
};

const applyMiddleware = (...middleware: any[]) => (
  makeStore: (reducer: Reducer, state?: AnyState) => Store
) => (reducer: Reducer, state?: AnyState) => {
  const store = makeStore(reducer, state);
  let dispatch = (_: any): any => {
    throw new Error('Dispatching during middleware setup');
  };

  const innerStore = {
    getState: store.getState,
    dispatch: (action: any): any => dispatch(action)
  };

  dispatch = middleware.map(m => m(innerStore)).reduce((acc, cur) => (m: any) => acc(cur(m)))(
    store.dispatch
  );

  return { ...store, dispatch };
};

export { createStore, applyMiddleware };
