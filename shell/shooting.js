const turner = document.getElementById('turner');
const turner_left_limit = document.getElementById('turn_left');
const turner_right_limit = document.getElementById('turn_right');

turner.ontouchstart = shoot_starthandler;
turner.ontouchmove = shoot_rotatehandler;
turner.ontouchend = shoot_endhandler;

function getOffset(el) {
  const rect = el.getBoundingClientRect();
  return {
    left: rect.left + window.scrollX,
    top: rect.top + window.scrollY,
  };
}

function shoot_starthandler(ev) {
  ev.preventDefault();
}

function shoot_rotatehandler(ev) {
  ev.preventDefault();
  if (!document.callRPC) return;

  var currentX = turner.style.left.split('px')[0] * 1 + 50;
  if (currentX > turner.oldX) {
    // document.callRPC('PLAYER_MOVE_RIGHT');
  }
  if (turner.oldX > currentX) {
    // document.callRPC('PLAYER_MOVE_LEFT');
  }
  if (currentX - turner.oldX > 50 || currentX - turner.oldX < -50) {
    turner.oldX = currentX;
  }

  const leftLimit = getOffset(turner_left_limit);
  const rightLimit = getOffset(turner_right_limit);

  if (
    ev.targetTouches[0].clientX - 30 > leftLimit.left &&
    ev.targetTouches[0].clientX + 30 < rightLimit.left
  ) {
    turner.style.left = ev.targetTouches[0].clientX - 30 + 'px';
  }

  if (ev.targetTouches[0].clientX - 20 <= leftLimit.left) {
    document.callRPC('PLAYER_ROTATE_LEFT');
  } else if (ev.targetTouches[0].clientX + 20 >= rightLimit.left) {
    document.callRPC('PLAYER_ROTATE_RIGHT');
  } else {
    document.callRPC('PLAYER_ROTATE_STOP');
  }

  turner.style.top = ev.targetTouches[0].clientY - 30 + 'px';

  // console.log(
  //   'Turner: ',
  //   ev.targetTouches[0].clientX + 60 < rightLimit.left,
  //   rightLimit,
  //   ev.targetTouches[0].clientX + 30
  // );
}

function shoot_endhandler(ev) {
  ev.preventDefault();
  if (document.callRPC) {
    document.callRPC('PLAYER_ROTATE_STOP');
    // turner.moving = false;
  }
}
