//importando as bibliotecas
#include <DHT.h>  //importando a biblioteca do dht
#include <Adafruit_Sensor.h>  //importando a biblioteca do dht
#include <SPI.h>   // importando a biblioteca da ethernet
#include <Ethernet.h>   // importando a biblioteca da ethernet
// definindo as pinagem
#define pino_sinal_analogico A0  // pino do sensor higrometro
int valor_analogico;  //valor _analogico rebendo um valor inteiro
#define DHTPIN A1    // definindo o DHTPIN A1
#define DHTTYPE DHT11   //definindo o DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
//mac da maquina para se conectar a internet
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
#define pino_bomba 10    // definindo o pino da bomba como pino 10
#define pino_cooler 11    // definindo o pino do cooler como pino 11
#define pino_lamp 9      // definindo o pino da lâmpada como pino 9
//ip da maquina para se conectar a internet
IPAddress ip(192,168,0,108); // ip da shield ethernet para rede
EthernetServer server(80); // porta do servidor que vai ser ultizada 

void setup()
{
  Serial.begin(9600);  // estartando o manitor serial e informando a velocidade da conexão
  pinMode(pino_sinal_analogico, INPUT); // informando o pino e o estado 
  pinMode(pino_bomba, OUTPUT); // informando o pino e o estado 
  pinMode(pino_cooler, OUTPUT); // informando o pino e o estado 
  pinMode(pino_lamp, OUTPUT); // informando o pino e o estado 
  //estartando o dht
  dht.begin(); //  estartando o dht
  //estartando o ethernet
  Ethernet.begin(mac, ip);
   //estartando o servidor
  server.begin();
} 
void loop() 
{

    EthernetClient client = server.available();  
    //ler o valor analogico para tomar as decisões de ligar ou desligar bomba.
    valor_analogico = analogRead(pino_sinal_analogico);
    if (valor_analogico > 0 && valor_analogico < 500)// umidade do solo esta umida, será informado ao usuário na web
    {
      client.println("Status: Solo umido");
      //desligar bomba
      digitalWrite(pino_bomba, LOW); 
    }
    if (valor_analogico > 600 && valor_analogico < 900)// umidade do solo esta modera ou seja adequada, será informado ao usuário na web
    {
      client.println(" Status: Umidade moderada");
      //desligar bomba
      digitalWrite(pino_bomba, LOW);
    }
    if (valor_analogico > 900 && valor_analogico < 1024)// umidade do solo esta seca, será informado ao usuário na web
    {
      client.println(" Status: Solo seco");
      //ligar bomba
      digitalWrite(pino_bomba, HIGH);
    }
    
    // lendo os valores analogicos do sensor dht 11
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (isnan(t) || isnan(h)) 
    {
      //error no dht
      client.println("error no DHT");
    } 
    else 
    {
      //imprimir no manitor serial a umidade do solo
      client.print("Umidade: ");
      client.print(h);
      client.print(" %t");
      //imprimir no manitor serial a temperatura do solo
      client.print("Temperatura: ");
      client.print(t);
      client.println(" *C");
      if (t>25 or h> 28){
        //ligar o cooler
        //digitalWrite(pino_cooler, HIGH);
      }
      if (t<=25 or h<= 28){
        //desligar o cooler
        //digitalWrite(pino_cooler, LOW);
      }
      if (t <=22){
        // ligando a lâmpada caso tempersatura esteja baixo
        digitalWrite(pino_lamp, HIGH);
      }
      if (t >22){
        // desligar lâmpada casoa temperatura esteja adequada
        digitalWrite(pino_lamp, LOW);
      }
      digitalWrite(pino_cooler, HIGH);
    }

    
    //EthernetClient client = server.available();  
    if (client) 
    {  
      //estabelecer a conexão com a web
        boolean currentLineIsBlank = true;
        while (client.connected()) 
        {
            if (client.available())
            {   
                char c = client.read();                
                if (c == '\n' && currentLineIsBlank) 
                {    
                    //programaçao para web          
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.println("Connection: close");
                    client.println("Refresh: 2"); //Recarrega a pagina a cada 2 segundos
                    client.println();
                    client.println("<!DOCTYPE html>");
                    client.println("<html>");
                    client.println("<head>");
                    //titulo que vai ficar na pagina web
                    client.println("<title>Umidade do solo</title>");//titulo da pagina web
                    client.println("</head>");
                    client.println("<body>");
                    //Mostra as informacoes lidas pelo dht 11
                    client.print("Sensor dht 11 umidade : ");//mostrar a temperatura do ar
                    client.print("<b>");
                    client.print(h);
                    client.println("</b>");  
                    client.print("Sensor dht 11 temperatura : ");//mostrar a temperatura do ar
                    client.print("<b>");
                    client.print(t);
                    client.println("</b>");                                         
                    //Mostra as informacoes lidas pelo higrometro
                    client.print("Sensor higrometro : ");
                    client.print("<b>");
                    client.print(valor_analogico);
                    client.println("</body>");
                    client.println("</b></html>");
                    break;                 
                } 
                // encerrando conexão   
                if (c == '\n') 
                {
                    currentLineIsBlank = true;
                } 
                else if (c != '\r') 
                {
                    currentLineIsBlank = false;
                }
            } 
        }      
        delay(1);      
        client.stop();        
    } 
}
/*void ligar_cooler(){
  //ligar o cooler
  digitalWrite(pino_cooler, HIGH);
}
void desligar_cooler(){
  //desligar o cooler
  digitalWrite(pino_cooler, LOW);
}
void ligar_bomba(){
  //ligar bomba
  digitalWrite(pino_bomba, HIGH);
}
void desligar_bomba(){
  //desligar bomba
  digitalWrite(pino_bomba, LOW); 
}
//medir temperatura e umidade do solo
void umidade_ar() 
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(t) || isnan(h)) 
  {
    //erro no dht
    Serial.println("error no DHT");
  } 
  else 
  {
    //imprimir no manitor serial a umidade do solo
    Serial.print("Umidade: ");
    Serial.print(h);
    Serial.print(" %t");
    //imprimir no manitor serial a temperatura do solo
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.println(" *C");
    //ligar cooler caso a temperatura esteja alta
    while (t<25){
      ligar_cooler();
    }
   desligar_cooler(); 
  }
}
//medir umidade do solo
void temperatura_solo()
{
  valor_analogico = analogRead(pino_sinal_analogico);
  //ler o valor analogico para tomar as decisões de ligar ou ndesligar bomba.
  if (valor_analogico > 0 && valor_analogico < 500)
  {
    Serial.println(" Status: Solo umido");
  }
  if (valor_analogico > 600 && valor_analogico < 900)
  {
    Serial.println(" Status: Umidade moderada");
  }
  if (valor_analogico > 900 && valor_analogico < 1024)
  {
    Serial.println(" Status: Solo seco");
  }
  //ligar bombar caso a terra esteja seca
  while (valor_analogico >900){
    ligar_bomba();
  }
  desligar_bomba();
  delay(1000);
}*/
