'use strict';

const { getEmitter, isExtraTaskSolved } = require('./emitter');

let students = {
  Sam: {
    focus: 100,
    wisdom: 50
  },
  Sally: {
    focus: 100,
    wisdom: 60
  },
  Bill: {
    focus: 90,
    wisdom: 50
  },
  Sharon: {
    focus: 110,
    wisdom: 40
  }
};

let lecturer = getEmitter();

// С началом лекции у всех резко повышаются показатели
lecturer
  .on('begin', students.Sam, function() {
    this.focus += 10;
  })
  .on('begin', students.Sally, function() {
    this.focus += 10;
  })
  .on('begin', students.Bill, function() {
    this.focus += 10;
    this.wisdom += 5;
  })
  .on('begin', students.Sharon, function() {
    this.focus += 20;
  });

// На каждый слайд внимательность падает, но растет мудрость
lecturer
  .on('slide', students.Sam, function() {
    this.wisdom += Math.round(this.focus * 0.1);
    this.focus -= 10;
  })
  .on('slide', students.Sally, function() {
    this.wisdom += Math.round(this.focus * 0.15);
    this.focus -= 5;
  })
  .on('slide', students.Bill, function() {
    this.wisdom += Math.round(this.focus * 0.05);
    this.focus -= 10;
  })
  .on('slide', students.Sharon, function() {
    this.wisdom += Math.round(this.focus * 0.01);
    this.focus -= 5;
  });

// На каждый веселый слайд всё наоборот
lecturer
  .on('slide.funny', students.Sam, function() {
    this.focus += 5;
    this.wisdom -= 10;
  })
  .on('slide.funny', students.Sally, function() {
    this.focus += 5;
    this.wisdom -= 5;
  })
  .on('slide.funny', students.Bill, function() {
    this.focus += 5;
    this.wisdom -= 10;
  })
  .on('slide.funny', students.Sharon, function() {
    this.focus += 10;
    this.wisdom -= 10;
  });

// Начинаем лекцию
lecturer.emit('begin');
// Sam(110,50); Sally(110,60); Bill(100,55); Sharon(130,40)

lecturer
  .emit('slide.text')
  .emit('slide.text')
  .emit('slide.text')
  .emit('slide.funny');
// Sam(75,79); Sally(95,118); Bill(65,63); Sharon(120,34)

lecturer
  .off('slide.funny', students.Sharon)
  .emit('slide.text')
  .emit('slide.text')
  .emit('slide.funny');
// Sam(50,90); Sally(85,155); Bill(40,62); Sharon(105,37)

lecturer
  .off('slide', students.Bill)
  .emit('slide.text')
  .emit('slide.text')
  .emit('slide.text');

lecturer.emit('end');
// Sam(20,102); Sally(70,191); Bill(40,62); Sharon(90,40)

if (isExtraTaskSolved) {
  students = {
    Sam: {
      focus: 100,
      wisdom: 50
    },
    Bill: {
      focus: 90,
      wisdom: 50
    }
  };

  lecturer = getEmitter()
    .several(
      'begin',
      students.Sam,
      function() {
        this.focus += 10;
      },
      1
    )
    .several(
      'begin',
      students.Bill,
      function() {
        this.focus += 10;
        this.wisdom += 5;
      },
      1
    )
    // На Сэма действуют только нечетные слайды
    .through(
      'slide',
      students.Sam,
      function() {
        this.wisdom += Math.round(this.focus * 0.1);
        this.focus -= 10;
      },
      2
    )
    // Концентрации Билла хватит ровно на 4 слайда
    .several(
      'slide',
      students.Bill,
      function() {
        this.wisdom += Math.round(this.focus * 0.05);
        this.focus -= 10;
      },
      4
    )
    .on('slide.funny', students.Sam, function() {
      this.focus += 5;
      this.wisdom -= 10;
    })
    .on('slide.funny', students.Bill, function() {
      this.focus += 5;
      this.wisdom -= 10;
    });

  lecturer.emit('begin');
  // Sam(110,50); Bill(100,55)

  lecturer
    .emit('slide.text')
    .emit('slide.text')
    .emit('slide.text')
    .emit('slide.funny');
  // Sam(95,61); Bill(65,63)

  lecturer
    .emit('slide.text')
    .emit('slide.text')
    .emit('slide.funny');
  // Sam(80,70); Bill(70,53)
}
