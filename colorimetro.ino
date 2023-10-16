//bibliotecas
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Adafruit_TCS34725.h>
// switches
int caseI = 0;
int x = 0;
int btn1 = 8;
int btn1p = 0;
int btn2 = 7;
int btn2p = 0;
// led
int red = A1; 
int green = A2;
int blue = A3;
int valr, valg, valb;
int r, g, b;
//i2c
#define col 16 //Numero de colunas do display
#define lin  2 //Numero de linhas do display
#define ende  0x27 //Endereço do display
LiquidCrystal_I2C lcd(ende,col,lin); //função LiquidCrystal com I2C
//tcs34725
int ledTcs = 13;
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS  , TCS34725_GAIN_1X);
uint16_t rs, gs, bs, cs, colorTemp, lux;
//variaveis
int branco;
double absorbancia;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(ledTcs, OUTPUT);
  digitalWrite(ledTcs, LOW);
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  switch(caseI){
    case 0:{
      ledApagado();    
      while(1){
        btn1p = digitalRead(btn1);delay(200);
        btn2p = digitalRead(btn2);delay(200);
        if(btn2p == LOW){
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Primeiro ligue o");
          lcd.setCursor(0, 1);
          lcd.print("led");
        }
        if(btn1p == LOW){
          caseI = 1;
          break;
        }
      }
    }
    case 1:{
      ledVermelho();
      pegaMedida();
    }
    case 2:{
      ledAzul();
      pegaMedida();
    }
    case 3:{
      ledVerde();
      pegaMedida();
    }
    default:
    break;
 }
}
void pegaMedida(){
  while(1){
  tcs.getRawData(&rs, &gs, &bs, &cs);
  lux = tcs.calculateLux(rs, gs, bs);
  lcd.setCursor(0, 1);
  lcd.print("I = ");
  lcd.setCursor(4, 1);
  lcd.print(lux);
  delay(1000);
  btn1p = digitalRead(btn1);delay(200);
  btn2p = digitalRead(btn2);delay(200);
  if (btn2p == LOW){
    branco = lux;
    while(1){
      tcs.getRawData(&rs, &gs, &bs, &cs);
      lux = tcs.calculateLux(rs, gs, bs);
      double(absorbancia) = double(branco) / double(lux);
      lcd.setCursor(0, 1);
      lcd.print("T = ");
      lcd.setCursor(4, 1);
      lcd.print(absorbancia, 4);
      btn1p = digitalRead(btn1);delay(200);
      if(btn1p == LOW){
      break;
      }
    }
  }
  if(btn1p == LOW){
    break;
    loop();
  }
  }return;
}
void ledApagado(){
  // valores do led
  r = 0;
  g = 0;
  b = 0;
  // valores sendo convertidos
  valr = (255- r); //valores sendo convertidos
  valg = (255- g);
  valb = (255- b);
  // passando os valores para o led
  analogWrite (red, r); //saída já convertida
  analogWrite (green, g);
  analogWrite (blue, b);
  // escrita no display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Led apagado"); 
}
void ledVermelho(){
  // valores do led
  r = 255;
  g = 0;
  b = 0;
  // valores sendo convertidos
  valr = (255- r); //valores sendo convertidos
  valg = (255- g);
  valb = (255- b); 
  // passando os valores para o led
  analogWrite (red, r); //saída já convertida
  analogWrite (green, g);
  analogWrite (blue, b);
  // escrita no display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Led vermelho"); 
}
void ledVerde(){
  // valores do led
  r = 0;
  g = 255;
  b = 0;
  // valores sendo convertidos
  valr = (255- r); //valores sendo convertidos
  valg = (255- g);
  valb = (255- b); 
  // passando os valores para o led
  analogWrite (red, r); //saída já convertida
  analogWrite (green, g);
  analogWrite (blue, b);
  // escrita no display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Led verde"); 
}
void ledAzul(){
  // valores do led
  r = 0;
  g = 0;
  b = 255;
  // valores sendo convertidos
  valr = (255- r); //valores sendo convertidos
  valg = (255- g);
  valb = (255- b); 
  // passando os valores para o led
  analogWrite (red, r); //saída já convertida
  analogWrite (green, g);
  analogWrite (blue, b);
  // escrita no display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Led azul"); 
}