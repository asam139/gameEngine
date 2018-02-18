//
// Created by Saul Moreno Abril on 18/02/2018.
//

#ifndef GAMEENGINE_GAMEMANAGER_H
#define GAMEENGINE_GAMEMANAGER_H


class GameManager {
public:
    void setPause(bool pause);
    bool getPause();

    enum class GameState: unsigned int {
        Menu = 0,
        Game = 1,
        Win = 2,
        Lose = 3
    };
    GameManager::GameState getGameState();
    void setGameState(GameManager::GameState state);

    static const unsigned int maxLives = 3;
    void setLives(unsigned int lives);
    unsigned int getLives();

    void setPoints(unsigned int points);
    unsigned int getPoints();


    void resetGame();

private:
    bool _pause = false;
    GameManager::GameState _gameState = GameManager::GameState::Menu;

    unsigned int _lives = 0;
    unsigned int _points = 0;
};


#endif //GAMEENGINE_GAMEMANAGER_H
