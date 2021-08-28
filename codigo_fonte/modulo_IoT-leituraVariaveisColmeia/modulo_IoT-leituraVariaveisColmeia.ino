#include <OneWire.h> // sensor temperatura
#include <DallasTemperature.h> // sensor temperatura
#include <Servo.h> // servo
#include <LiquidCrystal.h> // liquid cristal.
#include <SD.h>
#include <SPI.h>


// definicao dos pinos
#define  pinoGas   A2   
#define pinoSensorMovimento 9
#define pinoSD  10

unsigned long contadorAbelha = 0;
bool s_high=0;

#define NOME_ARQUIVO_DATA_SET  "dataset.txt"

// objetos.
//OneWire oneWire(sensorTemperaturaPin); // Cria um objeto OneWire
//DallasTemperature sensor(&oneWire); // Informa a referencia da biblioteca dallas temperature para Biblioteca onewire
DeviceAddress endereco_temp; // Cria um endereco temporario da leitura do sensor
File myFile;

// variaveis diversas.
int TIME_DELAY = 100;
int UM_MINUTO = 10 * 60; 
int contadorLoopParaLeitura = 0;


void setup() {
  Serial.begin(9600);   
  setupPinos();
  
  if (SD.begin()) { 
    Serial.println("SD Card pronto para uso."); 
    myFile = SD.open(NOME_ARQUIVO_DATA_SET, FILE_WRITE); 
  } else {
    Serial.println("Falha na inicialização do SD Card.");
    return;
  }

  Serial.println("Setup config OK");  
  processaLeituraEscritaSensores();  

}

// TODO tirar todos os print de log, 
void loop() {

  if(contadorLoopParaLeitura == UM_MINUTO){
      processaLeituraEscritaSensores();
      contadorLoopParaLeitura = 0;
  }else{
     contadorLoopParaLeitura++;
  }
  
  processaContadorAbelhas();
  
  delay(TIME_DELAY);

}

void processaContadorAbelhas(){
  bool movimento = digitalRead(pinoSensorMovimento);
  if(movimento){ 
    s_high = 1;
  }

  if(!movimento && s_high){
    s_high =0;
    contadorAbelha+=1;
    Serial.println(contadorAbelha); // TODO DEPOIS TIRAR ESTE LOG.
  }
}

void processaLeituraEscritaSensores(){
    int  gas = analogRead(pinoGas);   
    String valores = criaStringValoresSensores(contadorAbelha,gas);
    escreveCartao(valores);
    Serial.println("processaLeituraEscritaSensores: " + valores);
}

// valores: contador;gas
String criaStringValoresSensores(int contador,int gas){
  String token = ";";
  String message = "";
  message.concat(String(gas));    
  message.concat(String(token));    
  message.concat(String(contador));
  message.concat(String(token));          
  return message;     
}


void escreveCartao(String valor){
  
  myFile = SD.open(NOME_ARQUIVO_DATA_SET, FILE_WRITE); 
 
  if (myFile) {     
    myFile.println(valor); 
    myFile.close();     
  }
  
}


void setupPinos(){
  pinMode(pinoGas, INPUT);
  pinMode(pinoSensorMovimento,INPUT);  
  pinMode(pinoSD, OUTPUT); 

  digitalWrite(pinoSensorMovimento,LOW); 
}



void digitalWrite(int pin, int status, String texto){
  int statusAtual = digitalRead(pin);
  if(statusAtual != status){
    digitalWrite(pin, status);   
    Serial.println(texto);
  }
}



//float leituraSensorTemperatura(){
//  float temperatura = 0;
//  sensor.requestTemperatures(); // Envia comando para realizar a conversão de temperatura
//  if (!sensor.getAddress(endereco_temp,0)) { // Encontra o endereco do sensor no barramento
//    Serial.println("SENSOR TEMPERATURA NAO CONECTADO"); // Sensor conectado, imprime mensagem de erro   
//  } else {    
//    temperatura = sensor.getTempC(endereco_temp);
//    String message = "Temperatura: ";
//    message.concat(String(temperatura));
//    message.concat(" C");
//    
//  }
//  return temperatura;
//}



//void setupSensorTemperatura(){
//  //sensor.begin();  // Inicia o sensor temperatura
//}
  
