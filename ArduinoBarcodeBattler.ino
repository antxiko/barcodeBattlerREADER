
#define barcodePIN 9      //the pin thats read de Barcode Exp. Port.

int recibido;             //receibed data variable, if 1 goes to read the churro
int churro[205];          //the lengt of the barcode bit stream + 5 more bits

void setup() {
    pinMode(barcodePIN, INPUT_PULLUP);   //Barcode PIN as INPUT whith internal pull up resistor
    Serial.begin(9600);                  //Start the serial
}

void loop() {
    leerEntrada();                       //Whe read the arduino ext port.
}

void leerEntrada(){
  churro[0] = 0;                            //first bit of the churro is always 0
    int anterior = 1;                       //if last bit is 1 we can start reading
    int recibido = digitalRead(barcodePIN); //read again de Barcode Exp. Port. 
    if (anterior != recibido) {             //If value changues, go and try reading the churro
      delayMicroseconds(840);               //We wait 840 micros, waiting for the next bit
      leerChurro();                         //Calls churro reading function
      imprimirChurro();                     //Print the bit stream info, BINARI & ASCII
    }
  
}

void leerChurro(){                          //This function reads all the 205 bits of the churro bit stream

    for (int i = 1; i < 205; i++)
      {
      recibido = digitalRead(barcodePIN);
      churro[i] = recibido;
      delayMicroseconds(835);     
    }
}

void imprimirChurro(){                      //This function prints the bit stream in binary and then in ASCII
    Serial.println("Esto es lo que hemos leido desde el Barcode");
  for (int c=0; c<205;c++)
    {
    Serial.print(churro[c]);
    }
    Serial.println();
    Serial.println("Esto es la info de la carta en ASCII");
    for (int a = 1; a < 191; a=a+10)
      {
        imprimirAscii(a);
      }
    Serial.println();
}

void imprimirAscii(int bitChurro){        //This function puts the binary value of the bit stream bits to byte "caracter"
  byte caracter = 0;                      //and then prints it as ASCII Character
  for (int o = 0; o < 8; o++){
    bitWrite(caracter,o,churro[bitChurro+o]);
  }
  Serial.print(char(caracter));
}
