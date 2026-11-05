

const byte pinosSegmentos[7] = {3, 4, 5, 6, 7, 8, 9}; 
const byte pinoBotaoIniciar = 11;
const byte pinoBotaoSortear = 12;

const unsigned long intervaloAnimacao = 55;
const unsigned long debounceMs = 35;


const byte digitos[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

struct Botao {
  byte pino;
  bool leituraEstavel;
  bool ultimaLeitura;
  unsigned long instanteMudanca;
};

Botao botaoIniciar = {pinoBotaoIniciar, HIGH, HIGH, 0};
Botao botaoSortear = {pinoBotaoSortear, HIGH, HIGH, 0};

bool animando = false;
byte numeroExibido = 0;
unsigned long instanteAnimacao = 0;

// Retorna verdadeiro uma única vez quando o botão é pressionado.
bool foiPressionado(Botao &botao) {
  bool leituraAtual = digitalRead(botao.pino);

  if (leituraAtual != botao.ultimaLeitura) {
    botao.ultimaLeitura = leituraAtual;
    botao.instanteMudanca = millis();
  }

  if (millis() - botao.instanteMudanca >= debounceMs &&
      leituraAtual != botao.leituraEstavel) {
    botao.leituraEstavel = leituraAtual;
    if (botao.leituraEstavel == LOW) {
      return true; 
    }
  }
  return false;
}

void mostrarDigito(byte numero) {
  numero = numero % 10;
  for (byte segmento = 0; segmento < 7; segmento++) {
    digitalWrite(pinosSegmentos[segmento], digitos[numero][segmento] ? HIGH : LOW);
  }
}

void apagarDisplay() {
  for (byte segmento = 0; segmento < 7; segmento++) {
    digitalWrite(pinosSegmentos[segmento], LOW);
  }
}

void setup() {
  for (byte segmento = 0; segmento < 7; segmento++) {
    pinMode(pinosSegmentos[segmento], OUTPUT);
  }

  pinMode(pinoBotaoIniciar, INPUT_PULLUP);
  pinMode(pinoBotaoSortear, INPUT_PULLUP);
  apagarDisplay();

  
  randomSeed(analogRead(pinoSeed));
}

void loop() {
  if (foiPressionado(botaoIniciar)) {
    animando = !animando;
    if (!animando) {
      apagarDisplay();
    }
  }

  if (foiPressionado(botaoSortear) && animando) {
    animando = false;
    numeroExibido = random(0, 10); 
    mostrarDigito(numeroExibido);
  }

  if (animando && millis() - instanteAnimacao >= intervaloAnimacao) {
    instanteAnimacao = millis();
    numeroExibido = random(0, 10);
    mostrarDigito(numeroExibido);
  }
}
