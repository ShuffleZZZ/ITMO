'use strict';

const robbery = require('./robbery');

const gangSchedule = {
  Danny: [{ from: 'ПН 12:00+5', to: 'ПН 17:00+5' }, { from: 'ВТ 13:00+5', to: 'ВТ 16:00+5' }],
  Rusty: [{ from: 'ПН 11:30+5', to: 'ПН 16:30+5' }, { from: 'ВТ 13:00+5', to: 'ВТ 16:00+5' }],
  Linus: [
    { from: 'ПН 09:00+3', to: 'ПН 14:00+3' },
    { from: 'ПН 21:00+3', to: 'ВТ 09:30+3' },
    { from: 'СР 09:30+3', to: 'СР 15:00+3' }
  ]
};

const bankWorkingHours = {
  from: '10:00+5',
  to: '18:00+5'
};

// Время не существует
const longMoment = robbery.getAppropriateMoment(gangSchedule, 121, bankWorkingHours);

// Выведется `false` и `""`
console.info(longMoment.exists());
console.info(longMoment.format('Метим на %DD, старт в %HH:%MM!'));

// Время существует
const moment = robbery.getAppropriateMoment(gangSchedule, 90, bankWorkingHours);

// Выведется `true` и `"Метим на ВТ, старт в 11:30!"`
console.info(moment.exists());
console.info(moment.format('Метим на %DD, старт в %HH:%MM!'));

if (robbery.isExtraTaskSolved) {
  // Вернет `true`
  moment.tryLater();
  // `"ВТ 16:00"`
  console.info(moment.format('%DD %HH:%MM'));

  // Вернет `true`
  moment.tryLater();
  // `"ВТ 16:30"`
  console.info(moment.format('%DD %HH:%MM'));

  // Вернет `true`
  moment.tryLater();
  // `"СР 10:00"`
  console.info(moment.format('%DD %HH:%MM'));

  // Вернет `false`
  moment.tryLater();
  // `"СР 10:00"`
  console.info(moment.format('%DD %HH:%MM'));
}

const moment2 = robbery.getAppropriateMoment(gangSchedule, 121, bankWorkingHours);

console.info(!moment2.exists());
console.info(moment2.format('Метим на %DD, старт в %HH:%MM!'), '');
