This code is for STM32F407VE microcontroller to receive data from ADS1299 over 8 channels. 
=====================

Data processing due BrainFlow https://brainflow.readthedocs.io/en/stable/  board_id: 17

File   
1.ADS_1299.c   - code for Atollic TrueSTUDIO for STM32 9.3.0  
1.ADS_1299.ioc - STM32CubeMX


#### 1.General pin information about ADS1299 signals  
1.1. Reset - to the low position - reset all settings
1.2.DRDY output - goes high when conversion starts and low when data is ready  
1.3  Two ways to read data:  
      - RDATA C1 - continuous read command  
      - RDATA data read which requires a command to load the input offset  
1.4. The amount of input data is 24 bits * 8 = 192 bits, and 24 status bits, in total we get 216 bits  
1.5 To receive data from the device after executing the RDATAC command, the START pin must be high, or a START command has been issued.  

#### 2. Конфигаруия регисторов управления
2.1 Запись в регистор
Три байта конфигурации регисторов 
0b11010110    
0b11010100
0b11100000

First command byte: 010r rrrr, where r rrrr is the starting register address.
Второй байт команды: 000n nnnn, где n nnnn - количество записываемых регистров - 1.
2.2 Чтения с регистрв, аналогично но первые четые бита из байта следующего формата
BYTE 1 = 0010 0000 

2.3 Скорость передач данных
Предполагая, что CLK составляет 2,048 МГц, тогда tSDECODE (4 tCLK) составляет 1,96 мкс. Когда SCLK составляет 16 МГц, один байт может быть передан за 500 нс. Это время передачи байтов не соответствует спецификации tSDECODE; поэтому должна быть вставлена задержка, чтобы конец второго байта приходил на 1,46 мкс позже.

#### 3. SCLK
tSCLK=500 ns - 2 MHz (12 page).












