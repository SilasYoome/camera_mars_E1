# 視覺戰神車範例程式
## 燒入程式時的環境建置
### 1. 下在全部檔案
點擊由上方的「<> Code」綠色按鈕，選擇「Download ZIP」下載全部的檔案  

### 2. 建置Arduino Library
將Arduino -> library這整個資料夾移動到C:\Users\<username>\Documents\Arduino\libraries這路徑下
* 注意，需要先安裝Arduino IDE 1.8.19

### 3 程式燒入
#### 3.1 使用Cagebot_blockly
- 主程式下載
請到這網站下載Cagebot_blockly離線版，或者使用線上版的Cagebot_blockly

[離線版下載](https://www.cagebot.com/website/support)
[線上版編程](https://www.cagebot.com/shayangye_blockly/demos/code/index.html)

- 點擊上方的「載入積木程式(XML)」，並選擇副檔名為.xml的檔案來進行積木檔案匯入

- 點擊紅色箭頭按鈕「燒入程式到Arduino板」來進行程式燒入

#### 3.2 使用Arduino IDE 1.8.19
需先安裝Arduino IDE 1.8.19
- 開啟副檔名為.ino的檔案

- 設定Arduino的硬體選項
   - 工具 -> 開發板 : 選擇Arduino NANO
   - 工具 -> 處理器 : 選擇ATmega328P(Old Bootloader)
   - 工具 -> 序列埠 ：選擇Cageboard所在的COM Port

- 選擇左上角的箭頭按鈕進行上傳即可開始燒入程式