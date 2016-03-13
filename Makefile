# Hello :D

build:	iptv.cpp
	@echo building...
	g++ iptv.cpp -o iptv_extreme -Wall -pedantic -lcurl -lpthread -std=c++11

clean:
	@echo cleaning...
	$(RM) *.o
	$(RM) iptv_extreme

all:
	@make clean
	@make build
    
