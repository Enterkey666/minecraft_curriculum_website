# マインクラフトプログラミング教室 - プロダクトローンチサイト

## 概要
小学生から中学生向けのマインクラフトプログラミング教室のプロダクトローンチサイトです。プロダクトローンチを意識したデザインと動的な要素を取り入れ、各導線を強化しています。

## 特徴
- **プロダクトローンチ向けデザイン**: 緊急性を示すバナー、動的な背景、浮遊要素
- **C++メール送信機能**: フォーム送信時にnayutaweb.marketing@gmail.comにメールが届く
- **レスポンシブ対応**: スマートフォン、タブレット、PCに対応
- **動的要素**: スクロールトリガー、カウントアップアニメーション、パルス効果
- **ソーシャルプルーフ**: 統計情報と顧客の声で信頼性を向上

## ファイル構成
```
minecraft_curriculum_website/
├── index.html              # メインページ
├── contact.html            # お問い合わせページ
├── trial.html              # 無料体験レッスン申込ページ
├── details.html            # 詳細ページ
├── mail_server.cpp         # C++メール送信サーバー
├── mail_handler.cpp        # CGIメールハンドラー
├── Makefile                # コンパイル用Makefile
├── images/                 # 画像ファイル
│   ├── minecraft_education.png
│   ├── minecraft_coding.png
│   └── coding_with_minecraft.png
└── README.md               # このファイル
```

## セットアップ手順

### 1. C++プログラムのコンパイル
```bash
cd minecraft_curriculum_website
make
```

### 2. CGIハンドラーの配置
```bash
sudo cp mail_handler /usr/local/bin/
sudo chmod +x /usr/local/bin/mail_handler
```

### 3. Webサーバーの設定
Apacheの場合、CGIを有効にして以下のディレクトリを作成：
```bash
sudo mkdir -p /var/www/cgi-bin
sudo cp mail_handler /var/www/cgi-bin/
sudo chmod +x /var/www/cgi-bin/mail_handler
```

### 4. ローカルでの確認
```bash
# Pythonサーバーを使用
python3 -m http.server 8000

# またはNode.jsのhttp-serverを使用
npx http-server -p 8000
```

ブラウザで `http://localhost:8000` にアクセス

## メール送信機能
- お問い合わせフォームと無料体験レッスン申込フォームから送信
- C++のCGIハンドラーがnayutaweb.marketing@gmail.comにメールを送信
- Gmailのアプリパスワードが必要（mail_server.cpp内で設定）

## デザインの特徴
- **グラデーション背景**: 動的に変化する背景
- **浮遊パーティクル**: ページ全体に浮遊する要素
- **スクロールアニメーション**: 要素が画面に入るとアニメーション
- **緊急性バナー**: 限定キャンペーンの表示
- **ソーシャルプルーフ**: 統計情報と顧客の声
- **CTAボタン**: 目を引くアニメーション効果

## 技術スタック
- HTML5
- CSS3 (Tailwind CSS)
- JavaScript (ES6+)
- C++ (メール送信機能)
- CGI (フォーム処理)

## 注意事項
- C++プログラムを使用するには、OpenSSLライブラリが必要
- Gmailのアプリパスワードを設定する必要があります
- 本番環境では適切なセキュリティ設定を行ってください

## ライセンス
このプロジェクトは教育目的で作成されています。 