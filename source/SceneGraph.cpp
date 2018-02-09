//
// Created by Saul Moreno Abril on 04/02/2018.
//

#include "SceneGraph.h"

#include <queue>
#include <iostream>

SceneGraph::SceneGraph(GameObject *r) {
    root = r;
}

SceneGraph::~SceneGraph() {

}

void SceneGraph::update(float deltaTime) {
    std::queue<GameObject*> Q;
    std::vector<GameObject*> allObject;
    std::vector<std::shared_ptr<GameObject>>* children;

    Q.push(root);
    allObject.push_back(root);
    while(!Q.empty()) {
        GameObject* gO = Q.front();
        Q.pop();

        gO->update(deltaTime);

        children = &(gO->children);
        for (int i = 0; i < children->size(); ++i) {
            GameObject* child = (*children)[i].get();
            Q.push(child);
            allObject.push_back(child);
        }
    }
    //std::cout << "Check Collision" << std::endl;
    for(auto const& gObject0: allObject) {
        for(auto const& gObject1: allObject) {
            if (gObject0 == gObject1) continue;

            auto& boxCollider0 =  gObject0->GetComponent<BoxCollider>();
            auto& boxCollider1 =  gObject1->GetComponent<BoxCollider>();
            if (&boxCollider0 == nullptr || &boxCollider1 == nullptr) continue;

            bool collision = boxCollider0.collision(&boxCollider1);
            //std::cout << "Collision: " << collision << std::endl;
            if (collision) {
                gObject0->collide(&boxCollider1);
                gObject1->collide(&boxCollider0);
            }
        }
    }
}

