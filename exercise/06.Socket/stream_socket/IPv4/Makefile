all:
	make Diagram Stream
Diagram : Diagram/client.c Diagram/serve.c
	gcc -o Diagram/client Diagram/client.c
	gcc -o Diagram/serve Diagram/serve.c
Stream :  Stream/Client.c Stream/Serve.c
	gcc -o Stream/Client Stream/Client.c
	gcc -o Stream/Serve Stream/Serve.c
clean: 
	rm -rf Diagram/client Diagram/serve Stream/Client  Stream/Serve 
.PHONY :  Stream Diagram