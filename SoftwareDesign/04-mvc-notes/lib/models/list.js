"use strict";

const Moment = require("moment");

module.exports = (sequelize, DataTypes) => {
  const List = sequelize.define("List", {
    title: DataTypes.STRING,
    slug: DataTypes.STRING,
    count: DataTypes.INTEGER
  });

  return List;
};
