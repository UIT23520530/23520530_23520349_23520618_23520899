#include <SFML/Audio/Sound.hpp>
#include <states/game_state.hpp>
#include <states/state.hpp>

//Ơi ông Hoàng, cái class GameState nhớ thêm hàm loadSounds() vào nhé
this->loadSounds();

void GameState::loadSounds()
{
  //Snake eat
  this->state_sound_1.loadFromFile(....);
  this->snake_eat.setBuffer(this->state_sound_1);

  //Snake looses
  this->state_sound_2.loadFromFile(....);
  this->snake_looses.setBuffer(this->state_sound_2);
}
