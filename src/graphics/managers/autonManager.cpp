#include "main.h"

//Autonomous Manager Fields
int autonIndex;
const char* autonNames[12] = {"Autonomous 1",
                                        "Autonomous 2",
                                        "Autonomous 3",
                                        "Autonomous 4",
                                        "Autonomous 5",
                                        "Autonomous 6",
                                        "Autonomous 7",
                                        "Autonomous 8",
                                        "Autonomous 9",
                                        "Autonomous 10",
                                        "Autonomous 11",
                                        "Autonomous 12"};

const char* autonDescs[12] = {"Frelims (far roller)",
                                        "AWP",
                                        "Drelims (driver rollers)",
                                        "Do Nothing",
                                        "Do Nothing",
                                        "Do Nothing",
                                        "Do Nothing",
                                        "Do Nothing",
                                        "Do Nothing",
                                        "Do Nothing",
                                        "Do Nothing",
                                        "Do Nothing"};

//Autonomous Manager Initialization
void autonInit(){
  autonIndex=0;
}
