let healthBar = document.getElementById('progress_top');
let enemyHealthBar = document.getElementById('e_progress_top');

function UI_RPC(command, ...args) {
  switch (command) {
    case 'PLAYER_HP_RESET':
      break;

    case 'ENEMY_HP_RESET':
      break;

    case 'PLAYER_HP_HIT':
      if (args instanceof Array && args.length > 0) {
        // healthBar.style.width = `${args[0]}%`;
      }
      break;

    case 'ENEMY_HP_HIT':
      if (args instanceof Array && args.length > 0) {
        // enemyHealthBar.style.width = `${args[0]}`;
      }
      break;

    case 'PLAYER_GUN_CHANGE':
      if (args instanceof Array && args.length > 0) {
        console.log('Player gun changed to: ', args[0]);
      }
      break;

    default:
      break;
  }
}
