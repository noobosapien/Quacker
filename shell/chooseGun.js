const gun1 = document.getElementById('gun1');
const gun2 = document.getElementById('gun2');

gun1.onclick = (e) => {
  e.preventDefault();
  document.callRPC('PLAYER_SELECT_GUN1');
};

gun2.onclick = (e) => {
  e.preventDefault();
  document.callRPC('PLAYER_SELECT_GUN2');
};
