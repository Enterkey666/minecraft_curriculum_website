#ifndef MAIL_SENDER_HPP
#define MAIL_SENDER_HPP

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

class MailSender {
private:
    std::string smtp_server = "smtp.gmail.com";
    int smtp_port = 587;
    std::string username = "nayutaweb.marketing@gmail.com";
    std::string password = "your_app_password"; // Gmailのアプリパスワード
    
public:
    bool sendMail(const std::string& to, const std::string& subject, const std::string& body) {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            std::cerr << "Socket creation failed" << std::endl;
            return false;
        }
        
        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(smtp_port);
        server_addr.sin_addr.s_addr = inet_addr("173.194.76.108"); // smtp.gmail.comのIP
        
        if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            std::cerr << "Connection failed" << std::endl;
            close(sock);
            return false;
        }
        
        std::string response;
        char buffer[1024];
        
        // EHLO
        std::string ehlo = "EHLO localhost\r\n";
        send(sock, ehlo.c_str(), ehlo.length(), 0);
        recv(sock, buffer, sizeof(buffer), 0);
        
        // STARTTLS
        std::string starttls = "STARTTLS\r\n";
        send(sock, starttls.c_str(), starttls.length(), 0);
        recv(sock, buffer, sizeof(buffer), 0);
        
        // ここでTLSハンドシェイクを行う必要があります
        // 簡略化のため、実際の実装ではOpenSSLライブラリを使用
        
        // AUTH LOGIN
        std::string auth = "AUTH LOGIN\r\n";
        send(sock, auth.c_str(), auth.length(), 0);
        recv(sock, buffer, sizeof(buffer), 0);
        
        // ユーザー名（Base64エンコード）
        std::string encoded_username = base64_encode(username);
        send(sock, (encoded_username + "\r\n").c_str(), encoded_username.length() + 2, 0);
        recv(sock, buffer, sizeof(buffer), 0);
        
        // パスワード（Base64エンコード）
        std::string encoded_password = base64_encode(password);
        send(sock, (encoded_password + "\r\n").c_str(), encoded_password.length() + 2, 0);
        recv(sock, buffer, sizeof(buffer), 0);
        
        // MAIL FROM
        std::string mail_from = "MAIL FROM:<" + username + ">\r\n";
        send(sock, mail_from.c_str(), mail_from.length(), 0);
        recv(sock, buffer, sizeof(buffer), 0);
        
        // RCPT TO
        std::string rcpt_to = "RCPT TO:<" + to + ">\r\n";
        send(sock, rcpt_to.c_str(), rcpt_to.length(), 0);
        recv(sock, buffer, sizeof(buffer), 0);
        
        // DATA
        std::string data = "DATA\r\n";
        send(sock, data.c_str(), data.length(), 0);
        recv(sock, buffer, sizeof(buffer), 0);
        
        // メール本文
        std::string email_content = 
            "From: " + username + "\r\n"
            "To: " + to + "\r\n"
            "Subject: " + subject + "\r\n"
            "Content-Type: text/plain; charset=UTF-8\r\n"
            "\r\n"
            + body + "\r\n.\r\n";
        
        send(sock, email_content.c_str(), email_content.length(), 0);
        recv(sock, buffer, sizeof(buffer), 0);
        
        // QUIT
        std::string quit = "QUIT\r\n";
        send(sock, quit.c_str(), quit.length(), 0);
        
        close(sock);
        return true;
    }
    
private:
    std::string base64_encode(const std::string& input) {
        const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        std::string result;
        int val = 0, valb = -6;
        
        for (unsigned char c : input) {
            val = (val << 8) + c;
            valb += 8;
            while (valb >= 0) {
                result.push_back(chars[(val >> valb) & 0x3F]);
                valb -= 6;
            }
        }
        
        if (valb > -6) result.push_back(chars[((val << 8) >> (valb + 8)) & 0x3F]);
        while (result.size() % 4) result.push_back('=');
        
        return result;
    }
};

#endif // MAIL_SENDER_HPP 