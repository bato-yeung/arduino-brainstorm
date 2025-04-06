# Arduino 遊戲專案

## 專案描述
這是一個基於 Arduino 的互動遊戲，玩家需要根據亮起的 LED 按下對應的按鈕。遊戲會隨著分數的增加逐漸加快，當玩家按錯按鈕或未及時按下按鈕時，生命值會減少。當生命值歸零時，遊戲結束。

### 功能
1. 使用 2 個 LED 和 2 個按鈕進行互動。
2. Grove LED Bar 顯示玩家的生命值。
3. MAX7219 8x8 LED 矩陣顯示玩家的分數。
4. Grove 喇叭模組播放正確或錯誤的提示音。
5. 遊戲速度隨分數增加逐漸加快。

---

## 遊戲設定
- **起始生命值**: 10。
- **初始 LED 轉換間隔**: 2 秒。
- **回答正確後的速度提升**: 每次正確回答後，LED 轉換間隔將縮短 4%。

---

## 接線資訊

### 硬體元件
- **LED 燈**: 使用 2 個 LED，每個 LED 需串聯一個 220Ω 或 330Ω 的限流電阻，連接到 Arduino 的數位腳位 2, 3。
- **按鈕**: 使用 2 個按鈕，連接到 Arduino 的數位腳位 6, 7，並使用內建的上拉電阻。
- **Grove LED Bar**: 
  - **DCKI (Clock Input)**: 連接到 Arduino 的數位腳位 9。
  - **DI (Data Input)**: 連接到 Arduino 的數位腳位 8。
  - **VCC**: 連接到 Arduino 的 5V 腳位。
  - **GND**: 連接到 Arduino 的 GND 腳位。
- **MAX7219 8x8 LED 矩陣**: 
  - DIN: 連接到數位腳位 11
  - CLK: 連接到數位腳位 13
  - CS: 連接到數位腳位 12
- **Grove 喇叭模組**: 
  - **SIG (信號)**: 連接到 Arduino 的數位腳位 10。
  - **VCC**: 連接到 Arduino 的 5V 腳位。
  - **GND**: 連接到 Arduino 的 GND 腳位。

---

## 遊戲規則
1. 每次隨機亮起一個 LED。
2. 玩家需要按下對應的按鈕。
3. 按錯按鈕或未及時按下按鈕會扣除一點生命值。
4. 分數會顯示在 MAX7219 矩陣上，生命值會顯示在 Grove LED Bar 上。
5. 當生命值歸零時，遊戲結束。

---

## Demo 影片
[觀看 Demo 影片](https://youtube.com/shorts/ZwI1-EiM5uY?feature=share)

---

## 注意事項
- 確保所有元件正確連接，並檢查電路是否穩定。
- 使用 Arduino IDE 上傳程式碼，並安裝所需的外部函式庫（如 `MD_MAX72XX` 和 `Grove_LED_Bar`）。
- 可根據需求調整遊戲速度和其他參數。

---

## 硬體設置說明
![hardware-settings](https://github.com/user-attachments/assets/bca33534-bcd9-4ca3-aab1-99c52cd434c9)
