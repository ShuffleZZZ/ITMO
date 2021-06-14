const express = require('express');
const router = express.Router();

router.get('/', function (req, res, next) {
  res.send({login: curUser});
});

router.post('/', function (req, res, next) {
  const handleResult = handleData(req.body);

  if (typeof handleResult === 'number') {
    res.sendStatus(handleResult);
  } else {
    res.send(handleResult);
  }
});

router.post('/logout', function (req, res, next) {
  curUser = undefined;

  res.sendStatus(200);
});

const passwordsDB = new Map();
let curUser;

function handleData(body) {
  if (!body.email || !body.password) {
    return 400;
  }

  if (passwordsDB.has(body.email)) {
    if (passwordsDB.get(body.email) !== DJB2hash(body.password)) {
      return 401;
    }
  } else {
    passwordsDB.set(body.email, DJB2hash(body.password));
  }

  curUser = getUser(body.email);
  return {login: curUser};
}

function DJB2hash(string) {
  let hashSum = 5381;
  for (let i = 0; i < string.length; i++) {
    hashSum = (hashSum << 5) + hashSum + string.charCodeAt(i);
  }

  return hashSum;
}

function getUser(email) {
  return /(.*?)@.*/.exec(email)[1];
}

module.exports = router;
