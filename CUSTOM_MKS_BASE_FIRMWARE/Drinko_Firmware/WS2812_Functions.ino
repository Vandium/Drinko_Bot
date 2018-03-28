

void setAllColor(int RED,int GREEN,int BLUE){

for(int i=0;i<CAM_LED_NUM;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    CamLight.setPixelColor(i, CamLight.Color(RED,GREEN,BLUE)); // Moderately bright green color.
  }

  CamLight.show(); // This sends the updated pixel color to the hardware.

}// setAllColor END