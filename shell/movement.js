let target = null;

function filter(e) {
  // console.log(document.callRPC);
  document.callRPC([0.2, 1, 4, 2], 4);

  target = e.target;

  if (!target.classList.contains('draggable')) {
    return;
  }

  target.moving = true;

  if (e.clientX) {
    target.oldX = e.clientX;
    // target.oldY = e.clientY;
  } else {
    target.oldX = e.touches[0].clientX;
    // target.oldY = e.touches[0].clientY;
  }

  target.oldLeft =
    window.getComputedStyle(target).getPropertyValue('left').split('px')[0] * 1;
  //   target.oldTop =
  //     window.getComputedStyle(target).getPropertyValue('top').split('px')[0] * 1;

  document.onmousemove = dr;
  document.ontouchmove = dr;

  function dr(event) {
    event.preventDefault();

    if (!target.moving) {
      return;
    }

    if (event.clientX) {
      target.distX = event.clientX - target.oldX;
      //   target.distY = event.clientY - target.oldY;
    } else {
      target.distX = event.touches[0].clientX - target.oldX;
      //   target.distY = event.touches[0].clientY - target.oldY;
    }

    target.style.left = target.oldLeft + target.distX + 'px';
    // target.style.top = target.oldTop + target.distY + 'px';
  }

  // target.onmouseup = endDrag;
  // target.ontouchend = endDrag;
}

function endDrag() {
  if (target) {
    target.moving = false;
  }
}

document.onmousedown = filter;
document.ontouchstart = filter;
document.onmouseup = endDrag;
document.ontouchend = endDrag;
