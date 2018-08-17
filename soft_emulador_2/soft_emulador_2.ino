
#define Rst A0 // al Pin 2 integrado (Reset rampa)
#define Load A1 // al Pin 5 integrado
#define Vref A7 // En este pin hay ponerlo en V+ y a La tension de salida deseada // Pin 37 integrado
#define Sal_comp A6 // este es el posible PWM, esta es la señal que hay que integrar // Pin 36 integrado
#define Clk A2 //Pin 3 del integrado (Clock)
#define Prst A3 // al Pin 6 del integrado (reset_GRAL)
#define VDAC1 A4 // Pin 39 integrado
#define VDAC2 A5 // Pin 40 integrado
// Pines de datos del sumador
#define a_msb 2 
#define a_lsb 11
#define s_lsb A7
#define s_msb 12

// El pin 38 (in_neg) DEBE estar conectado con Vout1 o Vout2 del DAC (pines 40 y 39) $.$ cierto?
int Entrada, Salida,Datos;
byte bitsal[]={11,10,9,8,7,6,5,4,3,2};
byte biten[]={19,18,17,16,15,14,13,12};
void setup() {

Serial.begin(9600);
  // Configuro los puertos


  for (int i=0;i<10;i++){
     pinMode(bitsal[i],OUTPUT);
    }

 
  for (int i=0;i<8;i++){
     pinMode(biten[i],INPUT);//INPUT_PULLUP
    }

pinMode(A7,INPUT);
pinMode(A6,INPUT);


Serial.println("Iniciando");

Entrada=0;
Salida=0;
}

void loop() {

  Sacar();
  Leer();
  Serial.print("Enviado: ");
  Datos=Potencia(Salida)+16384;
  Serial.print(Datos,BIN);Serial.print(" "); Serial.println(Datos-16384);
  //  Serial.println(Salida);
   Serial.print(" Leido: ");
   Serial.println(Entrada,BIN);
   delay(2000);
}


void Sacar(){
  //Pone todas las salidas en bajo
  for (int i=0;i<10;i++){
     digitalWrite(bitsal[i],LOW);
    }
  
 digitalWrite(bitsal[Salida],HIGH);
 Salida++;
 if (Salida>=10){Salida=0;}
  }

 void Leer(){
int Elbit;
Entrada=0;
  for (int i=0;i<8;i++){
     Elbit=digitalRead(biten[i]);
    // Serial.print(Elbit);
     Entrada=Entrada+Elbit*Potencia(i+2); // Los menos significativos son las entradas analogicas
    }
   //  Serial.print(" ");
  Elbit=analogRead(A7);

  if (Elbit>800){Elbit=1;}else {Elbit=0;}
    // Serial.print(Elbit);
   Entrada=Entrada+Elbit*Potencia(0); 
  // Serial.print(" ");
   Elbit=analogRead(A6);
   
  if (Elbit>800){Elbit=1;}else {Elbit=0;}
  // Serial.println(Elbit);
   Entrada=Entrada+Elbit*Potencia(1); 
    
  }

int Potencia(int a){
  int Salidass=1;
  for (int i=1;i<a+1;i++){
    Salidass=Salidass*2;
    }
  return Salidass;
  }
/*
// Lo convierto a decimal
Val_bits=0;
 for (i=0;i<9+1;i++){  
    Val_bits+=Bits[i]*pow(2,i);
    } 
   //Val_bits=dd;
  }
  */
