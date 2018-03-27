

void moveTo(int MOVEX, int MOVEY){ // handels ALL interfacing with stepper drivers
    int XPROGRESS = 0;
    int YPROGRESS = 0;

    digitalWrite(X_ENABLE_PIN,LOW); // enable X stepper driver
    digitalWrite(Y_ENABLE_PIN,LOW);//enable Y stepper driver

    if(MOVEX < 0){ // true if we want a negative move
        digitalWrite(X_DIR_PIN,LOW);
    }

    else{ // if we arent doing a negative move  set to positive
        digitalWrite(X_DIR_PIN,HIGH);
    }

    if(MOVEY < 0){ //true if we want a negative move
        digitalWrite(Y_DIR_PIN,LOW);
    }

    else{// if we arent doing a negative move  set to positive
        digitalWrite(Y_DIR_PIN,HIGH);
    }



    while( XPROGRESS != MOVEX  && YPROGRESS != MOVEY){ // move both steppers similtaniously 
        digitalWrite(X_STEP_PIN,HIGH);
        digitalWrite(Y_STEP_PIN,HIGH);
        delayMicroseconds(50);
        digitalWrite(X_STEP_PIN,LOW);
        digitalWrite(Y_STEP_PIN,LOW);
        XPROGRESS++;
        YPROGRESS++;
    }
    


    while( XPROGRESS != MOVEX ){ // move x stepper only
        digitalWrite(X_STEP_PIN,HIGH);
        delayMicroseconds(50);
        digitalWrite(X_STEP_PIN,LOW);
        XPROGRESS++;
    }


    while(YPROGRESS != MOVEY){ // Move Y stepper only
        digitalWrite(Y_STEP_PIN,HIGH);
        delayMicroseconds(50);
        digitalWrite(Y_STEP_PIN,LOW);
        YPROGRESS++;

    }

    //we are done so disable steppers olding position is not important on this robot
    digitalWrite(X_ENABLE_PIN,HIGH);
    digitalWrite(Y_ENABLE_PIN,HIGH);

    //reset move buffer
    x = 0;
    y = 0;



}
