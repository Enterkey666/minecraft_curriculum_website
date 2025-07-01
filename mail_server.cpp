#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sstream>
#include <fstream>
#include <ctime>
#include "mail_sender.hpp"

int main() {
    MailSender sender;
    
    // テスト送信
    std::string to = "nayutaweb.marketing@gmail.com";
    std::string subject = "テストメール";
    std::string body = "これはテストメールです。";
    
    if (sender.sendMail(to, subject, body)) {
        std::cout << "メール送信成功" << std::endl;
    } else {
        std::cout << "メール送信失敗" << std::endl;
    }
    
    return 0;
} 