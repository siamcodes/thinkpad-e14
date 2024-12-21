/*  Repeat,      // Play all music in sequence, and repeat.
    RepeatOne,   // Repeat current sound.
    OneOff,      // Play sound file and stop.
    Random,      // Play random sound file.
    RepeatDir,   // Repeat current directory.
    RandomDir,   // Play random sound file in current folder.
    SequenceDir, // Play all sound files in current folder in sequence, and stop.
    Sequence     // Play all sound files on device in sequence, and stop.*/
#include <Arduino.h>
#include "DYPlayerArduino.h"

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Initialise the player, it defaults to using Serial.
DY::Player player;

int b1,b2,b3,b4,i=0;
int ply = 2;
int mod = 3;
int prv = 4;
int nxt = 5;
int bmode =0;
int vol=15;
char *path[] = {"train.wav",
                "bird.wav",
                "dog.wav",
                "whistle.wav",
                "iseeyou.mp3",
                "kitty.wav",
                "bente2x.mp3",
                "hulogna.mp3",
                "fart.wav",
                "bente2x.wav",
                "hulogna.wav",
                "sword.wav"};
                
size_t pathsize = sizeof ( path) / sizeof ( path[0]);

void setup() {
  pinMode(ply,INPUT_PULLUP);
  pinMode(mod,INPUT_PULLUP);
  pinMode(prv,INPUT_PULLUP);
  pinMode(nxt,INPUT_PULLUP);
  player.begin();
  player.setVolume(vol);//Volume (max =30)
  Serial.begin(9600);
  lcd.begin();//init();
  lcdprint("DY-HV20T","Voice Module");
  player.setCycleMode(DY::PlayMode::OneOff);
}

void loop() {
  b1 =digitalRead(ply);
  b2 =digitalRead(mod);
  b3 =digitalRead(prv);
  b4 =digitalRead(nxt);
  int volume  = map(vol,0,30,0,100);
  String str;
  str = "/";
  str += path[i];
  if (b1==0){//play/select
    if (bmode == 2){
      player.setCycleMode(DY::PlayMode::Repeat); // Play all and repeat.
      player.play();
    }else if (bmode == 3){
      player.setCycleMode(DY::PlayMode::RepeatOne);
      player.play();      
    }else{
      player.setCycleMode(DY::PlayMode::OneOff);
      player.playSpecifiedDevicePath(DY::Device::Sd,str.c_str()); 
      Serial.println(" Playing file: " + String(str));  
      lcdprint("Playing file:",str);
      delay(500);
    }
  }
  if (b4==0){
    if (bmode == 0 || bmode == 2 || bmode == 3){//vol++
      if (vol<=29){vol++;}else{vol=30;}
      player.setVolume(vol);
      Serial.println(" volume: " + String(vol));
      lcdprint("Volume:",String(volume)+"%");
      delay(50);
    }else if (bmode == 1){//next
      if (i<pathsize-1){i++;}else{i=0;}
      Serial.println(" Sound choice: "+ String(path[i]));
      lcdprint("Sound choice:",path[i]);
      delay(500);
    } 
  }
  if (b3==0){
    if (bmode == 0 || bmode == 2 || bmode == 3){//vol--
      if (vol>=1){vol--;}else{vol=0;}
      player.setVolume(vol);
      Serial.println(" volume: " + String(vol));
      lcdprint("Volume:",String(volume)+"%");
      delay(50);
    }else if (bmode == 1){//prev
      if (i>=1){i--;}else{i=pathsize-1;}
      Serial.println(" Sound choice: " + String(path[i]));
      lcdprint("Sound choice:",path[i]);
      delay(500);
    }
    delay(100);
  }
  if (b2==0){//mode
    bmode++; 
    switch (bmode){
      case 0://adjust volume b3=decrease vol b4=increase vol
      Serial.println(" mode selected: volume adjustment");
      lcdprint("Mode Select:","Volume Adjust");
        break;
      case 1://toggle playback 1 sound (b3=prev/b4=next) b1=select
      Serial.println(" mode selected: Select Sound");
      lcdprint("Mode Select:","Select Sound");
        break;
      case 2://play all b3=decrease vol b4=increase vol
      Serial.println(" mode selected: play all sounds");
      lcdprint("Mode Select:","Play All");
        break;
      case 3://loop 1 sound b3=decrease vol b4=increase vol
      Serial.println(" mode selected: loop 1 sound");
      lcdprint("Mode Select:","Loop 1 Sound");
        break;
      default:
      bmode = -1;
        break;
    }
    delay(1000); 
  }  
}
void lcdprint(String msg1,String msg2){
  lcd.clear();
  lcd.print(msg1);
  lcd.setCursor(0,1);
  lcd.print(msg2);
}
