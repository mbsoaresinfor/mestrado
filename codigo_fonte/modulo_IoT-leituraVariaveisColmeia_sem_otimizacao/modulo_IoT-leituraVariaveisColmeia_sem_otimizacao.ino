/**
 * Desenvolvido por: Marcelo Barbosa Soares
 * E-mail: mbsoares.infor@gmail.com
 * Data: 11/10/2021
 * Dissertacao do curso de Mestrado em informatica Aplicada, pela Universidade Unisinos - RS - Brasil 
 * Implementacao de leitura de sensores, sem otimizações para enconomia de energia.
 */
#include <SD.h>
#include <SPI.h> 
#include <DHT.h>
#include <DHT_U.h>
#include "HX711.h"                    

// definicao dos pinos
#define  pinoGas   A2   
#define pinoSensorMovimento 9
#define pinoSD  10
#define pinoSensorTemperatura 2  
#define pinoSensorSom  A4
#define pinoBalancaDOUT 3                      
#define pinoBalancaCLK  4  
#define TAM_VETOR  5


// outros define
#define DHTTYPE      DHT22 
#define NOME_ARQUIVO_DATA_SET  "dataset.txt"

// objetos.
DHT_Unified dht(pinoSensorTemperatura, DHTTYPE);    
HX711 balanca;             

// variaveis diversas.
int TEMPO_DELAY  = 1000;
bool s_high=0;
short som = 0;
short gas = 0;
float temperatura = 0;
float humidade = 0;
long contadorAbelha = 0;
String valores = "";
float peso = 0;
float calibration_factor = -22130;     


void setup() {
  Serial.begin(9600);   
  
  setupPinos();
  
  if (SD.begin()) { 
    Serial.println("SD Card pronto para uso.");     
  } else {
    Serial.println("Falha na inicializacao do SD Card.");
    return;
  }
  dht.begin();   
  configuraBalanca();
  Serial.println("Fazendo primeiro leitura dos sensores e salvando");  
  processaLeituraTodosSensores();
  adicionaValoresVetor();
  escreveCartao(valores);
  Serial.println("Setup OK"); 
}


void loop() {

    processaMaiorSomAbelhas();
    processaContadorAbelhas();    
    processaMaiorGas();
    processaLeituraTemperaturaHumidade();    
    processaLeituraBalanca();
    
    adicionaValoresVetor(); 
    escreveCartao(valores);  
    delay(TEMPO_DELAY);    
 
}

void configuraBalanca(){
  Serial.println("Configurando balanca");
  balanca.begin(pinoBalancaDOUT, pinoBalancaCLK);   
  balanca.set_scale(calibration_factor);            
  balanca.tare();                                   
}

void processaLeituraTodosSensores(){  
  processaMaiorGas();
  processaMaiorSomAbelhas();
  processaContadorAbelhas();  
  processaLeituraTemperaturaHumidade();
  processaLeituraBalanca();
}

void processaLeituraBalanca(){
  peso = balanca.get_units();
}


void processaMaiorGas(){
  gas = analogRead(pinoGas);     
}

void processaMaiorSomAbelhas(){
  som = analogRead(pinoSensorSom);     
}

void processaContadorAbelhas(){
  bool movimento = digitalRead(pinoSensorMovimento);
  if(movimento){ 
    s_high = 1;
  }

  if(!movimento && s_high){
    s_high =0;
    contadorAbelha+=1;   
  }
}


void processaLeituraTemperaturaHumidade(){
    sensors_event_t event;                      
    dht.temperature().getEvent(&event);           
     temperatura = event.temperature;  
    dht.humidity().getEvent(&event);    
    humidade= event.relative_humidity;      
}

void adicionaValoresVetor(){    
    String valorAtualLido = criaLinhaValoresSensores(contadorAbelha,gas,temperatura,humidade,som,peso);
    Serial.println("valores lidos agora:  " + valorAtualLido);
    valores += valorAtualLido;        
}



String criaLinhaValoresSensores(int contador,int gas,float temperatura, float humidade,int som,float peso ){

  String token = ";";
  String message = "";
  message.concat(contador);
  message.concat(token);    
  message.concat(gas);    
  message.concat(token);          
  message.concat(temperatura);          
  message.concat(token);          
  message.concat(humidade);       
  message.concat(token);          
  message.concat(som);        
  message.concat(token);
  message.concat( formataPeso(peso));       
  message.concat("\n");       
  return message;     
}

String formataPeso(float peso){   
   return   String(peso, 3);
}

void escreveCartao(String valor){
  
  File myFile = SD.open(NOME_ARQUIVO_DATA_SET, FILE_WRITE);  
  if (myFile) {         
      Serial.println("Escrevendo no arquivo");  
      Serial.print(valor);
      myFile.println(valor);     
      myFile.close();        
  }  
  valores = "";   
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

  
