'use strict';

global.fetch = require('node-fetch');

const ERROR_STRING = 'Не могу построить маршрут!';

/**
 * @typedef {object} TripItem Город, который является частью маршрута.
 * @property {number} geoid Идентификатор города
 * @property {number} day Порядковое число дня маршрута
 */

class TripBuilder {
  /**
   * Конструктор с заданным geoids
   * @param {geoid[]} geoids
   */
  constructor(geoids) {
    this.geoids = geoids;
    this.tripPlan = [];
    this.limit = 7;
  }

  /**
   * Метод, добавляющий условие наличия в маршруте
   * указанного количества солнечных дней
   * Согласно API Яндекс.Погоды, к солнечным дням
   * можно приравнять следующие значения `condition`:
   * * `clear`;
   * * `partly-cloudy`.
   * @param {number} daysCount количество дней
   * @returns {object} Объект планировщика маршрута
   */
  sunny(daysCount) {
    this.tripPlan = this.tripPlan.concat(Array(daysCount).fill('sunny'));

    return this;
  }

  /**
   * Метод, добавляющий условие наличия в маршруте
   * указанного количества пасмурных дней
   * Согласно API Яндекс.Погоды, к солнечным дням
   * можно приравнять следующие значения `condition`:
   * * `cloudy`;
   * * `overcast`.
   * @param {number} daysCount количество дней
   * @returns {object} Объект планировщика маршрута
   */
  cloudy(daysCount) {
    this.tripPlan = this.tripPlan.concat(Array(daysCount).fill('cloudy'));

    return this;
  }

  /**
   * Метод, добавляющий условие максимального количества дней.
   * @param {number} daysCount количество дней
   * @returns {object} Объект планировщика маршрута
   */
  max(daysCount) {
    this.limit = daysCount;

    return this;
  }

  /**
   * Метод, возвращающий Promise с планируемым маршрутом.
   * @returns {Promise<TripItem[]>} Список городов маршрута
   */
  build() {
    return Promise.all(this.geoids.map(geoid => getWeather(geoid))).then(tripItems => {
      const tripPlan = this.tripPlan;
      const limit = this.limit;
      const tripItemsToDays = new Map();

      const trip = buildTrip([], -1);

      if (!trip) {
        throw new Error(ERROR_STRING);
      }

      return trip;

      function buildTrip(curTrip, curGeoid) {
        const curDay = curTrip.length;

        if (curDay === tripPlan.length) {
          return curTrip;
        }

        for (const tripItem of tripItems) {
          const daysInCity = tripItemsToDays.get(tripItem.geoId) || 0;

          const isFirst = daysInCity === 0;
          const canStay = daysInCity < limit && tripItem.geoId === curGeoid;
          const suitsForecast = tripItem.weather[curDay] === tripPlan[curDay];

          if ((isFirst || canStay) && suitsForecast) {
            tripItemsToDays.set(tripItem.geoId, daysInCity + 1);
            const followTrip = buildTrip(
              curTrip.concat({ geoid: tripItem.geoId, day: curDay + 1 }),
              tripItem.geoId
            );

            if (followTrip === null) {
              tripItemsToDays.set(tripItem.geoId, daysInCity);
            } else {
              return followTrip;
            }
          }
        }

        return null;
      }
    });
  }
}

/**
 * Делает запрос по данному geoid и возвращает сопоставленный ему TripItem.
 *
 * @param geoid Идентификатор города
 * @returns {Promise<TripItem>} TripItem сопоставленный данному geoid
 */
function getWeather(geoid) {
  return global
    .fetch(`https://api.weather.yandex.ru/v1/forecast?hours=false&limit=7&geoid=${geoid}`)
    .then(response => response.json())
    .then(json => ({
      geoId: geoid,
      weather: json['forecasts'].map(day => {
        return parseCondition(day['parts']['day_short']['condition']);
      })
    }));
}

/**
 * Транслирует принимаемое значение прогноза погоды в рассматриваемое в маршрутах.
 *
 * @param {string} forecast Значение прогноза погоды, полученное из запроса
 * @returns {string | undefined} Значение прогноза погоды, рассматриваемое в маршруте
 */
function parseCondition(forecast) {
  if (forecast === 'clear' || forecast === 'partly-cloudy') {
    return 'sunny';
  }
  if (forecast === 'cloudy' || forecast === 'overcast') {
    return 'cloudy';
  }
}

/**
 * Фабрика для получения планировщика маршрута.
 * Принимает на вход список идентификаторов городов, а
 * возвращает планировщик маршрута по данным городам.
 *
 * @param {geoid[]} geoids Список идентификаторов городов
 * @returns {TripBuilder} Объект планировщика маршрута
 * @see https://yandex.ru/dev/xml/doc/dg/reference/regions-docpage/
 */
function planTrip(geoids) {
  return new TripBuilder(geoids);
}

module.exports = {
  planTrip
};
