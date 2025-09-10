// Marchas - parte de cima e baixo do câmbio
const int g1st = 12;
const int g3rd = 11;
const int g5th = 10;
const int g2nd = 2;
const int g4th = 3;
const int g6th = 4;
const int gre  = 5;

const int pwmY = 9;  // eixo Y
const int pwmX = 6;  // eixo X

// Valores PWM
const int upgear   = 230; // ~90%
const int downgear = 26;  // ~10%
const int neutral  = 127; // ~50%

// Eixo X
const int left1    = 77;  // esquerda 1
const int left2    = 102; // esquerda 2
const int right1   = 152; // direita 1
const int right2   = 178; // direita 2
const int xNeutral = 127; // neutro

// Array de pinos
const int pinosMarchas[] = {g1st, g2nd, g3rd, g4th, g5th, g6th, gre};

// Mapas diretos de PWM (índice = marcha, 0 = neutro)
const int mapaPWMY[8] = {neutral, upgear, downgear, upgear, downgear, upgear, downgear, downgear};
const int mapaPWMX[8] = {xNeutral, left1, left1, left2, left2, right1, right1, right2};

int marchaAtualY = -1;
int marchaAtualX = -1;

// Função genérica para retornar a marcha ativa
int getMarchaAtiva(const int pinos[], int tamanho) {
  for (int i = 0; i < tamanho; i++) {
    if (!digitalRead(pinos[i])) return i + 1; // +1 para numerar 1..7
  }
  return 0; // neutro
}

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 7; i++) pinMode(pinosMarchas[i], INPUT_PULLUP);

  pinMode(pwmY, OUTPUT);
  pinMode(pwmX, OUTPUT);

  Serial.println("=== Sistema de Leitura de Marchas Iniciado ===");
}

void loop() {
  int marchaY = getMarchaAtiva(pinosMarchas, 7);
  int marchaX = marchaY; // usamos a mesma leitura para ambos os eixos

  int pwmYValue = mapaPWMY[marchaY];
  int pwmXValue = mapaPWMX[marchaX];

  analogWrite(pwmY, pwmYValue);
  analogWrite(pwmX, pwmXValue);

  // --- Debug compacto ---
  static String lastPrint = "";
  String marchaStr = (marchaY == 0 ? "N" : (marchaY == 7 ? "R" : String(marchaY)));
  String printLine = "(" + marchaStr + ", " + String(pwmXValue) + ", " + String(pwmYValue) + ")";
  
  if (printLine != lastPrint) {
    Serial.println(printLine);
    lastPrint = printLine;
  }

  delay(100);
}
