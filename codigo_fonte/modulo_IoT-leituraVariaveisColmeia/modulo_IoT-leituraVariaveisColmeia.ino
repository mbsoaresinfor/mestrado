#include <OneWire.h> // sensor temperatura
#include <DallasTemperature.h> // sensor temperatura
#include <Servo.h> // servo
#include <LiquidCrystal.h> // liquid cristal.


// definicao dos pinos
#define  pinoGas   A2   
#define pinoSensorMovimento 10

const int sensorTemperaturaPin = 7; // Define pino do sensor

// objetos.
OneWire oneWire(sensorTemperaturaPin); // Cria um objeto OneWire
DallasTemperature sensor(&oneWire); // Informa a referencia da biblioteca dallas temperature para Biblioteca onewire
DeviceAddress endereco_temp; // Cria um endereco temporario da leitura do sensor


// variaveis diversas.
int TIME_DELAY = 1000;

void setup() {
  Serial.begin(9600);   
  setupPinos();
  Serial.print("Setup config");

}

void loop() {
 
  int  gas = analogRead(pinoGas);
  bool movimento = digitalRead(pinoSensorMovimento);
  // verificar uma forma automatizada para salvar os dados de movimento, mais que os outros...pensar sobre isso
  escreveCartao(gas,movimento);
  
  delay(TIME_DELAY);

}

// valorgaz;
void escreveCartao(int gas, bool movimento){
  String token = ";";
  String message = "";
  message.concat(String(gas));    
  message.concat(String(token));    
  message.concat(String(movimento));
  message.concat(String(token));        
  Serial.println(message);
  // aqui escreve no cartao
  
}


void setupPinos(){
  pinMode(pinoGas, INPUT);
  pinMode(pinoSensorMovimento,INPUT);
  digitalWrite(pinoSensorMovimento,LOW);
 
}



void digitalWrite(int pin, int status, String texto){
  int statusAtual = digitalRead(pin);
  if(statusAtual != status){
    digitalWrite(pin, status);   
    Serial.println(texto);
  }
}



float leituraSensorTemperatura(){
  float temperatura = 0;
  sensor.requestTemperatures(); // Envia comando para realizar a conversão de temperatura
  if (!sensor.getAddress(endereco_temp,0)) { // Encontra o endereco do sensor no barramento
    Serial.println("SENSOR TEMPERATURA NAO CONECTADO"); // Sensor conectado, imprime mensagem de erro   
  } else {    
    temperatura = sensor.getTempC(endereco_temp);
    String message = "Temperatura: ";
    message.concat(String(temperatura));
    message.concat(" C");
    
  }
  return temperatura;
}



void setupSensorTemperatura(){
  sensor.begin();  // Inicia o sensor temperatura
}
  
