'use strict';

/**
 * Флаг решения дополнительной задачи
 * @see README.md
 */
const isExtraTaskSolved = true;

const DAYS_OF_WEEK = { ПН: 0, ВТ: 1, СР: 2 };

const MINS_IN_HOUR = 60;
const HOURS_IN_DAY = 24;
const MINS_IN_DAY = MINS_IN_HOUR * HOURS_IN_DAY;

const AVAILABLE_STAMP_SIZE = MINS_IN_DAY * 3;

const NEXT_GAP_BREAK = 30;

const BUSY = 1;
const READY_AND_OPEN = 2;

/**
 * @param {Object} schedule Расписание Банды
 * @param {number} duration Время на ограбление в минутах
 * @param {Object} workingHours Время работы банка
 * @param {string} workingHours.from Время открытия, например, "10:00+5"
 * @param {string} workingHours.to Время закрытия, например, "18:00+5"
 * @returns {Object}
 */
function getAppropriateMoment(schedule, duration, workingHours) {
  const bankTimeZone = workingHours.from.slice(workingHours.from.length - 1);
  const availableStamp = [];

  /**
   * Вносит данные о данном промежутке
   * @param {Object} stamp временной промежуток от и до
   * @param {Boolean} isBank является ли stamp расписанием банка
   */
  function parseStamp(stamp, isBank) {
    const borders = Object.values(stamp).map(string => {
      const [day, time] = isBank ? ['ПН', string] : string.split(' ');
      const [hours, rest] = time.split(':');
      const [minutes, timeZone] = rest.split('+');

      return Math.max(
        Number(minutes) +
          (hours - (timeZone - bankTimeZone)) * MINS_IN_HOUR +
          DAYS_OF_WEEK[day] * MINS_IN_DAY,
        0
      );
    });

    for (let i = borders[0]; i < borders[1]; i++) {
      if (!isBank) {
        availableStamp[i] = BUSY;

        continue;
      }
      for (let j = 0; j < Object.keys(DAYS_OF_WEEK).length; j++) {
        if (!availableStamp[i + MINS_IN_DAY * j]) {
          availableStamp[i + MINS_IN_DAY * j] = READY_AND_OPEN;
        }
      }
    }
  }

  /**
   * Находит все удовлетворяющие промежутки данной продолжительности и разницей не меньше 30 минут
   * @param {Number} duration продолжительность временного промежутка
   * @returns {Number[]} время старта каждого удовлетворяющего промежутка
   */
  function getFreeGaps(duration) {
    const res = [];
    let freeStreak = 0;

    for (let i = 0; i < AVAILABLE_STAMP_SIZE; i++) {
      while (
        i < AVAILABLE_STAMP_SIZE &&
        freeStreak < duration &&
        availableStamp[i] === READY_AND_OPEN
      ) {
        freeStreak++;
        i++;
      }

      if (freeStreak === duration) {
        res.push(i - freeStreak);
        i += NEXT_GAP_BREAK - freeStreak - 1;
      }
      freeStreak = 0;
    }

    return res;
  }

  Object.values(schedule).forEach(name => {
    for (const stamp of name) {
      parseStamp(stamp, false);
    }
  });
  parseStamp(workingHours, true);

  const freeGaps = getFreeGaps(duration);
  let gapIndex = 0;

  return {
    /**
     * Найдено ли время
     * @returns {boolean}
     */
    exists() {
      return freeGaps.length !== 0;
    },

    /**
     * Возвращает отформатированную строку с часами
     * для ограбления во временной зоне банка
     *
     * @param {string} template
     * @returns {string}
     *
     * @example
     * ```js
     * getAppropriateMoment(...).format('Начинаем в %HH:%MM (%DD)') // => Начинаем в 14:59 (СР)
     * ```
     */
    format(template) {
      if (!this.exists()) {
        return '';
      }

      const mins = freeGaps[gapIndex] % MINS_IN_HOUR;
      const hours = Math.floor(freeGaps[gapIndex] / MINS_IN_HOUR) % HOURS_IN_DAY;
      const days = Math.floor(freeGaps[gapIndex] / MINS_IN_DAY);

      function formattedDay() {
        for (const [dayName, digit] of Object.entries(DAYS_OF_WEEK)) {
          if (digit === days) {
            return dayName;
          }
        }
      }

      return template
        .replace(/%D{2}/, formattedDay())
        .replace(/%H{2}/, String(hours).padStart(2, '0'))
        .replace(/%M{2}/, String(mins).padStart(2, '0'));
    },

    /**
     * Попробовать найти часы для ограбления позже [*]
     * @note Не забудь при реализации выставить флаг `isExtraTaskSolved`
     * @returns {boolean}
     */
    tryLater() {
      return gapIndex + 1 >= freeGaps.length ? false : Boolean(++gapIndex);
    }
  };
}

module.exports = {
  getAppropriateMoment,

  isExtraTaskSolved
};
