#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	input.set_Input(v);
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofDrawArrow(init_point.toVec3(), v.toVec3() + init_point.toVec3(), 6);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
	if (key == 'c') //key C
	{
		input.change_norm(true);
	}
	else if (key == 'x') // key X
	{
		input.change_norm(false);
	}
	else if (key == 'e')
	{
		input.angle_key = true;
		
	}
	input.set_Input(v);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == 'e')
	{
		input.angle_key = false;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	if (input.angle_key)
	{
		int diffx = x - input.last_pos_x;
		int diffy = y - input.last_pos_y;
		if (abs(diffx) > abs(diffy) + 2 && diffx != 0)
		{
			input.change_angle2(diffx > 0);

		}
		else if (abs(diffy) > abs(diffx) + 2 && diffy != 0)
		{
			input.change_angle1(diffy > 0);
		}
		input.last_pos_x = x;
		input.last_pos_y = y;
		input.set_Input(v);
	}
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (button == 0)
	{
		init_point.set(x, y, 0);
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
