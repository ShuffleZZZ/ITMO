'use strict';

/**
 * @typedef {Object} Friend
 * @property {string} name Имя
 * @property {'male' | 'female'} gender Пол
 * @property {boolean} best Лучший ли друг?
 * @property {string[]} friends Список имён друзей
 */

/**
 * Возвращает друзей упорядоченных по уровням приглашений
 * @param {Friend[]} friends список друзей
 * @returns {Friend[]} Список упорядоченных по уровням списков друзей
 */
function getLayers(friends) {
  const delayedPush = new Map();
  const layers = [];
  let curLayer = [];

  friends.forEach(friend => {
    if (friend.best) {
      curLayer.push(friend);
    } else {
      delayedPush.set(friend.name, friend);
    }
  });

  const getNextLayer = function() {
    return curLayer.reduce((layer, friend) => {
      friend.friends.forEach(mate => {
        if (delayedPush.has(mate)) {
          layer.push(delayedPush.get(mate));
          delayedPush.delete(mate);
        }
      });

      return layer;
    }, []);
  };

  while (curLayer.length !== 0) {
    layers.push(curLayer.sort((first, second) => (first.name > second.name ? 1 : -1)));

    curLayer = getNextLayer();
  }

  return layers;
}

/**
 * Итератор по друзьям одного уровня приглашений
 * @constructor
 * @param {Friend[]} friends Список друзей
 * @param {Filter} filter Фильтр друзей
 */
function LayerIterator(friends, filter) {
  this.friends = friends;
  this.filter = filter;

  this.next = function() {
    let friend = this.friends.shift();

    while (friend !== undefined && !this.filter.test(friend)) {
      friend = this.friends.shift();
    }

    return friend || null;
  };

  this.done = function() {
    const friend = this.next();

    if (friend) {
      this.friends.unshift(friend);
    }

    return friend === null;
  };
}

/**
 * Итератор по друзьям
 * @constructor
 * @param {Friend[]} friends Список друзей
 * @param {Filter} filter Фильтр друзей
 */
function Iterator(friends, filter) {
  if (!(filter instanceof Filter)) {
    throw new TypeError('Not a valid filter given');
  }

  this.filter = filter;
  this.layers = getLayers(friends);
  this.depth = 0;

  const firstLayer = this.layers.length ? this.layers[this.depth++] : [];
  this.layerIterator = new LayerIterator(firstLayer, filter);

  this.done = function() {
    return this.layerIterator.done() && this.depth === this.layers.length;
  };

  this.next = function() {
    if (this.done()) {
      return null;
    }

    if (this.layerIterator.done()) {
      this.layerIterator = new LayerIterator(this.layers[this.depth++], this.filter);
    }

    return this.layerIterator.next();
  };
}

/**
 * Итератор по друзям с ограничением по кругу
 * @extends Iterator
 * @constructor
 * @param {Friend[]} friends Список друзей
 * @param {Filter} filter Фильтр друзей
 * @param {Number} maxLevel Максимальный круг друзей
 */
function LimitedIterator(friends, filter, maxLevel) {
  Iterator.call(this, maxLevel && maxLevel > 0 ? friends : [], filter);
  this.layers = this.layers.slice(0, maxLevel);
}

LimitedIterator.prototype = Object.create(Iterator.prototype);

/**
 * Фильтр друзей
 * @constructor
 */
function Filter() {
  this.test = function() {
    return true;
  };
}

/**
 * Фильтр друзей-парней
 * @extends Filter
 * @constructor
 */
function MaleFilter() {
  this.test = function(friend) {
    return friend.gender === 'male';
  };
}

MaleFilter.prototype = Object.create(Filter.prototype);

/**
 * Фильтр друзей-девушек
 * @extends Filter
 * @constructor
 */
function FemaleFilter() {
  this.test = function(friend) {
    return friend.gender === 'female';
  };
}

FemaleFilter.prototype = Object.create(Filter.prototype);

module.exports = {
  Iterator,
  LimitedIterator,
  Filter,
  MaleFilter,
  FemaleFilter
};
