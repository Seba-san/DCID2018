
#define Rst A0 // al Pin 2 integrado (Reset rampa)
#define Load A1 // al Pin 5 integrado
#define Vref A7 // En este pin hay ponerlo en V+ y a La tension de salida deseada // Pin 37 integrado
#define Sal_comp A6 // este es el posible PWM, esta es la señal que hay que integrar // Pin 36 integrado
#define Clk A2 //Pin 3 del integrado (Clock)
#define Prst A3 // al Pin 6 del integrado (reset_GRAL)
#define VDAC1 A4 // Pin 39 integrado
#define VDAC2 A5 // Pin 40 integrado
// El pin 38 (in_neg) DEBE estar conectado con Vout1 o Vout2 del DAC (pines 40 y 39) $.$ cierto?
const int BLSB=2 , BMSB=11; // Lectura de los pines del sumador // Pines 7 a 16 del integrado (entrada sumador) // Pines 25 al 34 del integrado (salida sumador) entrada DAC. 
const float cota=0.01; // supuesto $.$ valor con el cual se concidera  0 la integral del error
int Tclk=500; // delay del clock en microsegundos
float Val_vref; // Valor analogico de la referencia
float Integral=0,error=0;
float Val_comp; // valor analogico de la salida de referencia
float Val_VDAC1=0,Val_VDAC2=0;
int Bits[10];
float Val_bits;
void setup() {

Serial.begin(9600);
  // Configuro los puertos
  
  pinMode(Vref,INPUT);
  pinMode(Sal_comp,INPUT);
  pinMode(Rst,OUTPUT);
  pinMode(Load,OUTPUT);
  pinMode(Clk,OUTPUT);
  pinMode(Prst,OUTPUT);
  pinMode(VDAC1,INPUT);
  pinMode(VDAC2,INPUT);

  for (int i=BLSB;i<BMSB+1;i++){
     pinMode(i,INPUT);
    }

digitalWrite(Rst,LOW);
digitalWrite(Load,LOW);
digitalWrite(Clk,LOW);
clk_uni();
rst_GRAL();
rst_Rampa();
clk_uni();
 // 
Serial.println("Iniciando");
}

void loop() {
  // Leo todas las entradas
Val_vref=analogRead(Vref);
Val_comp=analogRead(Sal_comp);
Val_VDAC1=analogRead(VDAC1);
Val_VDAC2=analogRead(VDAC2);
adder(); // Actualiza el valor de los bits
// Calculo la integral del error
error=Val_vref-Val_comp;
Integral+=error;
// Si se cumplen las siguientes condiciones se levantan las banderas y luego se ejecuta el clock
if (abs(Val_vref-Val_VDAC1)<cota){Load_();}
if (abs(Integral)<cota){rst_Rampa();}
Serial.print("vref ");
Serial.print(Val_vref);
Serial.print(" Sal_compa ");
Serial.print(Val_comp);
Serial.print(" error ");
Serial.print(error);
Serial.print(" Integral ");
Serial.print(Integral);
Serial.print(" Val_VDAC2 ");
Serial.print(Val_VDAC2);
Serial.print(" sumador ");
Serial.println(Val_bits);
clk_uni();
//delay(1000);

}


void clk_uni(void){
  digitalWrite(Clk,HIGH);
  delayMicroseconds(Tclk);
  digitalWrite(Clk,LOW);
  delayMicroseconds(Tclk);
  digitalWrite(Rst,LOW);
  digitalWrite(Load,LOW);
  }


  void rst_GRAL(void){
// Reinicio el dispositivo (no se como se reinicia) $.$
 delay(1000);
 digitalWrite(Prst,LOW);
 clk_uni();
 delay(1000);
 digitalWrite(Prst,HIGH);
 clk_uni();
 delay(1000);
 digitalWrite(Prst,LOW);
 clk_uni();   
 Integral=0; 
    }
    
  void rst_Rampa(void){
    digitalWrite(Rst,HIGH);   
    Serial.println(" Reset RAMPA ");
    Integral=0;
      }
  void Load_(void){ 
    digitalWrite(Load,HIGH);        
    Serial.println(" LOAD ");
     }

  void adder(void){
    int i=0,k=0;
    // Leo entrada por entrada
      for (i=BLSB;i<BMSB+1;i++){
     if (digitalRead(i)){Bits[i]=1;}else{Bits[i]=0;} 
     //Serial.print(Bits[i]);
    }
// Lo convierto a decimal
Val_bits=0;
 for (i=0;i<9+1;i++){  
    Val_bits+=Bits[i]*pow(2,i);
    } 
   //Val_bits=dd;
  }
