#pragma once
const double USER_MOVE_SPEED = 11;
const double USER_ROTATE_SPEED = 0.05; // [0, 2PI)

const unsigned int WINDOW_WIDTH  = 1280;
const unsigned int WINDOW_HEIGHT = 720;

const int REAL_WIDTH = 1280 / 4;
const int REAL_HEIGHT = 720 / 4;

const double VERTICAL_FOV = 90; //[0, 360] 
const double HORIZONTAL_FOV = 90; //[0, 360] 

// Don't change it
const double PI = 3.1415926;
const double ACCURACY = 1e-5;

#pragma comment(linker, "/STACK:5120000000")

const int RAYS_LENGTH = 1000;