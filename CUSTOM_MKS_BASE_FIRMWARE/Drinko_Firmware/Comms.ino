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

    else{
      Serial.println("Descriptor not supported");
    }
}
}
