Settings for ESP8266  ESP-01
1.1 Connect to computer by adapter ttl/usb
1.2 Use terminal, for  example CoolTerm  
3. Commands
AT, receive - OK
AT+CWMODE=1  - start wifi
AT+CWLAP - to see available wifi networks
AT+CWJAP="name of network","password" - connect to the network
AT+CWQAP - disconnect from network
AT+CIFSR - to see IP


2. TCP-server
2.1 Connect to wifi
2.2 AT+CIPMODE=0  - сервер может отправлять данные клиенту и может принимать данные от клиента   (AT+CIPSERVER=0, AT+CIPMUX=0)
2.2 AT+CIPMUX=<mode> - возможность множественных соединений
    mode 1 — multiple connection
    AT+CIPMUX=1 
2.3 AT+CIPSERVER=1,8888 - Запускаем сервер на порту 8888

SocketTest Send from computer to ESP
2.4 Set PORT and IP and connect
2.5 Закрыть соединение можно командой AT+CIPCLOSE=0 
           
           Send from ESP to computer   (not correct - AT+CIPSEND=0,16 > Ping Habrahabr SEND) 
        AT+CIPSEND=0,5
        подождать пока ESP ответит символом
        >
        И после того отдать 5 символов.
      
