
#define R1 2
#define R2 3
#define R3 4
#define R4 5
#define R5 6
#define R6 7
#define R7 8
#define R8 9

#define C1 10
#define C2 11
#define C3 12
#define C4 13
#define C5 A0
#define C6 A1
#define C7 A2
#define C8 A3

#define P1Down A4
#define P1Up A5
#define P2Down 1
#define P2Up 0


int currentColumn = 0;
 
int ballX;
int ballY;


int player1Position, player2Position;

boolean ballMovingUp = true;
boolean ballMovingLeft = true;

boolean isGameOn = true;

int shape[8][8] = {
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
};

void setup(){
  
  pinMode(P1Down, INPUT);
  pinMode(P1Up, INPUT);
  pinMode(P2Down, INPUT);
  pinMode(P2Up, INPUT);
    
   pinMode(R1, OUTPUT);
   pinMode(R2, OUTPUT);
   pinMode(R3, OUTPUT);
   pinMode(R4, OUTPUT);
   pinMode(R5, OUTPUT);
   pinMode(R6, OUTPUT);
   pinMode(R7, OUTPUT);
   pinMode(R8, OUTPUT);
   pinMode(C1, OUTPUT);
   pinMode(C2, OUTPUT);
   pinMode(C3, OUTPUT);
   pinMode(C4, OUTPUT);
   pinMode(C5, OUTPUT);
   pinMode(C6, OUTPUT);
   pinMode(C7, OUTPUT);
   pinMode(C8, OUTPUT);

  digitalWrite(R1,HIGH);
  digitalWrite(R2,HIGH);
  digitalWrite(R3,HIGH);
  digitalWrite(R4,HIGH);
  digitalWrite(R5,HIGH);
  digitalWrite(R6,HIGH);
  digitalWrite(R7,HIGH);
  digitalWrite(R8,HIGH);
  digitalWrite(C1,LOW);
  digitalWrite(C2,LOW);
  digitalWrite(C3,LOW);
  digitalWrite(C4,LOW);
  digitalWrite(C5,LOW);
  digitalWrite(C6,LOW);
  digitalWrite(C7,LOW);
  digitalWrite(C8,LOW);
  delay(350);
  ballX = 4;
  ballY = 4;
  ballMovingUp = true;
  ballMovingLeft = true;
  isGameOn = true;
}
 
void loop(){
  if(isGameOn){
    update();
    draw();
    delay(500);//0.5 second
  }
  else{ 
     ballX = 4;
     ballY = 5;
    ballMovingUp = true;
    ballMovingLeft = true;
    isGameOn = true;
  }

}

void SelectRow(int row){
  if (row==1)   digitalWrite(R1,LOW); else digitalWrite(R1,HIGH);
  if (row==2) digitalWrite(R2,LOW);   else digitalWrite(R2,HIGH);
  if (row==3) digitalWrite(R3,LOW); else digitalWrite(R3,HIGH);
  if (row==4) digitalWrite(R4,LOW); else digitalWrite(R4,HIGH);
  if (row==5)   digitalWrite(R5,LOW); else digitalWrite(R5,HIGH);
  if (row==6) digitalWrite(R6,LOW);   else digitalWrite(R6,HIGH);
  if (row==7) digitalWrite(R7,LOW); else digitalWrite(R7,HIGH);
  if (row==8) digitalWrite(R8,LOW); else digitalWrite(R8,HIGH);
}

void   Set_LED_in_Active_Row(int column, int state){
  if (column==1) digitalWrite(C1,state);   
  if (column==2) digitalWrite(C2,state); 
  if (column==3) digitalWrite(C3,state);   
  if (column==4) digitalWrite(C4,state); 
  if (column==5) digitalWrite(C5,state);   
  if (column==6) digitalWrite(C6,state); 
  if (column==7) digitalWrite(C7,state);   
  if (column==8) digitalWrite(C8,state); 
}

void gameOver(){
    isGameOn = false;
    for(int i = 2; i < 14; i++){
    digitalWrite(i, 0);
  }
  digitalWrite(A0, 0);
  digitalWrite(A1, 0);
  digitalWrite(A2, 0);
  digitalWrite(A3, 0);    
   
}

void updateBall(){
  if(ballY == 0 && shape[ballX][0] == 1){
    ballMovingLeft = false;
    
  }
  else if(ballY == 7 && shape[ballX][7] == 1){
    ballMovingLeft = true;

  }
  if(ballX == 0 && ballMovingUp == true){
    ballMovingUp = false;
    
  }
  else if(ballX == 7 && ballMovingUp == false){
    ballMovingUp = true;

  }
  if(ballMovingLeft)
    ballY--;
  else
    ballY++;
    
  if(ballY == 0)
    ballMovingLeft = false;
    
  else if (ballY == 7)
    ballMovingLeft = true;
    
  if(ballMovingUp)
    ballX--;
  else
    ballX++;

  if(ballY == 0  && shape[ballX][0] == 0){
    
    gameOver();
    
  }else if (ballY == 7 && shape[ballX][7] == 0){
    
    gameOver();
  }
}


void update(){
 
    for(int i = 0; i < 8; i++){
      for(int j = 0; j < 8; j++){
        shape[i][j] = 0;
      }
    }
 
  
  if(digitalRead(P1Down) == HIGH){
    if (player1Position + 3 < 8){
      player1Position ++;
    }
  }

  
  if(digitalRead(P1Up) == HIGH){
    if(player1Position != 0){
      player1Position --;
    }
 }  

 if(digitalRead(P2Down) == HIGH){
    if (player2Position + 3 < 8){
      player2Position ++;
    }
  }

  
  if(digitalRead(P2Up) == HIGH){
    if(player2Position != 0){
      player2Position --;
    }
}  
  for(int i = 0; i < 8; i++){
      if(i >= player1Position && i < player1Position + 3){
        shape[i][0] = 1;
      }else{
        shape[i][0] = 0;
      }
      if(i >= player2Position && i < player2Position + 3){
        shape[i][7] = 1;
      }else{
        shape[i][7] = 0;
      }
    }

    updateBall();
    shape[ballY][ballX] = 1;
}

void draw(){
    for (int j=0;j<8;j++){
    SelectRow(j+1);
      for (int i=0;i<8;i++){

        Set_LED_in_Active_Row(i+1 ,shape[j][i]);
      }
      delay(5);
    }
  }    

    

