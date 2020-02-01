'use strict';

const weather = require('./weather');

const geoids = [2, 5, 10, 14];

async function main() {
  const path = await weather
    .planTrip(geoids)
    .sunny(2)
    .cloudy(1)
    .build();

  console.info(path);
}

main().catch(console.error);
