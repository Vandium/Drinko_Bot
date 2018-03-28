void checkSerial(){
     while (Serial.available() > 0) {
    Descriptor = Serial.readStringUntil(' ');
    if (Descriptor == "G1") { //G1 describes a movemant given x and y coordinates
      X_MOVE = Serial.readStringUntil(' ');
      X_MOVE.remove(0,1);//removes the paramater from the integer in the future we should check what paramater it was
      Y_MOVE = Serial.readStringUntil(' ');
      Y_MOVE.remove(0,1);//removes the paramater from the integer in the future we should check what paramater it was
    
    

      x = X_MOVE.toInt();
      y = Y_MOVE.toInt();
      
      Serial.println(X_MOVE);
      Serial.println(Y_MOVE);


    }

    else if (Descriptor == "M400"){
      SR = Serial.readStringUntil(' '); // reads in the first value which should be for the red value
      SG = Serial.readStringUntil(' ');
      SB = Serial.readStringUntil(' ');

      SR.remove(0,1);
      SG.remove(0,1);
      SG.remove(0,1);

      CAM_R = SR.toInt();
      CAM_G = SG.toInt();
      CAM_B = SB.toInt();

      setAllColor(CAM_R,CAM_G,CAM_B);
      
    } // Cam light Descriptor

    else{
      Serial.println("Descriptor not supported");
    }
}
}
