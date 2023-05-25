#include "robot/subsystems/managers/pneumaticManager.hpp"
#include "robot/globals.hpp"

//Pneumatic State Fields
bool endgameState, blooperState, compressionState;

//Pneumatic Initializer
void pneumaticInit(){
    endgameState=false;
    blooperState=false;
    compressionState=false;

    topEndgame.set_value(endgameState);
    bottomEndgame.set_value(endgameState);
    blooper.set_value(blooperState);
    compression.set_value(compressionState);
}

//Pneumatic State Getters
bool getBlooperState(){
    return blooperState;
}

bool getCompressionState(){
    return compressionState;
}

bool getEndgameState(){
    return endgameState;
}

//Pneumatic State Togglers
void toggleEndgame(){
    endgameState = !endgameState;
    topEndgame.set_value(endgameState);
    bottomEndgame.set_value(endgameState);
}

void toggleBlooper(){
    blooperState = !blooperState;
    blooper.set_value(blooperState);
}

void toggleCompression(){
    compressionState = !compressionState;
    compression.set_value(compressionState);
}