"use strict";

const { List, Note } = require("../models/");

module.exports = async (request, h) => {
  const list = await List.findOne({
    where: {
      slug: request.params.slug
    }
  });
  const notes = await Note.findAll({
    where: {
      list: list.slug
    },
    order: [["date", "DESC"]]
  });

  return h.view("list", {
    list,
    data: {
      notes: notes
    },
    page: `${list.title}'s notes`
  });
};
