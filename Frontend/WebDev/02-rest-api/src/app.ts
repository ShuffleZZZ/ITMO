import express, { Request, Response } from 'express';
import { FindOptions, Op } from 'sequelize';

import Location from './db/model/location';

const app = express();

app.use(express.json());
app.use(express.urlencoded({ extended: true }));

function getAll(req: Request, res: Response): void {
  const sortBy = req.body.order || 'createdAt';
  const description = req.body.description;
  const limit = req.body.limit || 256;
  const offset = req.body.limit || 0;

  const options: FindOptions = { limit, offset };

  if (sortBy === 'createdAt' || sortBy === 'name') {
    options.order = [sortBy];
  } else {
    res.status(400);

    return;
  }

  if (description) {
    options.where = { description: { [Op.substring]: description } };
  }

  Location.findAll(options).then(locations => res.status(200).send(locations));
}

function getById(req: Request, res: Response): void {
  const id = req.params.id;

  Location.findByPk(id)
    .then(location => (location ? res.send(location) : res.sendStatus(404)))
    .catch(() => res.sendStatus(404));
}

function insert(req: Request, res: Response): void {
  const body = req.body;

  const place = {
    name: body.name,
    description: body.description,
    country: body.country,
    city: body.city
  };

  Location.create(place).then(() => res.sendStatus(204));
}

function update(req: Request, res: Response): void {
  Location.update(req.body, { where: { id: req.params.id } })
    .then(location => res.sendStatus(location ? 204 : 404))
    .catch(() => res.sendStatus(504));
}

function deleteById(req: Request, res: Response): void {
  const id = req.params.id;
  const locations = { where: { id } };

  Location.destroy(locations).then(() => res.sendStatus(204));
}

function deleteAll(req: Request, res: Response): void {
  Location.truncate().then(() => res.sendStatus(204));
}

app.get('/locations', getAll);
app.get('/locations/:id', getById);
app.post('/locations', insert);
app.patch('/locations/:id', update);
app.delete('/locations', deleteAll);
app.delete('/locations/:id', deleteById);

export default app;
