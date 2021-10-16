/**
 * Desenvolvido por: Marcelo Barbosa Soares
 * E-mail: mbsoares.infor@gmail.com
 * Data: 01/03/2021
 * Dissertacao do curso de Mestrado em informatica Aplicada, pela Universidade Unisinos - RS - Brasil 
 * Implementacao de leitura de sensores, com otimizações para enconomia de energia.
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
#define pinoBuzzer  5  
#define TAM_VETOR  5


// outros define
#define DHTTYPE      DHT11 
#define NOME_ARQUIVO_DATA_SET  "dataset.txt"

// objetos.
DHT_Unified dht(pinoSensorTemperatura, DHTTYPE);    
HX711 balanca;             

// variaveis diversas.
unsigned long contadorLoopParaLeitura = 0;
byte TEMPO_DELAY  = 100;
byte UM_SEGUNDO = ((TEMPO_DELAY / 10)); // representa a quantidade de loops 
short UM_MINUTO = (UM_SEGUNDO * 60) ; // representa a quantidade de loops 
bool s_high=0;
short maiorSom = 0;
short maiorGas = 0;
float temperatura = 0;
float humidade = 0;
long contadorAbelha = 0;
String valores = "";
float peso = 0;
float calibration_factor = -22130;     // fator de calibração aferido na Calibração 


void setup() {
  Serial.begin(9600);   
  
  setupPinos();
  
  if (SD.begin()) { 
    Serial.println("SD Card pronto para uso.");     
  } else {
    Serial.println("Falha na inicialização do SD Card.");
    ligaBuzzer(-1);
    return;
  }
  dht.begin();   
  configuraBalanca();
  Serial.println("Valores dos contadores de tempo:");
  Serial.print(UM_SEGUNDO);  
  Serial.println(" CICLOS = UM SEGUNDO");
  Serial.print(UM_MINUTO);  
  Serial.println(" CICLOS = UM MINUTO: ");
  
  Serial.println("Fazendo primeiro leitura dos sensores e salvando");  
  processaLeituraTodosSensores();
  adicionaValoresVetor();
  escreveCartao(valores);
  Serial.println("Setup OK"); 
}



// TODO tirar todos os print de log, 
void loop() {

  bool eUmMinuto = ((contadorLoopParaLeitura % UM_MINUTO) == 0) && contadorLoopParaLeitura != 0;
  bool eCincoMinuto = ((contadorLoopParaLeitura % (UM_MINUTO * 5)) == 0) && contadorLoopParaLeitura != 0;
  bool eQuinzeMinuto = ((contadorLoopParaLeitura % (UM_MINUTO * 15)) == 0) && contadorLoopParaLeitura != 0;


  if(eUmMinuto){
    Serial.println("processando operacoes por 1 minuto");
    processaMaiorGas();
    Serial.println(valores);
  }

  if(eCincoMinuto){
     Serial.println("processando operacoes por 5 minutos");           
     processaLeituraTemperaturaHumidade();    
     processaLeituraBalanca();
     validaPeso();
     adicionaValoresVetor(); 
  }
 
  if(eQuinzeMinuto){
    Serial.println("processando operacoes por 15 minutos");    
    escreveCartao(valores);
    contadorLoopParaLeitura = 0;    
  }
  
  processaMaiorSomAbelhas();
  processaContadorAbelhas();  
  
  delay(TEMPO_DELAY);
  contadorLoopParaLeitura++;  
 
}

void configuraBalanca(){
  Serial.println("Configurando balança");
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

// armazena o maior gas lido
void processaMaiorGas(){
  int  gasLido = analogRead(pinoGas);   
  if(gasLido > maiorGas){
    maiorGas = gasLido;    
  }
}

// armazena o maior som lido das abelhas.
// valor de calibração do sensor: 486 a 487
void processaMaiorSomAbelhas(){
  int somLido = analogRead(pinoSensorSom);   
  if(somLido > maiorSom){
    maiorSom = somLido;    
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

// parte de leitura de temperatura e humidade.
void processaLeituraTemperaturaHumidade(){
    sensors_event_t event;                      
    dht.temperature().getEvent(&event);           
     temperatura = event.temperature;  
    dht.humidity().getEvent(&event);    
    humidade= event.relative_humidity;      
}

void adicionaValoresVetor(){    
    String valorAtualLido = criaLinhaValoresSensores(contadorAbelha,maiorGas,temperatura,humidade,maiorSom,peso);
    Serial.println("valores lidos agora:  " + valorAtualLido);
    valores += valorAtualLido;    
    limpaVariaveisSensores();    
}

void limpaVariaveisSensores(){
    maiorSom = 0;
    maiorGas = 0;
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

void validaPeso(){  
  if(peso < 1){
    ligaBuzzer(-1);
  }
}

void escreveCartao(String valor){
  
  File myFile = SD.open(NOME_ARQUIVO_DATA_SET, FILE_WRITE);  
  if (myFile) {         
      Serial.println("Escrevendo no arquivo");  
      Serial.print(valor);
      myFile.println(valor);     
      myFile.close();        
  }else{
      ligaBuzzer(-1);
  }
  valores = "";   
}


void setupPinos(){
  pinMode(pinoGas, INPUT);
  pinMode(pinoSensorMovimento,INPUT);  
  pinMode(pinoSD, OUTPUT);   
  pinMode(pinoSensorSom, INPUT); 
  digitalWrite(pinoSensorMovimento,LOW); 
  pinMode(pinoBuzzer,OUTPUT);  
}

void ligaBuzzer(int tempo){
  tone(pinoBuzzer,500);   
  if(tempo != -1){
    delay(tempo);     
    noTone(pinoBuzzer);
    delay(tempo);    
  } 

}


void digitalWrite(int pin, int status, String texto){
  int statusAtual = digitalRead(pin);
  if(statusAtual != status){
    digitalWrite(pin, status);   
    Serial.println(texto);
  }
}

  
