// DEFINIÇÕES DE PINOS
#define pinTrigger 13
#define pinEcho 12

// DECLARAÇÃO DE FUNÇÕES
float leituraSimples();
float calcularDistancia();
void sonarBegin(byte trig, byte echo);

// DECLARAÇÃO DE VARIÁVEIS
float distancia;

void setup()
{

  Serial.begin(9600);
  sonarBegin(pinTrigger, pinEcho);
}

void loop()
{

  distancia = calcularDistancia();

  Serial.print("Distância: ");
  Serial.print(distancia);
  Serial.println(" cm");

  delay(40);
}

// IMPLEMENTO DE FUNÇÕES

void sonarBegin(byte trig, byte echo)
{

#define divisor 58.0
#define intervaloMedida 8.75 // MÁXIMO 35 mS PARA ATÉ 6,0M MIN 5mS PARA ATÉ 0,8M
#define qtdMedidas 20        // QUANTIDADE DE MEDIDAS QUE SERÃO FEITAS

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  digitalWrite(trig, LOW); // DESLIGA O TRIGGER E ESPERA 500 uS
  delayMicroseconds(500);
}

float calcularDistancia()
{

  float leituraSum = 0;
  float resultado = 0;

  for (int index = 0; index < qtdMedidas; index++)
  {

    delay(intervaloMedida);
    leituraSum += leituraSimples();
  }

  resultado = (float)leituraSum / qtdMedidas;
  resultado = resultado + 2.2;

  return resultado;
}

float leituraSimples()
{

  long duracao = 0;
  float resultado = 0;

  digitalWrite(pinTrigger, HIGH);

  delayMicroseconds(10);
  digitalWrite(pinTrigger, LOW);

  duracao = pulseIn(pinEcho, HIGH);

  resultado = ((float)duracao / divisor);

  return resultado;
}