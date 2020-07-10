import { Sequelize } from 'sequelize';

const sequelize = new Sequelize('itmo', 'admin', 'admin', {
  dialect: 'postgres',
  host: 'postgres'
});

const placeholder = { sequelize };

export default placeholder;
