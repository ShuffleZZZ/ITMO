"use strict";

const { List } = require("../models/");

module.exports = async (request, h) => {
  const result = await List.findAll();

  return h.view("home", {
    data: {
      lists: result
    },
    page: "Notes"
  });
};
