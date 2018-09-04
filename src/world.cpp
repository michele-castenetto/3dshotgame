#include "world.h"



ofxAssimpModelLoader World::palmtree1Model;
ofxAssimpModelLoader World::palmtree2Model;



World::World() {};


void World::loadModel() {
	palmtree1Model.loadModel("meshes/palmtree/palmtree1.obj");
	palmtree1Model.setRotation(0, 180, 1, 0, 0);
	palmtree1Model.setScale(0.05, 0.05, 0.05);
	palmtree2Model.loadModel("meshes/palmtree/palmtree2.obj");
	palmtree2Model.setRotation(0, 180, 1, 0, 0);
	palmtree2Model.setScale(0.05, 0.05, 0.05);
};


void World::update() {

};


void World::draw() {

	ofPushMatrix();

	ofTranslate(0, -GROUND_HEIGHT, 0);

	// grass terrain 1
	ofPushMatrix();
	drawBox(ofPoint(WORLD_DIMENSIONS.x, GROUND_HEIGHT, GROUND_DEPTH), GRASS_COLOR);
	ofPopMatrix();

	// grass terrain 2
	ofPushMatrix();
	ofTranslate(0, 0, WORLD_DIMENSIONS.z - GROUND_DEPTH);
	drawBox(ofPoint(WORLD_DIMENSIONS.x, GROUND_HEIGHT, GROUND_DEPTH), GRASS_COLOR);
	ofPopMatrix();

	// sand terrain
	ofPushMatrix();
	ofTranslate(0, -3, WORLD_DIMENSIONS.z - 2 * GROUND_DEPTH);
	drawBox(ofPoint(WORLD_DIMENSIONS.x, GROUND_HEIGHT, GROUND_DEPTH), SAND_COLOR);
	ofPopMatrix();


	ofPushMatrix();
	ofTranslate(0, -3, GROUND_DEPTH + 0.1);

	ofPoint dimensions = ofPoint(WORLD_DIMENSIONS.x, GROUND_HEIGHT, WORLD_DIMENSIONS.z - 3 * GROUND_DEPTH - 0.2);
	ofPoint resolution = ofPoint(10, 1, 10);

	ofPushMatrix();
	ofTranslate(dimensions.x / 2, dimensions.y / 2, dimensions.z / 2);

	ofPlanePrimitive plane;
	plane.set(WORLD_DIMENSIONS.x, WORLD_DIMENSIONS.z - 3 * GROUND_DEPTH - 0.2);
	plane.setResolution(40, 40);
	plane.rotate(90, 1, 0, 0);
	plane.setPosition(0, dimensions.y / 2, 0);


	// ##CODE da esempio openframeworks modelNoiseExample
	float liquidness = 5;
	float amplitude = 3;
	float speedDampen = 5;
	vector<ofVec3f>& verts = plane.getMesh().getVertices();
	for (unsigned int i = 0; i < verts.size(); i++) {
		verts[i].x += ofSignedNoise(verts[i].x / liquidness, verts[i].y / liquidness, verts[i].z / liquidness, ofGetElapsedTimef() / speedDampen)*amplitude;
		verts[i].y += ofSignedNoise(verts[i].z / liquidness, verts[i].x / liquidness, verts[i].y / liquidness, ofGetElapsedTimef() / speedDampen)*amplitude;
		verts[i].z += ofSignedNoise(verts[i].y / liquidness, verts[i].z / liquidness, verts[i].x / liquidness, ofGetElapsedTimef() / speedDampen)*amplitude;
	}

	ofSetColor(WATER_COLOR);
	plane.draw();


	ofBoxPrimitive box = ofBoxPrimitive(dimensions.x, dimensions.y, dimensions.z, resolution.x, resolution.y, resolution.z);
	box.setPosition(0, -1, 0);
	ofSetColor(WATER_COLOR2);
	box.draw();

	ofPopMatrix();

	ofPopMatrix();







	ofPopMatrix();


	// palms trees
	ofPushMatrix();
	for (size_t i = 0; i < 40; i++)
	{
		ofPushMatrix();
		ofTranslate(ofRandom(10, 190), 0, ofRandom(10, 30));
		ofRotate(ofRandom(0, 360), 0, 1, 0);
		if (ofRandom(1) < 0.5) {
			palmtree1Model.drawFaces();
		}
		else {
			palmtree2Model.drawFaces();
		}
		ofPopMatrix();
	}
	ofPopMatrix();

	// palms trees
	ofPushMatrix();
	ofTranslate(0, 0, 240);
	for (size_t i = 0; i < 40; i++)
	{
		ofPushMatrix();
		ofTranslate(ofRandom(10, 190), 0, ofRandom(10, 30));
		ofRotate(ofRandom(0, 360), 0, 1, 0);
		if (ofRandom(1) < 0.5) {
			palmtree1Model.drawFaces();
		}
		else {
			palmtree2Model.drawFaces();
		}
		ofPopMatrix();
	}
	ofPopMatrix();
};

bool World::isPointInsideWorld(ofPoint point) {

	ofPoint world_min = ofPoint(0, 0, 0);
	ofPoint world_max = ofPoint(200, 100, 280);

	return point.x >= world_min.x &&
		point.x <= world_max.x &&
		point.y >= world_min.y &&
		point.y <= world_max.y &&
		point.z >= world_min.z &&
		point.z <= world_max.z;
};



