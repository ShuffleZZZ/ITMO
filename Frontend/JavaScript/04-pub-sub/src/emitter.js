'use strict';

/**
 * Сделано дополнительное задание: реализованы методы several и through.
 */
const isExtraTaskSolved = true;

const SINGLE = 0;
const SEVERAL = 1;
const THROUGH = 2;

/**
 * Получение нового Emitter'а
 * @returns {Object}
 */
function getEmitter() {
  const events = {};

  function subscribeEvent(event, context, handler, type, value) {
    if (!(event in events)) {
      events[event] = [];
    }

    events[event].push({ context, handler, type, value, amount: 0 });
  }

  return {
    /**
     * Подписка на событие
     * @param {string} event
     * @param {Object} context
     * @param {Function} handler
     */
    on: function(event, context, handler) {
      subscribeEvent(event, context, handler, SINGLE, null);

      return this;
    },

    /**
     * Отписка от события
     * @param {string} event
     * @param {Object} context
     */
    off: function(event, context) {
      for (const subscribedEvent of Object.keys(events)) {
        if (subscribedEvent.startsWith(`${event}.`) || subscribedEvent === event) {
          events[subscribedEvent] = events[subscribedEvent].filter(
            item => item.context !== context
          );
        }
      }

      return this;
    },

    /**
     * Уведомление о событии
     * @param {string} event
     */
    emit: function(event) {
      while (event) {
        for (const curEvent of events[event] || []) {
          const pleasingSeveral = curEvent.type === SEVERAL && curEvent.amount < curEvent.value;
          const pleasingThrough = curEvent.type === THROUGH && !(curEvent.amount % curEvent.value);
          if (curEvent.type === SINGLE || pleasingSeveral || pleasingThrough) {
            curEvent.handler.call(curEvent.context);
          }

          curEvent.amount++;
        }

        event = (/(.*)\.\S+/.exec(event) || [])[1];
      }

      return this;
    },

    /**
     * Подписка на событие с ограничением по количеству отправляемых уведомлений
     * @param {string} event
     * @param {Object} context
     * @param {Function} handler
     * @param {number} times Сколько раз отправить уведомление
     */
    several: function(event, context, handler, times) {
      subscribeEvent(event, context, handler, times <= 0 ? SINGLE : SEVERAL, times);

      return this;
    },

    /**
     * Подписка на событие с ограничением по частоте отправки уведомлений
     * @param {string} event
     * @param {Object} context
     * @param {Function} handler
     * @param {number} frequency Как часто уведомлять
     */
    through: function(event, context, handler, frequency) {
      subscribeEvent(event, context, handler, frequency <= 0 ? SINGLE : THROUGH, frequency);

      return this;
    }
  };
}

module.exports = {
  getEmitter,

  isExtraTaskSolved
};
