//
// Created by Saul Moreno Abril on 04/02/2018.
//

#ifndef GAMEENGINE_SCENEGRAPH_H
#define GAMEENGINE_SCENEGRAPH_H

#include "Camera.h"
#include "GameObject.h"

class SceneGraph {
public:
    SceneGraph(GameObject* r);
    ~SceneGraph();

    GameObject* root;

private:
    SceneGraph(){};
};


#endif //GAMEENGINE_SCENEGRAPH_H
