import socket
s = socket.socket(
socket.AF_INET, socket.SOCK_STREAM)
s.connect(("ip_adress", port))

while True:
 data = str(s.recv(1024),encoding='utf-8')
 print(data)
