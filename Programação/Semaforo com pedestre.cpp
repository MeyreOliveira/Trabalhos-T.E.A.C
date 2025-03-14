// Pinos dos LEDs do semáforo de carros
const int vermelhoCarro = 2;
const int amareloCarro = 3;
const int verdeCarro = 4;

// Pinos dos LEDs do semáforo de pedestres
const int vermelhoPedestre = 5;
const int verdePedestre = 6;

// Pino do botão
const int botao = 7;

// Variáveis para controlar o tempo
unsigned long tempoAnterior = 0;
const long intervaloCarro = 5000; // 5 segundos para o verde dos carros
const long intervaloAmarelo = 2000; // 2 segundos para o amarelo dos carros
const long intervaloPedestre = 7000; // 7 segundos para o verde dos pedestres

// Variável para o estado do botão
int estadoBotao = 0;

// Variável para o estado do semáforo
enum Estado {CARRO_VERDE, CARRO_AMARELO, CARRO_VERMELHO, PEDESTRE_VERDE};
Estado estadoAtual = CARRO_VERDE;

void setup() {
  // Configura os pinos dos LEDs como saída
  pinMode(vermelhoCarro, OUTPUT);
  pinMode(amareloCarro, OUTPUT);
  pinMode(verdeCarro, OUTPUT);
  pinMode(vermelhoPedestre, OUTPUT);
  pinMode(verdePedestre, OUTPUT);

  // Configura o pino do botão como entrada
  pinMode(botao, INPUT);

  // Inicializa o semáforo
  digitalWrite(verdeCarro, HIGH);
  digitalWrite(vermelhoPedestre, HIGH);
}

void loop() {
  // Lê o estado do botão
  estadoBotao = digitalRead(botao);

  // Obtém o tempo atual
  unsigned long tempoAtual = millis();

  switch (estadoAtual) {
    case CARRO_VERDE:
      // Semáforo de carros verde
      if (estadoBotao == HIGH) {
        // Botão pressionado, muda para amarelo
        estadoAtual = CARRO_AMARELO;
        tempoAnterior = tempoAtual;
        digitalWrite(verdeCarro, LOW);
        digitalWrite(amareloCarro, HIGH);
      }
      break;

    case CARRO_AMARELO:
      // Semáforo de carros amarelo
      if (tempoAtual - tempoAnterior >= intervaloAmarelo) {
        // Tempo do amarelo expirou, muda para vermelho
        estadoAtual = CARRO_VERMELHO;
        tempoAnterior = tempoAtual;
        digitalWrite(amareloCarro, LOW);
        digitalWrite(vermelhoCarro, HIGH);
        digitalWrite(vermelhoPedestre, LOW);
        digitalWrite(verdePedestre, HIGH);
      }
      break;

    case CARRO_VERMELHO:
          if (tempoAtual - tempoAnterior >= intervaloPedestre) {
        // Tempo do pedestre verde expirou, volta para verde dos carros
        estadoAtual = CARRO_VERDE;
        tempoAnterior = tempoAtual;
        digitalWrite(vermelhoCarro, LOW);
        digitalWrite(verdeCarro, HIGH);
        digitalWrite(vermelhoPedestre, HIGH);
        digitalWrite(verdePedestre, LOW);
      }
      break;

    case PEDESTRE_VERDE:
      // Semáforo de pedestres verde
      if (tempoAtual - tempoAnterior >= intervaloPedestre) {
        // Tempo do pedestre verde expirou, volta para verde dos carros
        estadoAtual = CARRO_VERDE;
        tempoAnterior = tempoAtual;
        digitalWrite(vermelhoCarro, LOW);
        digitalWrite(verdeCarro, HIGH);
        digitalWrite(vermelhoPedestre, HIGH);
        digitalWrite(verdePedestre, LOW);
      }
      break;
  }
}