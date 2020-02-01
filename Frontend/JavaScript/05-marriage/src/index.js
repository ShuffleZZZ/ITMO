'use strict';

const marriage = require('./marriage');

const friends = [
  {
    name: 'Sam',
    friends: ['Mat', 'Sharon'],
    gender: 'male',
    best: true
  },
  {
    name: 'Sally',
    friends: ['Brad', 'Emily'],
    gender: 'female',
    best: true
  },
  {
    name: 'Mat',
    friends: ['Sam', 'Sharon'],
    gender: 'male'
  },
  {
    name: 'Sharon',
    friends: ['Sam', 'Itan', 'Mat'],
    gender: 'female'
  },
  {
    name: 'Brad',
    friends: ['Sally', 'Emily', 'Julia'],
    gender: 'male'
  },
  {
    name: 'Emily',
    friends: ['Sally', 'Brad'],
    gender: 'female'
  },
  {
    name: 'Itan',
    friends: ['Sharon', 'Julia'],
    gender: 'male'
  },
  {
    name: 'Julia',
    friends: ['Brad', 'Itan'],
    gender: 'female'
  }
];

// Создаем фильтры парней и девушек
const maleFilter = new marriage.MaleFilter();
const femaleFilter = new marriage.FemaleFilter();

// Создаем итераторы
const femaleIterator = new marriage.Iterator(friends, femaleFilter);

// Среди парней приглашаем только луших друзей и друзей лучших друзей
const maleIterator = new marriage.LimitedIterator(friends, maleFilter, 2);

const invitedFriends = [];

// Собираем пары «парень + девушка»
while (!maleIterator.done() && !femaleIterator.done()) {
  invitedFriends.push([maleIterator.next(), femaleIterator.next()]);
}

// Если остались девушки, то приглашаем остальных
while (!femaleIterator.done()) {
  invitedFriends.push(femaleIterator.next());
}

console.info(invitedFriends);
// Sam, Sally
// Brad, Emily
// Mat, Sharon
// Julia
