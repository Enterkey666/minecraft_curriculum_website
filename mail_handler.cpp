#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <map>
#include "mail_sender.hpp"

class MailHandler {
private:
    MailSender mailSender;
    
public:
    void handleContactForm() {
        std::cout << "Content-Type: text/html; charset=UTF-8\r\n\r\n";
        
        // POSTデータを読み取り
        std::string postData;
        std::getline(std::cin, postData);
        
        // フォームデータをパース
        std::map<std::string, std::string> formData = parseFormData(postData);
        
        std::string name = formData["name"];
        std::string email = formData["email"];
        std::string message = formData["message"];
        
        // メール本文を作成
        std::string subject = "マインクラフトプログラミング教室 - お問い合わせ";
        std::string body = 
            "新しいお問い合わせがありました。\n\n"
            "お名前: " + name + "\n"
            "メールアドレス: " + email + "\n"
            "メッセージ:\n" + message + "\n";
        
        // メール送信
        bool success = mailSender.sendMail("nayutaweb.marketing@gmail.com", subject, body);
        
        // レスポンスを返す
        if (success) {
            std::cout << "<!DOCTYPE html><html><head><meta charset='UTF-8'></head><body>";
            std::cout << "<h1>送信完了</h1><p>お問い合わせありがとうございます。</p>";
            std::cout << "<a href='index.html'>トップページに戻る</a></body></html>";
        } else {
            std::cout << "<!DOCTYPE html><html><head><meta charset='UTF-8'></head><body>";
            std::cout << "<h1>送信エラー</h1><p>申し訳ございません。送信に失敗しました。</p>";
            std::cout << "<a href='contact.html'>戻る</a></body></html>";
        }
    }
    
    void handleTrialForm() {
        std::cout << "Content-Type: text/html; charset=UTF-8\r\n\r\n";
        
        // POSTデータを読み取り
        std::string postData;
        std::getline(std::cin, postData);
        
        // フォームデータをパース
        std::map<std::string, std::string> formData = parseFormData(postData);
        
        std::string name = formData["name"];
        std::string email = formData["email"];
        std::string date = formData["date"];
        
        // メール本文を作成
        std::string subject = "マインクラフトプログラミング教室 - 無料体験レッスン申込";
        std::string body = 
            "無料体験レッスンの申し込みがありました。\n\n"
            "お名前: " + name + "\n"
            "メールアドレス: " + email + "\n"
            "希望日: " + date + "\n";
        
        // メール送信
        bool success = mailSender.sendMail("nayutaweb.marketing@gmail.com", subject, body);
        
        // レスポンスを返す
        if (success) {
            std::cout << "<!DOCTYPE html><html><head><meta charset='UTF-8'></head><body>";
            std::cout << "<h1>申込完了</h1><p>無料体験レッスンのお申し込みありがとうございます。</p>";
            std::cout << "<a href='index.html'>トップページに戻る</a></body></html>";
        } else {
            std::cout << "<!DOCTYPE html><html><head><meta charset='UTF-8'></head><body>";
            std::cout << "<h1>申込エラー</h1><p>申し訳ございません。申し込みに失敗しました。</p>";
            std::cout << "<a href='trial.html'>戻る</a></body></html>";
        }
    }
    
private:
    std::map<std::string, std::string> parseFormData(const std::string& data) {
        std::map<std::string, std::string> result;
        std::stringstream ss(data);
        std::string item;
        
        while (std::getline(ss, item, '&')) {
            size_t pos = item.find('=');
            if (pos != std::string::npos) {
                std::string key = item.substr(0, pos);
                std::string value = item.substr(pos + 1);
                // URLデコード
                value = urlDecode(value);
                result[key] = value;
            }
        }
        
        return result;
    }
    
    std::string urlDecode(const std::string& str) {
        std::string result;
        for (size_t i = 0; i < str.length(); ++i) {
            if (str[i] == '%' && i + 2 < str.length()) {
                int value;
                std::istringstream iss(str.substr(i + 1, 2));
                iss >> std::hex >> value;
                result += static_cast<char>(value);
                i += 2;
            } else if (str[i] == '+') {
                result += ' ';
            } else {
                result += str[i];
            }
        }
        return result;
    }
};

int main() {
    MailHandler handler;
    
    // リクエストメソッドを確認
    char* method = std::getenv("REQUEST_METHOD");
    
    if (method && std::string(method) == "POST") {
        // リクエストURIを確認して適切なハンドラーを呼び出し
        char* uri = std::getenv("REQUEST_URI");
        if (uri) {
            std::string uriStr(uri);
            if (uriStr.find("contact") != std::string::npos) {
                handler.handleContactForm();
            } else if (uriStr.find("trial") != std::string::npos) {
                handler.handleTrialForm();
            }
        }
    }
    
    return 0;
} 