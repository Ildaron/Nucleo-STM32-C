Кратко с мануала
1. Обшая информация
1.1. Reset - в низкое положение - сброс всех настроек
1.2. Выход DRDY - становится высоким, когда преобразования начинается, и низким когда данныее готовы
1.3  Два способа чтения данных: 
      - RDATAC1 - команда непрперывного чтения
      - RDATA -чтения данных при котором требуется команда для загрузки входного сдвига 
1.4. Количество входных данных составляет 24 бита*8 = 192 бита, и 24 бита состояния, в итоге мы получаем 216 битов
1.5 Чтобы получить данные с устройства после выполнения команды RDATAC,
Удостоверьтесь, что либо вывод START имеет высокий уровень, либо выдается команда START. 
Figure 46. - схема передачи данных

2. Конфигаруия регисторов управления
2.1 Запись в регистор
Три байта конфигурации регисторов (page 47)
0b11010110    
0b11010100
0b11100000
Схема отправки - Figure 49.
Причем преждем чем отправить данные регистра
First command byte: 010r rrrr, where r rrrr is the starting register address.
Второй байт команды: 000n nnnn, где n nnnn - количество записываемых регистров - 1.
2.2 Чтения с регистрв, аналогично но первые четые бита из байта следующего формата
BYTE 1 = 0010 0000 

2.3 Скорость передач данных
Предполагая, что CLK составляет 2,048 МГц, тогда tSDECODE (4 tCLK) составляет 1,96 мкс. Когда SCLK составляет 16 МГц, один байт может быть передан за 500 нс. Это время передачи байтов не соответствует спецификации tSDECODE; поэтому должна быть вставлена задержка, чтобы конец второго байта приходил на 1,46 мкс позже.

3. SCLK
tSCLK=500 ns - 2 MHz (12 page).











