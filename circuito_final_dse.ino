// Declaração das variáveis
int ldr=A5;
int pot=A4;
int led=2;
int led_status1=3;
int led_status2=4;
int estado=0;

// Declaração da função avalia(), que recebe 
// uma variável int luz e uma variável int estado
int avalia(int luz, int estado);

void setup()
{
  pinMode(led,OUTPUT);
  pinMode(led_status1,OUTPUT);
  pinMode(led_status2,OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  // Declaração das variáveis luz e potencia como variáveis locais
  int luz;
  int valor;
  
  // Faz a leitura do potenciômetro
  valor = analogRead(pot);
  
  // SE a leitura do potenciômetro for MENOR que 511...
  if(valor<511){
    // ...Ativa o modo 1, e liga o led correspondente
  	estado = 1;
    digitalWrite(led_status1,HIGH);
    digitalWrite(led_status2,LOW);
  }
  // SENÃO...
  else {
    // ...Ativa o modo 2, e liga o led correspondente
    estado = 2;
    digitalWrite(led_status1,LOW);
    digitalWrite(led_status2,HIGH);
  }
  
  // Espera 50 milisegundos e então faz a leitura do LDR
  delay(50);
  luz = analogRead(ldr);
  Serial.println(luz);
  
  // chama a função avalia()
  avalia(luz, estado);
}

// A função avalia recebe a luz e o modo e de acordo com isso, ativa a lanterna
int avalia(int luz, int estado)
{
  switch(estado){
    // No modo 1...
  	case 1:
    // ...SE a iluminação for MAIOR QUE 850...
    if(luz > 850){
      // ...Liga a iluminação por 15 segundos, e então a desliga
      digitalWrite(led,HIGH);
      delay(15000);
      digitalWrite(led,LOW);
      // Faz a chamada recursiva com estado 3
      estado = 3;
      avalia(luz,estado);
    }
    break; // encerra a função
    
    // No modo 2...
    case 2:
    // ...SE a iluminção for MAIOR QUE 850...
    if(luz > 850){
      // ...Liga a iluminação
      digitalWrite(led,HIGH);
    }
    // SENÃO...
    else{
      // ...Desliga a iluminação
      digitalWrite(led,LOW);
    }
    break; // encerra a função
    
    // O modo 3 faz parte do modo 1, e acontece ao seu fim sempre.
    case 3:
    // ENQUANTO a iluminação for MAIOR QUE 850, permanece desligado.
    do{
      digitalWrite(led,LOW);
      luz = analogRead(ldr);
    }while(luz > 850);
    // Quando a iluminação cair, reseta o estado, e encerra a função.
    estado = 0;
    break;
  }
  return 0;
}