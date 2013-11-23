//////////////////
///// LIGHTS /////
// All light related functions go here.

// Flashes the lights on the light sensors //
void FlashLights(int times, int delay)
{
	for(int i=0; i<times; i++)
	{
		LSsetInactive(lightRight);
	  LSsetInactive(lightLeft);
		wait1Msec(delay);
	  LSsetActive(lightRight);
  	LSsetActive(lightLeft);
		wait1Msec(delay);
	}
}
