// ====== 設定 ======
const int LED_PIN    = 3;   // 題目指定 D3
const int BUTTON_PIN = 2;   // 一端接 GND、使用 INPUT_PULLUP

// LED 驅動極性：一般裸LED = 高電位亮(1)；若用有源模組(低電位亮)改成 0
#define LED_ACTIVE_HIGH 1

// 三種頻率（毫秒）：慢閃 / 不快不慢 / 快閃
const unsigned long SLOW_MS   = 1000; // 1 秒
const unsigned long MEDIUM_MS = 500;  // 0.5 秒
const unsigned long FAST_MS   = 200;  // 0.2 秒

// ====== 狀態 ======
// 0=恆亮, 1=慢閃, 2=中閃, 3=快閃
int mode = 0;

int lastReading = HIGH, stableState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 30;

unsigned long lastToggle = 0; // 閃爍切換用
bool blinkOn = true;          // 目前閃爍顯示位元

// ====== 小工具 ======
inline void setLed(bool on) {
#if LED_ACTIVE_HIGH
  digitalWrite(LED_PIN, on ? HIGH : LOW);
#else
  digitalWrite(LED_PIN, on ? LOW : HIGH);
#endif
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // 按下=LOW
  setLed(true);                      // 初始：恆亮
}

void loop() {
  unsigned long now = millis();

  // ---- 去彈跳 + 邊緣偵測（用「放開」算一次按）----
  int reading = digitalRead(BUTTON_PIN);
  if (reading != lastReading) lastDebounceTime = now;
  if ((now - lastDebounceTime) > debounceDelay) {
    if (stableState == LOW && reading == HIGH) {
      // 短按釋放：切換模式
      mode = (mode + 1) % 4;  // 0→1→2→3→0
      // 切模式時重置閃爍節拍，避免接續時相位怪
      lastToggle = now;
      blinkOn = true;
    }
    stableState = reading;
  }
  lastReading = reading;

  // ---- 依模式顯示 ----
  switch (mode) {
    case 0: // 恆亮
      setLed(true);
      break;

    case 1: // 慢閃
      if (now - lastToggle >= SLOW_MS) {
        lastToggle = now;
        blinkOn = !blinkOn;
      }
      setLed(blinkOn);
      break;

    case 2: // 不快不慢
      if (now - lastToggle >= MEDIUM_MS) {
        lastToggle = now;
        blinkOn = !blinkOn;
      }
      setLed(blinkOn);
      break;

    case 3: // 快閃
      if (now - lastToggle >= FAST_MS) {
        lastToggle = now;
        blinkOn = !blinkOn;
      }
      setLed(blinkOn);
      break;
  }
}
