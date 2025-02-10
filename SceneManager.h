#pragma once
#include "PlayScene.h"
#include "GameOver.h"
#include "Novice.h"

enum SCENE {
    TITLE,
    GAME,
    RESULT
};

class SceneManager {
public:
    SceneManager();
    ~SceneManager();

    void Update(char* keys, char* preKeys);

    void Draw();
private:
    SCENE currentScene_;

    PlayScene* playScene_;
    GameOver* gameOverScene_;

    int titleImage_;
};