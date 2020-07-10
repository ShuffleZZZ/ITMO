# Задача «Redux_2»

> Мы очень хотим, чтобы код вы написали сами, а не пользовались внешними библиотеками.

## Основное задание

Вы попали в параллельную Вселенную, где Дэн Абрамов решил заниматься музыкой и не написал redux.
Вам нужно исправить вселенскую несправедливость и написать библиотеку redux.

Библиотека должна предоставлять следущую функциональность:

###`createStore`
для создания `store` используется функция `createStore(reducer, [initialState], [enhancer])`, где

-`reducer(state, action: Action)` – функция принимающая текущий `state` и `action` для изменения состояния, и возвращаюещее новое состояние. `Action` – простой объект, который должен содержать текстовое поле `type`.

-`initialState` – начальное значение `state` для `reducer`. Опциональное поле.

-`enhancer` – функция, позволяющая "усилить" `store`. имеет вид `const enhancer = originalCreateStore => ({ reducer, initialState }) => {/* return store */}`, где `originalCreateStore` – сама функция `createStore` из библиотеки, `{ reducer, initialState }` - переданный в `createStore` параметры. Эта функция позволяет реализовать девтулзы или систему мидлвар. Опциональное поле.

### `store`

у созданного объекта `store` не должно быть доступно получить состояние напрямую, но должны быть доступны следующие методы:

- `getState` – возвращает текущее состояние

- `dispatch(action: Action)` – принимает `action` в качестве аргумента и вызывает изменение внутренного состояния `store`, передавая `action` в `reducer` и перезаписывая внутреннее состояние.

- `subscribe(listener)` – функция для подписки на изменения. Передаваемый колбэк вызывается после каждого возможного изменения состояния `store`. Единственный способ изменения этого состояния – вызов `dispatch(action)`. `subscribe` возвращает функцию, вызов которой "отписывает" переданный колбэк от оповещений о изменении состояния.

### `applyMiddleware(...middleware)`

Система мидлвар в `redux` позволяет гибко расширять библиотеку. Например с помощью мидлвар можно добавить логирование, работу с ассинхронными функциями и даже девтулзы.

Мидлвара – некоторая функция, которая будет применена после вызова `dispatch`, но до обработки редьюсерами.

общий вид мидлвар такой: `const middleware = ({ dispatch, getState }) => next => action => yourCallback`, где

- `{ dipatch, getState }` - методы `store` позволяющие узнать состояние приложение, например, для логирования, и поменять его, например после запроса на сервер.

- `next` – это либо следующая мидлвара, либо, если текущая мидлвара – последняя, реальный `dispatch`, который изменит состояние.

- `action` – текущий `action`, который был передан в `dispatch`

Пример мидлвары:

```js
function logger({ getState }) {
  return next => action => {
    console.log('will dispatch', action);
    console.log('state before dispatch', getState());

    // Call the next dispatch method in the middleware chain.
    const returnValue = next(action);

    console.log('state after dispatch', getState());

    // This will likely be the action itself, unless
    // a middleware further in chain changed it.
    return returnValue;
  };
}

const store = createStore(reducer, initialState, applyMiddleware(logger));
```

Как вы видите в типах есть `any`. Вы можете использовать текущие типы или расширять, уточнять и улучшать их. 

## Доступные команды

Запускаются так: `npm run <command>`

| Команда       | Действие                                |
| ------------- | --------------------------------------- |
| build         | Компиляция кода                         |
| test          | Запуск всех тестов                      |
| test:watch    | Запуск тестов при изменении кода        |
| test:coverage | Проверка уровня покрытия кода тестами   |
| lint          | Проверка кода линтером                  |
| lint-fix      | Исправление ошибок, выявленных линтером |
| format        | Форматирование кода                     |

## Полезные ссылки

- [Документация по TypeScript](https://www.typescriptlang.org/docs/home.html)
- [TypeScript Deep Dive](https://basarat.gitbooks.io/typescript/)
