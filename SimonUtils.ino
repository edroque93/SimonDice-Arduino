// Simon Utils
const int delta_time = 500;

void simon_setup() {
  const int delta_time = 150; // Override

  pinMode(led_up, OUTPUT);
  pinMode(led_down, OUTPUT);
  pinMode(led_left, OUTPUT);
  pinMode(led_right, OUTPUT);

  pinMode(button_up, INPUT);
  pinMode(button_down, INPUT);
  pinMode(button_left, INPUT);
  pinMode(button_right, INPUT);

  pinMode(speaker, OUTPUT);
  pinMode(reset, OUTPUT);

  digitalWrite(reset, HIGH);

  // Visual...

  for (int i = 0; i < 3; i++) {
    digitalWrite(led_up, HIGH);
    digitalWrite(led_down, HIGH);
    digitalWrite(led_left, HIGH);
    digitalWrite(led_right, HIGH);

    delay(delta_time);

    digitalWrite(led_up, LOW);
    digitalWrite(led_down, LOW);
    digitalWrite(led_left, LOW);
    digitalWrite(led_right, LOW);

    tone(speaker, 220);    
    delay(delta_time);
    noTone(speaker);
  }

  digitalWrite(led_up, HIGH);
  tone(speaker, 220);
  delay(delta_time);
  digitalWrite(led_up, LOW);

  digitalWrite(led_left, HIGH);
  tone(speaker, 240);
  delay(delta_time);
  digitalWrite(led_left, LOW);

  digitalWrite(led_down, HIGH);
  tone(speaker, 260);
  delay(delta_time);
  digitalWrite(led_down, LOW);

  digitalWrite(led_right, HIGH);
  tone(speaker, 280);
  delay(delta_time);
  digitalWrite(led_right, LOW);

  digitalWrite(led_up, HIGH);
  tone(speaker, 300);
  delay(delta_time);
  digitalWrite(led_up, LOW);

  // Return :D

  digitalWrite(led_right, HIGH);
  tone(speaker, 280);
  delay(delta_time);
  digitalWrite(led_right, LOW);

  digitalWrite(led_down, HIGH);
  tone(speaker, 260);
  delay(delta_time);
  digitalWrite(led_down, LOW);

  digitalWrite(led_left, HIGH);
  tone(speaker, 240);
  delay(delta_time);
  digitalWrite(led_left, LOW);

  digitalWrite(led_up, HIGH);
  tone(speaker, 220);
  delay(delta_time);
  digitalWrite(led_up, LOW);

  noTone(speaker);
}

void simon_play() {
  for (int i = 0; i < simon_size; i++) {
    switch(simon_dice[i]) { // OPT SWITCH
    case 0:
      digitalWrite(led_up, HIGH);
      delay(delta_time);
      digitalWrite(led_up, LOW);
      break;
    case 1:
      digitalWrite(led_down, HIGH);
      delay(delta_time);
      digitalWrite(led_down, LOW);
      break;
    case 2:
      digitalWrite(led_left, HIGH);
      delay(delta_time);
      digitalWrite(led_left, LOW);
      break;
    case 3:
      digitalWrite(led_right, HIGH);
      delay(delta_time);
      digitalWrite(led_right, LOW);
      break;
    }

    delay(delta_time);
  }
}

void simon_get() {
  byte rand = random(4);

  switch(rand) { // OPT SWITCH
  case 0:
    digitalWrite(led_up, HIGH);
    delay(delta_time);
    digitalWrite(led_up, LOW);
    break;
  case 1:
    digitalWrite(led_down, HIGH);
    delay(delta_time);
    digitalWrite(led_down, LOW);
    break;
  case 2:
    digitalWrite(led_left, HIGH);
    delay(delta_time);
    digitalWrite(led_left, LOW);
    break;
  case 3:
    digitalWrite(led_right, HIGH);
    delay(delta_time);
    digitalWrite(led_right, LOW);
    break;
  }

  simon_dice[simon_size++] = rand;
  simon_dice = (byte*) realloc(simon_dice, simon_size + sizeof(byte));
}

int simon_listen() {
  if (digitalRead(button_up)) {
    while(digitalRead(button_up));
    beep();
    return 0;
  } 
  else if (digitalRead(button_down)) {
    while(digitalRead(button_down));
    beep();
    return 1;
  } 
  else if (digitalRead(button_left)) {
    while(digitalRead(button_left));
    beep();
    return 2;
  } 
  else if (digitalRead(button_right)) {
    while(digitalRead(button_right));
    beep();
    return 3;
  }

  return -1;
}

void simon_success() {
  tone(speaker, 220, 100);
  delay(100);
  tone(speaker, 320, 100);
  delay(100); 
}

void simon_lose() {
  tone(speaker, 320, 100);
  delay(100);
  tone(speaker, 220, 100);
  delay(100); 

  digitalWrite(led_up, HIGH);
  digitalWrite(led_down, HIGH);
  digitalWrite(led_left, HIGH);
  digitalWrite(led_right, HIGH);
  delay(delta_time);
  
  digitalWrite(led_up, LOW);
  delay(delta_time);
  digitalWrite(led_down, LOW);
  delay(delta_time);
  digitalWrite(led_left, LOW);
  delay(delta_time);
  digitalWrite(led_right, LOW);
  delay(delta_time);

  Serial.print("Has perdido con ");
  Serial.print(simon_size -1);
  Serial.println(" puntos");

  // So the message is received...  
  delay(500);

  // Kill me
  digitalWrite(reset, LOW);
}

void beep() {
  tone(speaker, 300);
  delay(50);
  noTone(speaker);
  delay(50);
}
