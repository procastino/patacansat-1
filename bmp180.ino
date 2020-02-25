#include <Wire.h>
#include <SFE_BMP180.h>

SFE_BMP180 bmp180;
double Po=1013.25;
int i=1; //definin este enteiro para que o bucle só se executase un número limitado de veces, pero chegaramos á conclusión de que era tontería, que se segue executnado igual.
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
 if (bmp180.begin())
    Serial.println("BMP180 iniciado correctamenten");
  else
  {
    Serial.println("Error al iniciar el BMP180");
    while(1); // bucle infinito
  }
  double status;
  double T,P;

  status = bmp180.startTemperature();//Inicio de lectura de temperatura: tempo de medida en milisegundos
  Serial.println(status);
  status= bmp180.startPressure(3); //Inicio de lectura de temperatura: devolve o tempo, en milisegundos, que tarda en medir tres veces a presión.
  Serial.println(status);
}

void loop() {
  // put your main code here, to run repeatedly:
  char status; //a variable estatus é dinámica, estase redefinindo continuamente
  double T,P,A;
  status = bmp180.startTemperature();//Inicio de lectura de temperatura
  if(status !=0)
    {
      delay(status); 
      status= bmp180.getTemperature(T);
      if (status !=0);
      {
        status=bmp180.startPressure(3);
        if (status !=0)
        {
          delay(status);
          status=bmp180.getPressure(P,T);
          if (status !=0)
          {
            Serial.print("Temperatura: ");
            Serial.print(T,2);
            Serial.print(" oC ; ");
            Serial.print("Presion: ");
            Serial.print(P,2);
            Serial.print(" mbar");     
            A=bmp180.altitude(P,Po);
            Serial.print("; Altitud: ");
            Serial.print(A);
            Serial.println(" metros");  
           
          }
        }
      }
    }
    delay(1000);
    i=i+1;
    if (i>100)//cando para que só faga 100 medidas e pare e non gaste batería, pero para a nosa aplicación teriamos que quitalo
    {
      while(1);
    }
    
  
}
