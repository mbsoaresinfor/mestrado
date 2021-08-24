#include <OneWire.h> // sensor temperatura
#include <DallasTemperature.h> // sensor temperatura
#include <Servo.h> // servo
#include <LiquidCrystal.h> // liquid cristal.


// definicao dos pinos
#define  pinoGas   A2   
#define pinoSensorMovimento 10

const int sensorTemperaturaPin = 7; // Define pino do sensor

unsigned long contadorAbelha = 0;
bool s_high=0;

// objetos.
OneWire oneWire(sensorTemperaturaPin); // Cria um objeto OneWire
DallasTemperature sensor(&oneWire); // Informa a referencia da biblioteca dallas temperature para Biblioteca onewire
DeviceAddress endereco_temp; // Cria um endereco temporario da leitura do sensor


// variaveis diversas.
int TIME_DELAY = 100;
int UM_MINUTO = 10 * 60;
int contadorLoopParaLeitura = 0;


void setup() {
  Serial.begin(9600);   
  setupPinos();
  Serial.println("Setup config");

}
// TODO tirar todos os print de log, 
void loop() {

   if(contadorLoopParaLeitura == UM_MINUTO){
      int  gas = analogRead(pinoGas);            
      escreveCartao(contadorAbelha,gas);
      contadorLoopParaLeitura = 0;
   }else{
      contadorLoopParaLeitura++;
   }
   
  // contadorAbelhas
  bool movimento = digitalRead(pinoSensorMovimento);
  if(movimento){ 
    s_high = 1;
   }

  if(!movimento && s_high){
    s_high =0;
    contadorAbelha+=1;
    Serial.println(contadorAbelha); // TODO DEPOIS TIRAR ESTE LOG.
  }
  
  delay(TIME_DELAY);

}

// valores: contador;gas
void escreveCartao(int contador,int gas){
  String token = ";";
  String message = "";
  message.concat(String(gas));    
  message.concat(String(token));    
  message.concat(String(contador));
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
  
