interface Action<T = any> {
  type: T;
}

type AnyAction = Action<any>;

type AnyState = any;

type Reducer<S = AnyState, A extends Action = AnyAction> = (state: S | undefined, action: A) => S;

type TCounterState = {
  count: number;
};

type TEnhancerTuple = [Reducer<AnyState, AnyAction>, AnyState];

interface Unsubscribe {
  (): void;
}

interface Store<S = AnyState, A extends Action = AnyAction> {
  dispatch(action: A): void;
  getState(): S;
  subscribe(listener: () => void): Unsubscribe;
}

interface StoreCreator {
  <S, A extends Action>(reducer: Reducer<S, A>, preloadedState?: S, enhancer?: any): Store<S, A>;
}

export {
  Action,
  AnyAction,
  AnyState,
  Reducer,
  TCounterState,
  TEnhancerTuple,
  Unsubscribe,
  Store,
  StoreCreator
};
