import { actions, reducers, thunk } from '../src/helpers';
import { applyMiddleware, createStore } from '../src/redux';
import { Action } from '../src/types';

describe('applyMiddleware', () => {
  it('warns when dispatching during middleware setup', () => {
    function dispatchingMiddleware(store: any) {
      store.dispatch(actions.increase());

      return (next: any) => (action: Action) => next(action);
    }

    expect(() => applyMiddleware(dispatchingMiddleware)(createStore)(reducers.counter)).toThrow();
  });

  it('wraps dispatch method with middleware once', () => {
    function test(spyOnMethods: any) {
      return (methods: any[]) => {
        spyOnMethods(methods);

        return (next: any) => (action: Action) => next(action);
      };
    }

    const spy = jest.fn();

    const store = applyMiddleware(test(spy) as any)(createStore)(reducers.counter);

    store.dispatch(actions.increase());
    store.dispatch(actions.increase());

    expect(spy.mock.calls).toHaveLength(1);

    expect(spy.mock.calls[0][0]).toHaveProperty('getState');
    expect(spy.mock.calls[0][0]).toHaveProperty('dispatch');

    expect(store.getState()).toEqual({ count: 2 });
  });

  it('works with thunk middleware', () => {
    return new Promise(done => {
      const store = applyMiddleware(thunk)(createStore)(reducers.counter);

      store.dispatch(actions.increase());
      store.dispatch(actions.increase());
      expect(store.getState()).toEqual({ count: 2 });

      // the typing for redux-thunk is super complex, so we will use an "as unknown" hack
      const dispatchedValue = store.dispatch(actions.asyncIncrease() as any) as Promise<void>;

      return dispatchedValue.then(() => {
        expect(store.getState()).toEqual({ count: 3 });
        done();
      });
    });
  });

  it('passes recursive dispatches through the middleware chain', () => {
    return new Promise(done => {
      function test(spyOnMethods: any) {
        return () => (next: any) => (action: any) => {
          spyOnMethods(action);

          return next(action) as () => any;
        };
      }

      const spy = jest.fn();

      const storeCreator = applyMiddleware(test(spy), thunk)(createStore);

      const store = storeCreator(reducers.counter);

      // the typing for redux-thunk is super complex, so we will use an as unknown hack
      const dispatchedValue = (store.dispatch(
        actions.asyncIncrease() as any
      ) as unknown) as Promise<void>;

      return dispatchedValue.then(() => {
        expect(spy.mock.calls).toHaveLength(2);

        expect(store.getState()).toEqual({ count: 1 });

        done();
      });
    });
  });
});
