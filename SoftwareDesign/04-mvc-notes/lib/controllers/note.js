"use strict";

const { List, Note } = require("../models/");
const Slugify = require("slug");
const Pug = require("pug");
const Path = require("path");

module.exports = {
  create: async (request, h) => {
    await Note.create({
      date: new Date(),
      title: request.payload.noteTitle,
      slug: Slugify(request.payload.noteTitle, { lower: true }),
      list: Slugify(request.payload.noteList, { lower: true }),
      content: request.payload.noteContent,
      isDone: false
    });

    const [list, isCreated] = await List.findOrCreate({
      where: {
        slug: Slugify(request.payload.noteList, { lower: true })
      },
      defaults: {
        title: request.payload.noteList,
        count: 1
      }
    });

    if (!isCreated) {
      await List.update(
        {
          count: list.count + 1
        },
        {
          where: {
            slug: list.slug
          }
        }
      );
    }

    const resList = await List.findOne({
      where: {
        slug: list.slug
      }
    });

    return Pug.renderFile(Path.join(__dirname, "../views/components/list.pug"), {
      list: resList
    });
  },

  read: async (request, h) => {
    const note = await Note.findOne({
      where: {
        slug: request.params.slug
      }
    });

    return h.view("note", {
      note,
      page: `${note.title} note`
    });
  },

  done: async (request, h) => {
    const options = {
      where: {
        slug: request.params.slug
      }
    };

    await Note.update({ isDone: true }, options);

    const note = await Note.findOne(options);

    const list = await List.findOne({
      where: {
        slug: note.list
      }
    });

    return h.redirect(`/list/${list.slug}`);
  },

  delete: async (request, h) => {
    const options = {
      where: {
        slug: request.params.slug
      }
    };

    const note = await Note.findOne(options);

    await Note.destroy(options);

    const list = await List.findOne({
      where: {
        slug: note.list
      }
    });

    const listOptions = {
      where: {
        slug: note.list
      }
    };

    if (list.count === 1) {
      await List.destroy(listOptions);
      return h.redirect("/");
    }

    await List.update(
      {
        count: list.count - 1
      },
      listOptions
    );

    return h.redirect(`/list/${list.slug}`);
  }
};
