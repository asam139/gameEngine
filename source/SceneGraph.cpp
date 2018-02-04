//
// Created by Saul Moreno Abril on 04/02/2018.
//

#include "SceneGraph.h"

#import <queue>
#include <iostream>


SceneGraph::SceneGraph(GameObject *r) {
    root = r;
}

SceneGraph::~SceneGraph() {

}

void SceneGraph::render(Camera& camera, GameObject& lightObject) {
    glm::mat4 projection = glm::perspective(glm::radians(camera.getFOV()), (float)800 / (float)800, 0.1f, 100.f);
    glm::mat4 view = camera.getViewMatrix();
    glm::vec3 cameraPos = camera.getPosition();
    std::cout << "1" << std::endl;
    ////////////////////////////////
    // Get Light
    auto& light = lightObject.GetComponent<Light>();
    glm::vec3 lightPos = lightObject.getTransform().getPosition();

    std::cout << "1" << std::endl;
    //breadthFirstSearch();

    std::queue<GameObject*> Q;
    std::vector<std::shared_ptr<GameObject>>* children;

    Q.push(root);

    while(!Q.empty())
    {
        std::cout << "1" << std::endl;
        GameObject* gO = Q.front();
        glm::mat4 model = gO->getTransform().getModel();
        Q.pop();

        gO->display(projection, view, cameraPos, lightPos, light);

        children = &(gO->children);
        for (int i = 0; i < children->size(); ++i) {
            std::cout << "1" << std::endl;
            GameObject* child = (*children)[i].get();
            if(gO->getTransform().dirty) {
                child->getTransform().setParentModel(model);
            }
            Q.push(child);
        }
    }
}

/*
void SceneGraph::breadthFirstSearch() {
    std::queue<GameObject*> Q;
    std::vector<std::unique_ptr<GameObject>>* children;

    Q.push(root);

    while(!Q.empty())
    {

        GameObject* gO = Q.front();
        glm::mat4 model = gO->getTransform().getModel();
        Q.pop();

        children = &(gO->children);
        for (int i = 0; i < children->size(); ++i) {
            std::cout << i << std::endl;
            GameObject* child = (*children)[i].get();
            if(gO->getTransform().dirty) {
                child->getTransform().setParentModel(model);
            }
            Q.push(child);
        }
    }
}*/