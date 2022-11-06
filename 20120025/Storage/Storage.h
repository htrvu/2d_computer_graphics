#pragma once
#include "../Shape/index.h"
#include <unordered_map>
using namespace std;

class Storage {
private:
    unordered_map<int, Shape*> shapeMap;
    int maxLayer;

public:
    void clear() {
        for (auto it = shapeMap.begin(); it != shapeMap.end(); it++) {
            if (it->second != nullptr) {
                delete it->second;
            }
        }
        shapeMap.clear();
    }

public:
    Storage() {
        maxLayer = -1;
    }

    ~Storage() {
        clear();
    }

public:
    void addShape(Shape* shape) {
        int layer = shape->getShapeLayer();
        shapeMap[layer] = shape;
        maxLayer = max(maxLayer, layer);
    }

    void removeShape(int layer) {
        if (shapeMap.find(layer) != shapeMap.end()) {
            delete shapeMap[layer];
            shapeMap.erase(layer);
        }
    }

    Shape* getShape(int layer) {
        if (shapeMap.find(layer) != shapeMap.end()) {
            return shapeMap[layer];
        }
        return nullptr;
    }

    Shape* getLastShape() {
        return shapeMap[maxLayer];
    }

public:
    void draw(Canvas& canvas) {
        for (int i = 1; i <= maxLayer; i++) {
            if (shapeMap.find(i) != shapeMap.end()) {
                shapeMap[i]->draw(canvas);
            }
        }
    }
};