const target = document.getElementById('direction');

target.ontouchstart = starthandler;
target.ontouchmove = movehandler;
target.ontouchend = endhandler;

function starthandler(ev) {
  ev.preventDefault();
  target.moving = true;
  target.oldX = target.style.left.split('px')[0] * 1 + 50;
}

function movehandler(ev) {
  ev.preventDefault();
  if (!document.callRPC) return;
  var currentX = target.style.left.split('px')[0] * 1 + 50;
  if (currentX > target.oldX) {
    document.callRPC('PLAYER_MOVE_RIGHT');
  }
  if (target.oldX > currentX) {
    document.callRPC('PLAYER_MOVE_LEFT');
  }
  if (currentX - target.oldX > 50 || currentX - target.oldX < -50) {
    target.oldX = currentX;
  }
  target.style.left = ev.targetTouches[0].clientX - 50 + 'px';
  target.style.top = ev.targetTouches[0].clientY - 50 + 'px';
}

function endhandler(ev) {
  ev.preventDefault();

  if (document.callRPC && target.moving) {
    document.callRPC('PLAYER_MOVE_STOP');
    target.moving = false;
  }
}
