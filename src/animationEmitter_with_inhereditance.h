#pragma once

#include "ofMain.h"



// ##TODO 
// non funziona perché nell'animationEmitter al momento del 
// check sul metodo isRunning va in errore forse per il delete dell'iteratore


//	esemio di utilizzo
//	//ExplosionAnimation* animation = new ExplosionAnimation();
//	//animation->position = ofPoint(100, 0, 100);
//	//animationEmitter.addAnimation(animation);



class Animation {

public:

	ofPoint position;
	bool running = true;

	Animation() {};
	//Animation(ofPoint p) { position = p; };
	
	virtual bool isRunning() {
		return running;
	}
	
	virtual void update() {
		
	}

	virtual void draw() {
		
	}

};



class ExplosionAnimation : public Animation {

public:
	
	float radius = 3;
	float MAX_RADIUS = 4;
	float ANIMATION_SPEED = 0.2;
	
	ofPoint position;
	bool running = true;

	ExplosionAnimation() {};
	//ExplosionAnimation(ofPoint p) { position = p; };

	virtual bool isRunning() override {
		return running;
	}

	
	virtual void update() override  {
		
		if (radius >= MAX_RADIUS)
		{
			running = false;
		}
		if (running == true)
		{
			radius += ANIMATION_SPEED;
		}
		
	}

	virtual void draw() override {

		if (running == false)
		{
			return;
		}

		//ofIcoSpherePrimitive sphere;
		ofSpherePrimitive sphere;

		ofPushMatrix();
			//ofTranslate(position + ofPoint(0, -3, 0) + ofPoint(10.5, 0, -5));
			ofTranslate(position);

			ofSetColor(ofColor(255, 255, 10, 100));
			sphere.setRadius(radius / 3);
			sphere.draw();

			ofSetColor(ofColor(255, 140, 0, 100));
			sphere.setRadius(radius / 2);
			sphere.draw();

			ofSetColor(ofColor(255, 10, 10, 100));
			sphere.setRadius(radius);
			sphere.draw();

		ofPopMatrix();
		
	}

};



class WaterHoleAnimation : public Animation {

public:

	float radius = 3;
	float MAX_RADIUS = 8;
	float ANIMATION_SPEED = 0.2;

	
	void update() {

		if (radius >= MAX_RADIUS)
		{
			running = false;
		}
		if (running == true)
		{
			radius += ANIMATION_SPEED;
		}

	}

	void draw() {

		if (running == false)
		{
			return;
		}

		//ofIcoSpherePrimitive sphere;
		ofSpherePrimitive sphere;

		ofPushMatrix();
			//ofTranslate(animation_water_point + ofPoint(0, -3, 0));
			ofTranslate(position);

			ofSetColor(ofColor(30, 144, 255, 100));
			sphere.setRadius(radius / 3);
			sphere.draw();

			ofSetColor(ofColor(0, 191, 255, 100));
			sphere.setRadius(radius / 1.6);
			sphere.draw();

			ofSetColor(ofColor(173, 216, 230, 100));
			sphere.setRadius(radius);
			sphere.draw();

		ofPopMatrix();

	}

};



class AnimationEmitter {

public:

	vector<Animation*> animations;
	

	AnimationEmitter() {};


	void addAnimation(Animation* a) {
		animations.push_back(a);
	}
	

	void setup() {}

	void update() {

		// ##OLD
		//for (size_t i = 0; i < animations.size(); i++)
		//{
		//	animations[i].update();
		//	if (animations[i].running == false)
		//	{
		//		animations.erase(animations.begin() + i);
		//	}
		//}
		
		vector<Animation*>::iterator it;
		for (it = animations.begin(); it < animations.end(); it++) {
			(*it)->update();
			if ((*it)->isRunning() == false)
			{
				delete *it;
				animations.erase(it);
			}
		}
		
	}

	void draw() {
		// ##OLD		
		//for (size_t i = 0; i < animations.size(); i++)
		//{
		//	animations[i].draw();
		//}

		vector<Animation*>::iterator it;
		for (it = animations.begin(); it < animations.end(); it++) {
			(*it)->draw();
		}


	}

};