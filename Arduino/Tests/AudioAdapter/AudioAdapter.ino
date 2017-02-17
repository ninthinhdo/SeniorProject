#include <Arduino.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav2;     //xy=147,222
AudioPlaySdWav           playSdWav1;     //xy=154,137
AudioPlaySdWav           playSdWav3;     //xy=155,294
AudioInputI2S            i2s2;           //xy=155,492
AudioPlaySdWav           playSdWav4;     //xy=156,368
AudioMixer4              mixer1;         //xy=413,151
AudioMixer4              mixer2;         //xy=414,282
AudioMixer4              mixer4;         //xy=651,386
AudioMixer4              mixer5;         //xy=652,518
AudioMixer4              mixer3;         //xy=897,152
AudioAnalyzeFFT1024      fft1024_1;      //xy=1197,151
AudioOutputI2S           i2s1;           //xy=1198,482
AudioConnection          patchCord1(playSdWav2, 0, mixer1, 1);
AudioConnection          patchCord2(playSdWav2, 1, mixer2, 1);
AudioConnection          patchCord3(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord4(playSdWav1, 1, mixer2, 0);
AudioConnection          patchCord5(playSdWav3, 0, mixer1, 2);
AudioConnection          patchCord6(playSdWav3, 1, mixer2, 2);
AudioConnection          patchCord7(i2s2, 0, mixer4, 1);
AudioConnection          patchCord8(i2s2, 1, mixer5, 1);
AudioConnection          patchCord9(playSdWav4, 0, mixer1, 3);
AudioConnection          patchCord10(playSdWav4, 1, mixer2, 3);
AudioConnection          patchCord11(mixer1, 0, mixer3, 0);
AudioConnection          patchCord12(mixer1, 0, mixer4, 0);
AudioConnection          patchCord13(mixer2, 0, mixer3, 1);
AudioConnection          patchCord14(mixer2, 0, mixer5, 0);
AudioConnection          patchCord15(mixer4, 0, i2s1, 0);
AudioConnection          patchCord16(mixer4, 0, mixer3, 2);
AudioConnection          patchCord17(mixer5, 0, i2s1, 1);
AudioConnection          patchCord18(mixer5, 0, mixer3, 3);
AudioConnection          patchCord19(mixer3, fft1024_1);
// GUItool: end automatically generated code



AudioControlSGTL5000     sgtl5000_1;

// Use these with the audio adaptor board
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

// My Variables
String input;
String theme = "";
elapsedMillis elapsedTime;

// An array to hold the 16 frequency bands
float level[14];
byte pixelLevel[14];

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(30);

  sgtl5000_1.enable();
  sgtl5000_1.volume(1.0);

  // Initialize gains
  mixer1.gain(0, 0.5);
  mixer1.gain(1, 0.5);
  mixer1.gain(2, 0.5);
  mixer1.gain(3, 0.5);
  mixer2.gain(0, 0.5);
  mixer2.gain(1, 0.5);
  mixer2.gain(2, 0.5);
  mixer2.gain(3, 0.5);
  mixer3.gain(0, 0.5);
  mixer3.gain(1, 0.5);
  mixer3.gain(2, 0.5);
  mixer3.gain(3, 0.5);
  mixer4.gain(0, 0.5);
  mixer4.gain(1, 0.5);
  mixer4.gain(2, 0.5);
  mixer4.gain(3, 0.5);
  mixer5.gain(0, 0.5);
  mixer5.gain(1, 0.5);
  mixer5.gain(2, 0.5);
  mixer5.gain(3, 0.5);
  
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
 
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(Serial1.available() > 0){
    input = Serial1.readStringUntil('.');
    if(input.equals("FFT")){
      audioSpectrum();
    }
    else if(input.equals("GAME")){
      gameMode();
    }
    else{
      playSoundEffect(input + ".WAV");
    }
  }
}

void gameMode(){
  fft1024_1.processorUsageMaxReset();
  mixer3.gain(0, 0);
  mixer3.gain(1, 0);
      
  input = Serial1.readStringUntil('.');
  theme = input + ".WAV";
      
  loopThemeMusic(1);

  while(!input.equals("STOP")){
    
    if(Serial1.available() > 0){
      input = Serial1.readStringUntil('.');
      playSoundEffect(input + ".WAV");
    }
    
    // loop theme music
    if((elapsedTime % 100) == 0)
      loopThemeMusic(0);
  }

  stopSdPlayer();
}


