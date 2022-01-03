Eğer aynı bilgisayara iki arduino bağlı olacak ise GÖNDERİCİ olan arduino daha küçük COM portuna bağlanmalıdır.

ArduinoConnection.py dosyası içerisindeki while döngüsü, başka bir komut gönderene kadar aynı komutu bir süre daha gönderir. İdeal hali 3-4 saniyede bir ekrana o anki durumla ilgili bilgi gönderilmesidir.

Ekran için olan komutlar 1000-1999 aralığındadır.
1000 = Sorun yok
1001 = 1. Şeritte kaza var
1002 = 1. Şeritte kaza var
1003 = 1. Şeritte kaza var
1004 = 2. Şeritte kaza var
1005 = 2. Şeritte kaza var
1006 = 2. Şeritte kaza var

Ekran Bağlantıları

D7, A5
D6, A4
D5, A3
D3, A2

RS, 7
EN1, 3
EN2, 4
EN3, 5
EN4, 6