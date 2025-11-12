// === 腳位設定（使用 PWM：3,5,6） ===
const int buttonPin = 2;       // 按鈕，一端接 GND
const int RPin = 3;            // R -> 3 (PWM)
const int GPin = 5;            // G -> 5 (PWM)
const int BPin = 6;            // B -> 6 (PWM)

// === 參數 ===
int mood = 10;                 // 0~20，預設中性
bool pressed = false;          // 按鈕邏輯
unsigned long touchedAt = 0;   // 最後互動時間
unsigned long reducedAt = 0;   // 上次自動減分時間
const unsigned long idleMs = 5000;  // 超過 5 秒沒按
const unsigned long stepMs = 1000;  // 每秒 -1

// --- 共陽輸出工具：把 0~255 反相 ---
static inline void writeRGB(int r, int g, int b) {
  r = constrain(r, 0, 255);
  g = constrain(g, 0, 255);
  b = constrain(b, 0, 255);
  // 共陽反相：0=最亮, 255=最暗
  analogWrite(RPin, 255 - r);
  analogWrite(GPin, 255 - g);
  analogWrite(BPin, 255 - b);
}

// --- 顯示顏色：0綠 → 10黃 → 20紅（B=0）---
void showLED(int m) {
  m = constrain(m, 0, 20);
  float t = m / 10.0;  // 0~2
  int R, G;

  if (t <= 1.0) {
    // 綠(0,255) → 黃(255,255)：R 0→255, G 255
    R = (int)(255 * t);
    G = 255;
  } else {
    // 黃(255,255) → 紅(255,0)：R 255, G 255→0
    R = 255;
    G = (int)(255 * (2.0 - t));
  }
  writeRGB(R, G, 0);
}

void setup() {
  pinMode(RPin, OUTPUT);
  pinMode(GPin, OUTPUT);
  pinMode(BPin, OUTPUT);

  // 用內建上拉，按鈕另一端接 GND（按下=LOW）
  pinMode(buttonPin, INPUT_PULLUP);

  touchedAt = millis();
}

void loop() {
  showLED(mood);

  // 簡單的按鈕去彈跳：只在 HIGH->LOW 觸發一次
  static int last = HIGH;
  int now = digitalRead(buttonPin);

  if (last == HIGH && now == LOW && !pressed) {  // 被按下
    pressed = true;
    mood = min(mood + 1, 20);
    touchedAt = millis();
  }
  if (now == HIGH) pressed = false;
  last = now;

  // 超過 5 秒沒互動，每秒自動 -1
  unsigned long t = millis();
  if (t - touchedAt > idleMs && t - reducedAt > stepMs) {
    mood = max(mood - 1, 0);
    reducedAt = t;
  }
}