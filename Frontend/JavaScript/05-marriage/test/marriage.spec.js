'use strict';

const marriage = require('../src/marriage');

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

describe('Итераторы', () => {
  it('должны обойти в правильном порядке друзей и составить пары', () => {
    const maleFilter = new marriage.MaleFilter();
    const femaleFilter = new marriage.FemaleFilter();
    const maleIterator = new marriage.LimitedIterator(friends, maleFilter, 2);
    const femaleIterator = new marriage.Iterator(friends, femaleFilter);

    const invitedFriends = [];

    while (!maleIterator.done() && !femaleIterator.done()) {
      invitedFriends.push([maleIterator.next(), femaleIterator.next()]);
    }

    while (!femaleIterator.done()) {
      invitedFriends.push(femaleIterator.next());
    }

    expect(invitedFriends).toStrictEqual([
      [getFriend('Sam'), getFriend('Sally')],
      [getFriend('Brad'), getFriend('Emily')],
      [getFriend('Mat'), getFriend('Sharon')],
      getFriend('Julia')
    ]);
  });

  function getFriend(name) {
    let len = friends.length;

    while (len--) {
      if (friends[len].name === name) {
        return friends[len];
      }
    }
  }
});
