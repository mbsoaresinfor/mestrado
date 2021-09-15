#include <SD.h>
#include <SPI.h>
//#include <Adafruit_Sensor.h>    
#include <DHT.h>
#include <DHT_U.h>

// definicao dos pinos
#define  pinoGas   A2   
#define pinoSensorMovimento 9
#define pinoSD  10
#define pinoSensorTemperatura 2  
#define pinoSensorSom  A4
#define TAM_VETOR  5


// outros define
#define DHTTYPE      DHT22 
#define NOME_ARQUIVO_DATA_SET  "dataset.txt"

// objetos.
DHT_Unified dht(pinoSensorTemperatura, DHTTYPE);    


// variaveis diversas.
unsigned long contadorLoopParaLeitura = 0;
byte TEMPO_DELAY  = 100;
byte UM_SEGUNDO = ((TEMPO_DELAY / 10));
short UM_MINUTO = (UM_SEGUNDO * 60) ; 
bool s_high=0;
short maiorSom = 0;
short maiorGas = 0;
float temperatura = 0;
float humidade = 0;
long contadorAbelha = 0;
String vetor[TAM_VETOR];
byte indiceVetor = 0;



void setup() {
  Serial.begin(9600);   
  
  setupPinos();
  
  if (SD.begin()) { 
    Serial.println("SD Card pronto para uso.");     
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

  
  Serial.println("Fazendo primeiro leitura dos sensores e salvando");  
  processaLeituraTodosSensores();
  adicionaValoresVetor();
  escreveCartaoEfazProcessamentoVetorAposEscreveCartao(vetor);
  Serial.println("Setup config OK"); 
}


// TODO tirar todos os print de log, 
void loop() {

  bool eUmMinuto = ((contadorLoopParaLeitura % UM_MINUTO) == 0) && contadorLoopParaLeitura != 0;
  bool eCincoMinuto = ((contadorLoopParaLeitura % (UM_MINUTO * 5)) == 0) && contadorLoopParaLeitura != 0;
  bool eDezMinuto =  ((contadorLoopParaLeitura % (UM_MINUTO * 10)) == 0) && contadorLoopParaLeitura != 0;
  bool eQuinzeMinuto = ((contadorLoopParaLeitura % (UM_MINUTO * 15)) == 0) && contadorLoopParaLeitura != 0;

  if(eUmMinuto){
    Serial.println("processando operacoes de cada 1 minuto");
    processaMaiorGas();
  }

  if(eCincoMinuto){
      Serial.println("processando operacoes de cada 5 minutos");           
      adicionaValoresVetor();
  }
  
  if(eDezMinuto){
    Serial.println("processando operacoes de cada 10 minutos");
    processaLeituraTemperaturaHumidade();    
  } 

  if(eQuinzeMinuto){
    Serial.println("processando operacoes de cada 15 minutos");
    escreveCartaoEfazProcessamentoVetorAposEscreveCartao(vetor);
    contadorLoopParaLeitura = 0;    
  }
  
  processaMaiorSomAbelhas();
  processaContadorAbelhas();  
  
  delay(TEMPO_DELAY);
  contadorLoopParaLeitura++;  
 
}

void processaLeituraTodosSensores(){  
  processaMaiorGas();
  processaMaiorSomAbelhas();
  processaContadorAbelhas();  
  processaLeituraTemperaturaHumidade();
}


// armazena o maior gas lido
void processaMaiorGas(){
  int  gasLido = analogRead(pinoGas);   
  if(gasLido > maiorGas){
    maiorGas = gasLido;
    //Serial.print("setado maior gas: ");     
    //Serial.println(maiorGas);
  }
}

// armazena o maior som lido das abelhas.
// valor de calibração do sensor: 486 a 487
void processaMaiorSomAbelhas(){
  int somLido = analogRead(pinoSensorSom);   
  if(somLido > maiorSom){
    maiorSom = somLido;
    //Serial.print("setado maior som: ");     
    //Serial.println(maiorSom);
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

void processaLeituraTemperaturaHumidade(){
    // parte de leitura de temperatura e humidade.
    sensors_event_t event;                      
    dht.temperature().getEvent(&event);           
     temperatura = event.temperature;  
    dht.humidity().getEvent(&event);    
    humidade= event.relative_humidity;      
}

void adicionaValoresVetor(){
    
    String valorAtualLido = criaLinhaValoresSensores(contadorAbelha,maiorGas,temperatura,humidade,maiorSom);
    vetor[indiceVetor] = valorAtualLido;
    indiceVetor++;
    limpaVariaveisSensores();
    Serial.print("valorAtualLido:");
    Serial.println(valorAtualLido);
    
}

void limpaVariaveisSensores(){
    maiorSom = 0;
    maiorGas = 0;
}


String criaLinhaValoresSensores(int contador,int gas,float temperatura, float humidade,int som ){

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
  message.concat("\n");       
  return message;     
}

void escreveCartaoEfazProcessamentoVetorAposEscreveCartao(String valor[]){
  escreveCartao(valor);
  fazProcessamentoVetorAposEscreveCartao(valor);
}

void fazProcessamentoVetorAposEscreveCartao(String valor[]){
  //for(int i=0; i < TAM_VETOR; i++){
  //    valor[i] = '\0';      
 // }
  indiceVetor = 0;
}

void escreveCartao(String valor[]){
  Serial.println("escrevendo no arquivo");  
  File myFile = SD.open(NOME_ARQUIVO_DATA_SET, FILE_WRITE);  
  if (myFile) {     
    for(int i=0; i < indiceVetor; i++){
      Serial.print(valor[i]);
      myFile.println(valor[i]); 
    }
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

  
