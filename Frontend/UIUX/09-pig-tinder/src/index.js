'use strict';

const LAST_CARD = 4;
let curCard = 0;

function swipeRight() {
  swipe(1);
}

function superLike() {
  swipe(0);
}

function swipeLeft() {
  swipe(-1);
}

function swipe(swipeType) {
  if (curCard === LAST_CARD) {
    return;
  }

  const oldCardStyle = document.getElementById(`card${curCard++}`).style;
  const sealStyle = document.getElementById(`seal${swipeType}`).style;

  sealStyle.display = 'block';

  oldCardStyle.transform = `translate3d(${swipeType * 100}%, ${-50 *
    (1 + (swipeType === 0))}%, 0) rotateZ(${swipeType * 75}deg)`;

  setTimeout(function() {
    sealStyle.display = 'none';
    oldCardStyle.display = 'none';
  }, 400);

  document.getElementById(`card${curCard}`).style.opacity = '1';
}