void audioSpectrum(){
  mixer3.gain(0, 0.5);
  mixer3.gain(1, 0.5);
  Serial.println("Audio Spectrum Mode");
  
  while(!input.equals("STOP")){
    
    if(Serial1.available() > 0){
      input = Serial1.readStringUntil('.');
      playWav1(input + ".WAV");
      delay(10);
    }
    if(Serial.available() > 0){
      input = Serial.readStringUntil('.');
      playWav1(input + ".WAV");
      delay(10);
    }
    
    if (fft1024_1.available()) {
      // read the 512 FFT frequencies into 16 levels
      // music is heard in octaves, but the FFT data
      // is linear, so for the higher octaves, read
      // many FFT bins together.
      /*
      level[0] =  fft1024_1.read(0,1);
      level[1] =  fft1024_1.read(2,3);
      level[2] =  fft1024_1.read(4, 6);
      level[3] =  fft1024_1.read(7, 10);
      level[4] =  fft1024_1.read(11, 16);
      level[5] =  fft1024_1.read(17, 25);
      level[6] =  fft1024_1.read(26, 37);
      level[7] =  fft1024_1.read(38, 55);
      level[8] =  fft1024_1.read(56, 81);
      level[9] =  fft1024_1.read(82, 118);
      level[10] = fft1024_1.read(119, 171);
      level[11] = fft1024_1.read(172, 247);
      level[12] = fft1024_1.read(248, 355);
      level[13] = fft1024_1.read(356, 511);
      */
      level[0] =  fft1024_1.read(0,1);
      level[1] =  fft1024_1.read(1,4);
      level[2] =  fft1024_1.read(2, 9);
      level[3] =  fft1024_1.read(5, 13);
      level[4] =  fft1024_1.read(9, 21);
      level[5] =  fft1024_1.read(16, 32);
      level[6] =  fft1024_1.read(24, 46);
      level[7] =  fft1024_1.read(35, 68);
      level[8] =  fft1024_1.read(52, 100);
      level[9] =  fft1024_1.read(76, 145);
      level[10] = fft1024_1.read(110, 210);
      level[11] = fft1024_1.read(160, 302);
      level[12] = fft1024_1.read(200, 434);
      level[13] = fft1024_1.read(250, 511);

      for (int i=0; i<14; i++) {
        int newLevel = level[i] * 200;
        pixelLevel[i] = map(newLevel, 0, 30, 0, 19);
        //Serial.print(pixelLevel[i]);
        //Serial.print(" ");
      }
      //Serial.print(" cpu:");
      //Serial.println(AudioProcessorUsageMax());
      Serial1.write(pixelLevel,14);
      Serial1.write('X');
      delay(50);
    }
    
  }
  stopSdPlayer();
}

void playWav1(String wavFile)
{
  char fileName[sizeof(wavFile)];
  wavFile.toCharArray(fileName, sizeof(fileName));
  
  Serial.print("Playing file: ");
  Serial.println(fileName);
  playSdWav1.play(fileName);
}

void loopThemeMusic(int resetTheme)
{
  if(resetTheme == 1){
    playWav1(theme);
    delay(5);
  }
  else if(!theme.equals("")){
    if(!playSdWav1.isPlaying()){
      playWav1(theme);
      delay(5);
    } 
  }
}

void playSoundEffect(String sound)
{
  char fileName[sizeof(sound)];
  sound.toCharArray(fileName, sizeof(fileName));
  
  Serial.print("Playing file: ");
  Serial.println(fileName);

  // Select non-busy WAV player
  if(!playSdWav2.isPlaying())
    playSdWav2.play(fileName);
  else if(!playSdWav3.isPlaying())
    playSdWav3.play(fileName);
  else
    playSdWav4.play(fileName);

  // A brief delay for the library read WAV info
  delay(10);
}


void stopSdPlayer()
{
  playSdWav1.stop();
  playSdWav2.stop();
  playSdWav3.stop();
  playSdWav4.stop();
}











