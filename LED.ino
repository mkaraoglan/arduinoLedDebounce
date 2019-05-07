/*
  Mücahit Karaoğlan 15.06.2018
*/
const int programPin = 11;//hangi programda olduğunu gösteren ledin pini
const int buttonPin = 9;
const int ledPin = 10;
bool ledDurumu=1;
int dongu = 4;
int uzunluk = 1000;
bool program = 0;//0 kısa program, 1 uzun
unsigned long varis = 1000;
int lastButtonState = LOW; 
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 3000;
 
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(programPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  //butona basılmadığında buton durumu low yapılır o an lastDebounceTime değişkenine atılır
  //butona basılı tutulduğu sürece lastDebounceTime değişmez ve fark oluşur
  if(digitalRead(buttonPin)){
    //aradaki fark bizim basılı tutma süremiz kadar olduğunda işlemlere geçilir
    //lastButtonState tekrar LOW olabilmesi için bırakılması gerekir. Bu sayede tekrar döngüye girmez
    if( millis() - lastDebounceTime > debounceDelay && !lastButtonState){
      lastButtonState = HIGH;
      program = !program;//program değişir
      digitalWrite(programPin, program);//led ile gösterilir
      //programa göre debounceDelay ve dongu ayarlanır
      if(program == 0){
        debounceDelay=3000;
        dongu = 4;
      }
      else{
        debounceDelay=100;
        dongu = 8;     
      }
      //her şey sıfırlanır
      uzunluk = 1000;
      ledDurumu=1;
      varis = millis() + 1000;
      lastDebounceTime = millis();
    }
  }
  else{
    lastDebounceTime = millis();
    lastButtonState = LOW;
  }
  ledyak();
}

void ledyak(){
  //varış kodlarla 1 ya da 2 sn millis in ilerisinde ayarlanmıştır
  if( millis() < varis ){
    digitalWrite(ledPin, ledDurumu);
  }
  //eğer varış yani bitiş süresine gelirse LOW ya da HIGH ledDurumu değişir dongu azalır
  else{
    ledDurumu =! ledDurumu;
    digitalWrite(ledPin, ledDurumu);
    dongu--;
    //dongu tamamlandığında yanıp sönme 2 programda da 1 ya da 2 sn
    //dongu yanıp sönme 2 sayılır o yüzden 4 kısa için, 8 uzun için
    if(dongu == 0){
      uzunluk = (uzunluk == 1000) ? 2000 : 1000;
      dongu = (program == 0) ? 4 : 8;
    }
    varis += uzunluk;//varışa bir sonraki uzunluk eklenir
  }
}


