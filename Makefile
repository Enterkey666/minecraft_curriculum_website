CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
LIBS = -lssl -lcrypto

all: mail_server mail_handler

mail_server: mail_server.cpp
	$(CXX) $(CXXFLAGS) -o mail_server mail_server.cpp $(LIBS)

mail_handler: mail_handler.cpp
	$(CXX) $(CXXFLAGS) -o mail_handler mail_handler.cpp $(LIBS)

clean:
	rm -f mail_server mail_handler

install: all
	cp mail_handler /usr/local/bin/
	chmod +x /usr/local/bin/mail_handler

.PHONY: all clean install 