import { DataTypes, Model } from 'sequelize';

import db from '../index';

class Location extends Model {}

Location.init(
  {
    id: {
      type: DataTypes.INTEGER,
      autoIncrement: true,
      primaryKey: true
    },
    name: {
      type: DataTypes.STRING,
      allowNull: false
    },
    description: {
      type: DataTypes.TEXT,
      allowNull: false
    },
    country: DataTypes.STRING,
    city: DataTypes.STRING,
    visited: {
      type: DataTypes.BOOLEAN,
      allowNull: false,
      defaultValue: false
    }
  },
  {
    sequelize: db.sequelize,
    tableName: 'Location'
  }
);

export default Location;
