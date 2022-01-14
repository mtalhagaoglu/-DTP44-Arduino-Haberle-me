Eğer aynı bilgisayara iki arduino bağlı olacak ise GÖNDERİCİ olan arduino daha küçük COM portuna bağlanmalıdır.

ArduinoConnection.py dosyası içerisindeki while döngüsü, başka bir komut gönderene kadar aynı komutu bir süre daha gönderir. İdeal hali 3-4 saniyede bir ekrana o anki durumla ilgili bilgi gönderilmesidir.

0 = Sorun Yok
1-50 = Birinci Şeritte Hata Var
51-99 = İkinci Şeritte Hata Var

Ekran Bağlantıları

D7, A5
D6, A4
D5, A3
D4, A2

RS, 7
EN1, 3
EN2, 4
EN3, 5
EN4, 6