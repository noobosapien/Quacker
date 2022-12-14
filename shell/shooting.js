// const turner = document.getElementById('turner');
// const turner_left_limit = document.getElementById('turn_left');
// const turner_right_limit = document.getElementById('turn_right');
// const shooting_range = document.getElementById('shooting_range');

// turner.ontouchstart = shoot_starthandler;
// turner.ontouchmove = shoot_rotatehandler;
// turner.ontouchend = shoot_endhandler;

// function getOffset(el) {
//   const rect = el.getBoundingClientRect();
//   return {
//     left: rect.left + window.scrollX,
//     top: rect.top + window.scrollY,
//   };
// }

// function shoot_starthandler(ev) {
//   ev.preventDefault();
// }

// function shoot_rotatehandler(ev) {
//   ev.preventDefault();
//   if (!document.callRPC) return;

//   var currentX = turner.style.left.split('px')[0] * 1 + 50;
//   if (currentX > turner.oldX) {
//     // document.callRPC('PLAYER_MOVE_RIGHT');
//   }
//   if (turner.oldX > currentX) {
//     // document.callRPC('PLAYER_MOVE_LEFT');
//   }
//   if (currentX - turner.oldX > 50 || currentX - turner.oldX < -50) {
//     turner.oldX = currentX;
//   }

//   const leftLimit = getOffset(turner_left_limit);
//   const rightLimit = getOffset(turner_right_limit);
//   const shootLimit = getOffset(shooting_range);

//   if (
//     ev.targetTouches[0].clientX - 30 > leftLimit.left &&
//     ev.targetTouches[0].clientX + 30 < rightLimit.left
//   ) {
//     turner.style.left = ev.targetTouches[0].clientX - 30 + 'px';
//   }

//   if (ev.targetTouches[0].clientX - 20 <= leftLimit.left) {
//     document.callRPC('PLAYER_ROTATE_LEFT');
//   } else if (ev.targetTouches[0].clientX + 20 >= rightLimit.left) {
//     document.callRPC('PLAYER_ROTATE_RIGHT');
//   } else {
//     document.callRPC('PLAYER_ROTATE_STOP');
//   }

//   if (ev.targetTouches[0].clientY <= shootLimit.top) {
//     turner.style.background = '#fefefe';
//     document.callRPC('PLAYER_SHOOT_START');
//   } else {
//     turner.style.background = 'rgb(255, 128, 0)';
//     document.callRPC('PLAYER_SHOOT_STOP');
//   }

//   turner.style.top = ev.targetTouches[0].clientY - 30 + 'px';

//   // console.log(
//   //   'Turner: ',
//   //   ev.targetTouches[0].clientX + 60 < rightLimit.left,
//   //   rightLimit,
//   //   ev.targetTouches[0].clientX + 30
//   // );
// }

// function shoot_endhandler(ev) {
//   ev.preventDefault();
//   if (document.callRPC) {
//     document.callRPC('PLAYER_ROTATE_STOP');
//     document.callRPC('PLAYER_SHOOT_STOP');

//     turner.style.background = 'rgb(255, 128, 0)';
//     // turner.moving = false;
//   }
// }

const shoot = document.getElementById('shooter');

shoot.ontouchstart = startToShoot;
shoot.ontouchend = endShoot;

function startToShoot(e) {
  e.preventDefault();
  document.callRPC('PLAYER_SHOOT_START');
}

function endShoot(e) {
  e.preventDefault();
  document.callRPC('PLAYER_SHOOT_STOP');
}
