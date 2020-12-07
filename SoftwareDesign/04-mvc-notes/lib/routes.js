"use strict";

const Path = require("path");
const Note = require("./controllers/note");
const Home = require("./controllers/home");
const List = require("./controllers/list");

module.exports = [
  {
    method: "GET",
    path: "/",
    handler: Home
  },
  {
    method: "GET",
    path: "/list/{slug}",
    handler: List
  },
  {
    method: "POST",
    path: "/note",
    handler: Note.create
  },
  {
    method: "GET",
    path: "/note/{slug}",
    handler: Note.read
  },
  {
    method: "GET",
    path: "/note/{slug}/done",
    handler: Note.done
  },
  {
    method: "GET",
    path: "/note/{slug}/delete",
    handler: Note.delete
  },
  {
    // Static files
    method: "GET",
    path: "/{param*}",
    handler: {
      directory: {
        path: Path.join(__dirname, "../static/public")
      }
    }
  }
];
