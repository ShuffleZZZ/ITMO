'use strict';

const qs = require('querystring');

const nock = require('nock');

const weather = require('../src/weather');

/**
 * Эмуляция запросов к API
 * @param {number[]} geoids Список идентификаторов городов
 * @param {number=1} times Количество повторений запросов
 */
const nockAPIRequests = (geoids, { presetName = 'default' } = {}) =>
  nock('https://api.weather.yandex.ru')
    .persist()
    .get('/v1/forecast')
    .query(q => geoids.includes(parseInt(q.geoid)))
    .reply(200, uri => {
      return require(`./__fixtures__/${presetName}/${qs.parse(uri).geoid}.json`);
    });

describe('Планировщик маршрута', () => {
  const geoids = [2, 5, 7, 10, 11, 14, 213];

  describe('Простой маршрут', () => {
    beforeEach(() => {
      nockAPIRequests(geoids, { limit: 2 });
    });

    it('Должен правильно построить маршрут', async () => {
      expect(
        await weather
          .planTrip(geoids)
          .cloudy(1)
          .sunny(1)
          .build()
      ).toStrictEqual([
        { geoid: 11, day: 1 },
        { geoid: 7, day: 2 }
      ]);
    });

    it('Должен выкинуть исключение если нет маршрута', async () => {
      expect.assertions(1);

      return expect(
        weather
          .planTrip(geoids)
          .sunny(3)
          .build()
      ).rejects.toThrow(new Error('Не могу построить маршрут!'));
    });
  });

  afterEach(() => nock.cleanAll());
});
