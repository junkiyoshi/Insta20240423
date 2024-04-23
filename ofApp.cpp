#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(3);
	ofEnableDepthTest();

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 50, true, true, true);
	this->word = "ABCDEFG";
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	ofSeedRandom(39);
	for (int x = -500; x <= 450; x += 50) {

		for (int y = -400; y <= 450; y += 50) {

			auto location = glm::vec3(x, y, 100);
			int word_index = ofMap(ofNoise(location.x * 0.05, location.y * 0.05, ofGetFrameNum() * 0.001), 0, 1, 0, this->word.size());

			ofPath chara_path = this->font.getCharacterAsPoints(this->word[word_index], true, false);
			vector<ofPolyline> outline = chara_path.getOutline();

			ofFill();
			ofSetColor(239);
			ofBeginShape();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				ofNextContour(true);

				outline[outline_index] = outline[outline_index].getResampledByCount(50);
				auto vertices = outline[outline_index].getVertices();
				for (auto& vertex : vertices) {

					glm::vec3 v = location + vertex;
					auto noise_param = ((int)glm::length(v) / 100) * 100 * 0.0015;
					auto rotate_deg = ofMap(ofNoise(noise_param - ofGetFrameNum() * 0.035), 0, 1, -120, 120);
					auto rotation = glm::rotate(glm::mat4(), rotate_deg * (float)DEG_TO_RAD, glm::vec3(1, 1, 1));
					v = glm::vec4(v, 0) * rotation;
					ofVertex(v);
				}
			}
			ofEndShape(true);

			ofNoFill();
			ofSetColor(39);
			ofBeginShape();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				ofNextContour(true);

				outline[outline_index] = outline[outline_index].getResampledByCount(50);
				auto vertices = outline[outline_index].getVertices();
				for (auto& vertex : vertices) {

					glm::vec3 v = location + vertex;
					auto noise_param = ((int)glm::length(v) / 100) * 100 * 0.0015;
					auto rotate_deg = ofMap(ofNoise(noise_param - ofGetFrameNum() * 0.035), 0, 1, -120, 120);
					auto rotation = glm::rotate(glm::mat4(), rotate_deg * (float)DEG_TO_RAD, glm::vec3(1, 1, 1));
					v = glm::vec4(v, 0) * rotation;
					ofVertex(v);
				}
			}
			ofEndShape(true);
		}
	}

	/*
	int start = 50;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}