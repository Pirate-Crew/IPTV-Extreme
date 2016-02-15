# Hello :D

build:	iptv.cpp
	@echo building...
	g++ -Wall -pedantic -lcurl -lpthread -std=c++11 iptv.cpp -o iptv_extreme

clean:
	@echo cleaning...
	$(RM) *.o
	$(RM) iptv_extreme

all:
	@make clean
	@make build
    
