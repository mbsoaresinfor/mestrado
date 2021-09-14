#include <OneWire.h> // sensor temperatura
#include <DallasTemperature.h> // sensor temperatura
#include <SD.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>    
#include <DHT.h>
#include <DHT_U.h>

// definicao dos pinos
#define  pinoGas   A2   
#define pinoSensorMovimento 9
#define pinoSD  10
#define pinoSensorTemperatura 2  
#define pinoSensorSom  A4


// outros define
#define DHTTYPE      DHT22 
#define NOME_ARQUIVO_DATA_SET  "dataset.txt"

// objetos.
DHT_Unified dht(pinoSensorTemperatura, DHTTYPE);    
sensor_t sensor;
File myFile;

// variaveis diversas.
unsigned long contadorAbelha = 0;
unsigned long contadorLoopParaLeitura = 0;
int TEMPO_DELAY = 100;
unsigned long UM_SEGUNDO = ((TEMPO_DELAY / 10));
unsigned long UM_MINUTO = (UM_SEGUNDO * 60) ; 
unsigned long CINCO_MINUTO = (UM_MINUTO * 5) ; 
bool s_high=0;
int maiorSom = 0;
int maiorGas = 0;



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
  dht.begin();   
  Serial.println("Valores dos contadores de tempo");
  Serial.print("UM_SEGUNDO: ");
  Serial.println(UM_SEGUNDO);  
  Serial.print("UM_MINUTO: ");
  Serial.println(UM_MINUTO);  
  Serial.print("CINCO_MINUTO: ");
  Serial.println(CINCO_MINUTO);  
  Serial.println("Setup config OK");  
  processaLeituraEscritaSensores();  

}

// TODO tirar todos os print de log, 
void loop() {

  if(eUmMinuto()){
    Serial.println("processando operacoes de cada 1 minuto");
    processaMaiorGas();
  }

  if(eCincoMinuto()){
      Serial.println("processando operacoes de cada 5 minutos");
      processaLeituraEscritaSensores();
      contadorLoopParaLeitura = 0;
      maiorSom = 0;
      maiorGas = 0;
  }
  
  processaMaiorSomAbelhas();
  processaContadorAbelhas();  
  
  delay(TEMPO_DELAY);
  contadorLoopParaLeitura++;  
 
}
boolean eCincoMinuto(){
  return contadorLoopParaLeitura == CINCO_MINUTO;
}
boolean eUmMinuto(){
  return ((contadorLoopParaLeitura % UM_MINUTO) == 0) && contadorLoopParaLeitura != 0;
}

// armazena o maior gas lido
void processaMaiorGas(){
  int  gasLido = analogRead(pinoGas);   
  if(gasLido > maiorGas){
    maiorGas = gasLido;
    Serial.print("setado maior gas: ");     
    Serial.println(maiorGas);
  }
}

// armazena o maior som lido das abelhas.
// valor de calibração do sensor: 486 a 487
void processaMaiorSomAbelhas(){
  int somLido = analogRead(pinoSensorSom);   
  if(somLido > maiorSom){
    maiorSom = somLido;
    Serial.print("setado maior som: ");     
    Serial.println(maiorSom);
  }
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
    
    // parte de leitura de temperatura e humidade.
    sensors_event_t event;                      
    dht.temperature().getEvent(&event);           
    float temperatura = event.temperature;  
    dht.humidity().getEvent(&event);    
    float humidade= event.relative_humidity;        
    
    String valores = criaStringValoresSensores(contadorAbelha,maiorGas,temperatura,humidade,maiorSom);

    escreveCartao(valores);
    Serial.println("processaLeituraEscritaSensores: " );    
    Serial.print("contadorAbelha: ");
    Serial.print(contadorAbelha);
    Serial.print(" - gas: ");
    Serial.print(maiorGas);
    Serial.print(" - temperatura: ");
    Serial.print(temperatura);
    Serial.print(" - humidade: ");
    Serial.print(humidade);
    Serial.print(" - maiorSom:");
    Serial.print(maiorSom);
    Serial.println("");
    
}

// valores: contador;gas
String criaStringValoresSensores(int contador,int gas,float temperatura, float humidade,int som ){
  String token = ";";
  String message = "";
  message.concat(String(contador));
  message.concat(String(token));    
  message.concat(String(gas));    
  message.concat(String(token));          
  message.concat(String(temperatura));          
  message.concat(String(token));          
  message.concat(String(humidade));       
  message.concat(String(token));          
  message.concat(String(som));             
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
  pinMode(pinoSensorSom, INPUT); 

  digitalWrite(pinoSensorMovimento,LOW); 
}



void digitalWrite(int pin, int status, String texto){
  int statusAtual = digitalRead(pin);
  if(statusAtual != status){
    digitalWrite(pin, status);   
    Serial.println(texto);
  }
}

  
