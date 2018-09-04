#pragma once
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

#include "utils.h"


class World {
	
private:

	static ofxAssimpModelLoader palmtree1Model;
	static ofxAssimpModelLoader palmtree2Model;
	
	ofColor WATER_COLOR = ofColor(0, 0, 255, 170);
	ofColor WATER_COLOR2 = ofColor(0, 0, 255, 50);
	ofColor GRASS_COLOR = ofColor(50, 255, 50);
	ofColor SAND_COLOR = ofColor(255, 255, 20);

	ofPoint WORLD_DIMENSIONS = ofPoint(200, 100, 280);
	float GROUND_DEPTH = 40;
	float	GROUND_HEIGHT = 20;

	ofPoint WORLD_MIN = ofPoint(0, 0, 0);
	ofPoint WORLD_MAX = ofPoint(200, 100, 280);

public:
			
	World();

	static void loadModel();

	void update();
	
	void draw();

	bool isPointInsideWorld(ofPoint point);

};


