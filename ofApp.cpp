#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->frame.clear();
	for (int i = 0; i < 35; i++) {

		auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
		for (int len = 0; len < 50; len++) {

			auto vertex = glm::vec3(
				ofMap(ofNoise(noise_seed.x, (ofGetFrameNum() + len) * 0.008), 0, 1, -200, 200),
				ofMap(ofNoise(noise_seed.y, (ofGetFrameNum() + len) * 0.008), 0, 1, -200, 200),
				ofMap(ofNoise(noise_seed.z, (ofGetFrameNum() + len) * 0.008), 0, 1, -200, 200));
			vertex = glm::normalize(vertex) * 200;
			this->frame.addVertex(vertex);
		}
	}

	for (int i = 0; i < this->frame.getNumVertices(); i++) {

		for (int k = i + 1; k < this->frame.getNumVertices(); k++) {

			auto d = glm::distance(this->frame.getVertex(i), this->frame.getVertex(k));
			if (d < 30) {

				this->frame.addIndex(i);
				this->frame.addIndex(k);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.5);

	this->frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}