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
2.2 AT+CIPMODE=0  - сервер может отправлять данные клиенту и может принимать данные от клиента
2.2 AT+CIPMUX=<mode> - возможность множественных соединений
    mode 1 — multiple connection
    AT+CIPMUX=1 
2.3 AT+CIPSERVER=1,8888 - Запускаем сервер на порту 8888
SocketTest 
2.4  Set PORT and IP and connect

