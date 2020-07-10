/* eslint-disable @typescript-eslint/no-explicit-any */
/* eslint-disable @typescript-eslint/explicit-function-return-type */
import supertest from 'supertest';

import app from '../src/app';
import db from '../src/db';

const request = supertest(app);

const cleanDb = async () => {
  const tableNames = Object.keys(db.sequelize.models);
  await db.sequelize.query(`TRUNCATE ${tableNames.map(name => `"${name}"`).join(', ')} CASCADE;`);
};

describe('API', () => {
  beforeAll(async () => {
    // Здесь создаются все таблицы по моделям
    await db.sequelize.sync({ force: true });
  });

  beforeEach(async () => {
    await cleanDb();
  });

  it('Должно вернуть список мест', async () => {
    const res = await request.get('/locations');

    expect(res.status).toBe(200);
    expect(res.body).toBeInstanceOf(Array);
  });

  it('Должно создать место', async () => {
    const resPost = await request.post('/locations').send({
      name: 'test name',
      description: 'test description'
    });

    const resGet = await request.get('/locations');
    const expectedPartResponse = {
      name: 'test name',
      description: 'test description',
      visited: false
    };

    expect(resPost.status).toBe(204);
    expect(resGet.body[0]).toMatchObject(expectedPartResponse);
  });

  it('Должно вернуть место по id', async () => {
    await request.post('/locations').send({
      name: 'test name by id',
      description: 'test description by id'
    });

    const resGet = await request.get('/locations');
    const expectedPartResponse = {
      name: 'test name by id',
      description: 'test description by id',
      visited: false
    };

    expect(resGet.status).toBe(200);
    expect(resGet.body[0]).toMatchObject(expectedPartResponse);
  });

  it('Должно удалить место по id', async () => {
    await request.post('/locations').send({
      name: 'test name by id',
      description: 'test description by id'
    });
    const resDelete = await request.delete('/locations/1');
    const resGetAfter = await request.get('/locations/1');

    expect(resDelete.status).toBe(204);
    expect(resGetAfter.status).toBe(404);
  });

  it('Должно удалить все места', async () => {
    for (let i = 0; i < 20; i++) {
      await request.post('/locations').send({
        name: `test name by id${i}`,
        description: `test description by id${i}`
      });
    }

    const resGetBefore = await request.get('/locations');
    const resDeleteAll = await request.delete('/locations');
    const resGetAfter = await request.get('/locations');

    expect(resGetBefore.status).toBe(200);
    expect(resGetBefore.body).toHaveLength(20);

    expect(resDeleteAll.status).toBe(204);

    expect(resGetAfter.status).toBe(200);
    expect(resGetAfter.body).toHaveLength(0);
  });
});
