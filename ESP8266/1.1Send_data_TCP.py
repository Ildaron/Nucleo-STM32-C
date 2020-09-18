  
import socket
s = socket.socket(family = socket.AF_INET, type = socket.SOCK_STREAM)
s.connect (("ESP_IP", 80))

while True:
 s.send(b"Hello!\n")
 s.sendall(b'Hello, world')
 data = s.recv(1024)
 data = str(s.recv(1024),encoding='utf-8')

