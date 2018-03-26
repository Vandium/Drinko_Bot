void checkSerial(){
     while (Serial.available() > 0) {
    descriptor = Serial.readStringUntil(' ');
    if (descriptor == "G1") { //G1 describes a movemant given x and y coordinates
      X_MOVE = Serial.readStringUntil(' ');
      X_MOVE.remove(0,1);//removes the paramater from the integer in the future we should check what paramater it was
      Y_MOVE = Serial.readStringUntil(' ');
      Y_MOVE.remove(0,1);//removes the paramater from the integer in the future we should check what paramater it was

      x = atoi(X_MOVE);
      y =  atoi(Y_MOVE);
      
      Serial.println(X_MOVE);
      Serial.println(Y_MOVE);


    }

    else{
      Serial.println("Descriptor not supported");
    }
}
}