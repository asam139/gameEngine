//
// Created by Saul Moreno Abril on 04/02/2018.
//

#ifndef GAMEENGINE_SCENEGRAPH_H
#define GAMEENGINE_SCENEGRAPH_H

#include "Camera.h"
#include "GameObject.h"

class SceneGraph {
public:
    SceneGraph(std::shared_ptr<GameObject> root);
    ~SceneGraph();

    GameObject* getRoot();

    void update(float deltaTime);
private:
    SceneGraph(){};

    std::shared_ptr<GameObject> _root;
};


#endif //GAMEENGINE_SCENEGRAPH_H
