#include "states.h"

states Arnold;
 
void setup() {
  Arnold.setup();
}

void loop() {
  Arnold.getTime();
  Arnold.changeState(actionNumber);
}
