//
// Created by Saul Moreno Abril on 04/02/2018.
//

#include "SceneGraph.h"

#import <queue>


SceneGraph::SceneGraph(GameObject *r) {
    root = r;
}

SceneGraph::~SceneGraph() {

}


void SceneGraph::render() {
    breadthFirstSearch();
}


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
            GameObject* child = (*children)[i].get();
            if(gO->getTransform().dirty) {
                child->getTransform().setParentModel(model);
            }
            Q.push(child);
        }
    }
}