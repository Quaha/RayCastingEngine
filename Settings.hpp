#pragma once
const float USER_MOVE_SPEED = 11;
const float USER_ROTATE_SPEED = 0.05f; // [0, 2PI)

const unsigned int WINDOW_WIDTH  = 1280;
const unsigned int WINDOW_HEIGHT = 720;

const int REAL_WIDTH = 1280 / 4;
const int REAL_HEIGHT = 720 / 4;

const float VERTICAL_FOV = 90.0f; //[0, 360] 
const float HORIZONTAL_FOV = 90.0f; //[0, 360] 

// Don't change it
const float PI = 3.1415926f;
const float ACCURACY = 5.0f;

#pragma comment(linker, "/STACK:5120000000")

const int RAYS_LENGTH = 1000;