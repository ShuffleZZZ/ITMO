import { Action, AnyState, TCounterState } from './types';

const counterReducer = (state: TCounterState = { count: 0 }, action: Action): TCounterState => {
  if (action.type === 'INCREASE') {
    return { count: state.count + 1 };
  }

  return state;
};

const errorReducer = (state: AnyState, action: Action): AnyState => {
  if (action.type === 'ERROR') {
    throw new Error('reducer error');
  }

  return state;
};

const reducer = (state: AnyState): AnyState => state;

const reducers = {
  default: reducer,
  counter: counterReducer,
  error: errorReducer
};

const actions = {
  unknown: () => ({ type: 'UNKNOWN' }),
  increase: () => ({ type: 'INCREASE' }),
  error: () => ({ type: 'ERROR' }),
  asyncIncrease: () => {
    return (dispatch: any): Promise<void> =>
      new Promise(resolve =>
        setImmediate(() => {
          dispatch(actions.increase());
          resolve();
        })
      );
  }
};

function thunk({ dispatch, getState }: any) {
  return (next: any) => <T>(action: any) =>
    typeof action === 'function' ? action(dispatch, getState) : next(action);
}

export { reducer, reducers, actions, thunk };
