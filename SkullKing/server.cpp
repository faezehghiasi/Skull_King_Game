#include "server.h"
#include "ui_server.h"
#include<QDebug>
#include"clientorserver.h"
#include"ui_clientorserver.h"
#include"menuselection.h"
#include<QMessageBox>
#include<QDataStream>
#include<QFile>
#include<QRandomGenerator>
#include<QTime>
Server * srv;
Server::Server(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);
    ui->setupUi(this);
    server = new QTcpServer;
    server_card.cards_button = new QPushButton(this);
    server_card.cards_button->setGeometry(290,290,101,141);
    client_card.cards_button = new QPushButton(this);
    client_card.cards_button->setGeometry(210,240,101,141);
    server_card.cards_button->hide();
    client_card.cards_button->hide();

}
//************************************************************
Server::~Server()
{
    delete ui;
}
//**************************************************************
void Server::newConnection(){
   socket = server->nextPendingConnection();
   ClientOrServer::server_label->setGeometry(80,280,513,51);
   ClientOrServer::server_label->setStyleSheet("font: 14pt Showcard Gothic; color: rgb(8, 8, 8);");
   ClientOrServer::server_label->setText("A new player has been added to the game...");
   emit changePage();
   connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
   connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()));

}
//*****************************************************************
void Server :: readyRead(){

    QByteArray file_content = socket->readAll();
          QFile file("recivedCard.bin");
          if(!file.open(QIODevice::WriteOnly)){
              qDebug()<<"file can not open";
              return;
          }
          file.write(file_content);
          file .close();
          readFromFileCards("recivedCard.bin",recivedCard);
          if(recivedCard.size()==1){

              currentPlayer.set_turn(true);
              server_card = recivedCard[0];
              set_picture(server_card);

         }
         else{

            currentPlayer.set_randomCards(recivedCard,currentPlayer.get_countOfTurn());
          }

}
//*****************************************************************
void Server::disconnected(){

    socket->close();
}
//*******************************************************************
void Server::creation(){
    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
     for(int nIter=0; nIter<list.count(); nIter++)
      {
        if(!list[nIter].isLoopback())
              if (list[nIter].protocol() == QAbstractSocket::IPv4Protocol ){
           serverIp= list[nIter].toString();
          break;
              }
      }
    QHostAddress myIP;
    myIP.setAddress(serverIp);
    serverIp= "IP: " + serverIp;
    ClientOrServer::ip_label->setText(serverIp);
    if(!server->listen(myIP,9999)){
        QMessageBox MQ;
        MQ.critical(this,"Error","server can not start");
    }
}
//***************************************************************************
QTcpSocket* Server::get_socket()
{
    return socket;
}
//*************************************************************************
QVector<buttons> Server::get_buttons(){return pushButtons;}
//***************************************************************************
void Server::showCards(QList<cards> cCards){
    qDebug()<<cCards.size();
   switch(cCards.size()){
   case 2:{
       for(int i = 0;i<2;i++){
           buttons QP;
           QP.cards_button = new QPushButton(this);
           QP.thisCard=cCards[i];
            pushButtons.append(QP);
       }
       int X =190;
       int Y = 490;
       int height = 181;
       int width =101;
       for(int i=0;i<2;i++,X+=120){
           pushButtons[i].cards_button->setGeometry(X,Y,width,height);
          pushButtons[i]. cards_button->show();
       }
   }
             break;
   case 4:{
       for(int i = 0;i<4;i++){
           buttons QP;
           QP.cards_button = new QPushButton(this);
           QP.thisCard=cCards[i];
            pushButtons.append(QP);
       }
       int X =100;
       int Y = 510;
       int height = 171;
       int width =101;
       for(int i=0;i<2;i++,X+=90,Y-=10){
           pushButtons[i].cards_button->setGeometry(X,Y,width,height);
           pushButtons[i].cards_button->show();
       }
       Y+=10;
       for(int i=2;i<4;i++,X+=90,Y+=10){
           pushButtons[i].cards_button->setGeometry(X,Y,width,height);
           pushButtons[i].cards_button->show();
       }
   }
              break;
   case 6:{
       for(int i = 0;i<6;i++){
           buttons QP;
           QP.cards_button = new QPushButton(this);
           QP.thisCard=cCards[i];
            pushButtons.append(QP);
       }
       int X = 90;
       int Y = 530;
       int height = 151;
       int width =91;
       for(int i=0;i<3;i++,X+=70,Y-=10){
           pushButtons[i].cards_button->setGeometry(X,Y,width,height);
           pushButtons[i].cards_button->show();
       }
       Y+=10;
       for(int i=3;i<6;i++,X+=70,Y+=10){
           pushButtons[i].cards_button->setGeometry(X,Y,width,height);
           pushButtons[i].cards_button->show();
       }
   }
              break;
   case 8:{
       for(int i = 0;i<8;i++){
           buttons QP;
           QP.cards_button = new QPushButton(this);
           QP.thisCard=cCards[i];
            pushButtons.append(QP);
       }
       int X = 60;
       int Y = 540;
       int height = 131;
       int width =81;
       for(int i=0;i<4;i++,X+=60,Y-=10){
           pushButtons[i].cards_button->setGeometry(X,Y,width,height);
           pushButtons[i].cards_button->show();
       }
       Y+=10;
       for(int i=4;i<8;i++,X+=60,Y+=10){
           pushButtons[i].cards_button->setGeometry(X,Y,width,height);
           pushButtons[i].cards_button->show();
       }
   }
              break;
   case 10:{
       for(int i = 0;i<10;i++){
           buttons QP;
           QP.cards_button = new QPushButton(this);
           QP.thisCard=cCards[i];
            pushButtons.append(QP);
       }
       int X = 40;
       int Y = 550;
       int height = 131;
       int width =71;
       for(int i=0;i<5;i++,X+=50,Y-=10){
           pushButtons[i].cards_button->setGeometry(X,Y,width,height);
           pushButtons[i].cards_button->show();
       }
         Y+=10;
       for(int i=5;i<10;i++,X+=50,Y+=10){
           pushButtons[i].cards_button->setGeometry(X,Y,width,height);
           pushButtons[i].cards_button->show();
       }
   }
              break;
   case 12:{
       for(int i = 0;i<12;i++){
           buttons QP;
           QP.cards_button = new QPushButton(this);
           QP.thisCard=cCards[i];
            pushButtons.append(QP);
       }
       int X = 5;
       int Y = 560;
       int height = 131;
       int width =71;
       for(int i=0;i<6;i++,X+=50,Y-=10){
           pushButtons[i].cards_button->setGeometry(X,Y,width,height);
           pushButtons[i].cards_button->show();
       }
         Y+=10;
       for(int i=6;i<12;i++,X+=50,Y+=10){
           pushButtons[i].cards_button->setGeometry(X,Y,width,height);
           pushButtons[i].cards_button->show();
       }
   }
              break;
   case 14: {
       for(int i = 0;i<14;i++){
           buttons QP;
           QP.cards_button = new QPushButton(this);
           QP.thisCard=cCards[i];
            pushButtons.append(QP);
       }
       int X =10;
       int Y = 540;
       int height = 140;
       int width =60;
       for(int i=0;i<7;i++,X+=42,Y-=10){
           pushButtons[i].cards_button->setGeometry(X,Y,width,height);
           pushButtons[i].cards_button->show();
       }
         Y+=10;
       for(int i=7;i<14;i++,X+=42,Y+=10){
           pushButtons[i].cards_button->setGeometry(X,Y,width,height);
           pushButtons[i].cards_button->show();
       }
   }
              break;

  }

//   connect(pushButtons[0].cards_button,SIGNAL(clicked()),this,SLOT( void on_Buttons0_clicked()));
//      connect(pushButtons[1].cards_button,SIGNAL(clicked()),this,SLOT( void on_Buttons1_clicked()));
//      connect(pushButtons[2].cards_button,SIGNAL(clicked()),this,SLOT( void on_Buttons2_clicked()));
//      connect(pushButtons[3].cards_button,SIGNAL(clicked()),this,SLOT( void on_Buttons3_clicked()));
//      connect(pushButtons[4].cards_button,SIGNAL(clicked()),this,SLOT( void on_Buttons4_clicked()));
//      connect(pushButtons[5].cards_button,SIGNAL(clicked()),this,SLOT( void on_Buttons5_clicked()));
//      connect(pushButtons[6].cards_button,SIGNAL(clicked()),this,SLOT( void on_Buttons6_clicked()));
//      connect(pushButtons[7].cards_button,SIGNAL(clicked()),this,SLOT( void on_Buttons7_clicked()));
//      connect(pushButtons[8].cards_button,SIGNAL(clicked()),this,SLOT( void on_Buttons8_clicked()));
//      connect(pushButtons[9].cards_button,SIGNAL(clicked()),this,SLOT( void on_Buttons9_clicked()));
//      connect(pushButtons[10].cards_button,SIGNAL(clicked()),this,SLOT( void on_Buttons10_clicked()));
//      connect(pushButtons[11].cards_button,SIGNAL(clicked()),this,SLOT( void on_Buttons11_clicked()));
//      connect(pushButtons[12].cards_button,SIGNAL(clicked()),this,SLOT( void on_Buttons12_clicked()));
//      connect(pushButtons[13].cards_button,SIGNAL(clicked()),this,SLOT( void on_Buttons13_clicked()));


}
//***************************************************************************
void Server::whoShouldStartTheGameFirst(){
    //delay function......
    QTime dietime=QTime::currentTime().addMSecs(3000);
    while(QTime::currentTime()<dietime)
    QCoreApplication::processEvents(QEventLoop::AllEvents,100);

    int server_number =( QRandomGenerator::global()->generate()%8)+1;
    int client_number =( QRandomGenerator::global()->generate()%8)+1;
    tab:if(server_number>client_number){
        currentPlayer.set_turn(true);
    }
    else if(server_number>client_number){
       currentPlayer.set_turn(false);
    }
    else{
        server_number =( QRandomGenerator::global()->generate()%8)+1;
        client_number =( QRandomGenerator::global()->generate()%8)+1;
        goto tab;
    }
    server_card.thisCard.setId(3);
    server_card.thisCard.setNumber(server_number);
    server_card.thisCard.setValue(server_number);
    client_card.thisCard.setId(3);
    client_card.thisCard.setNumber(client_number);
    client_card.thisCard.setValue(client_number);
    sendCard.push_back(server_card.thisCard);
    sendCard.push_back(client_card.thisCard);
    writeToFileCards("sendCard.bin",sendCard);
    QFile file("sendCard.bin");
    file.open(QFile::ReadOnly | QFile::Text);
    QByteArray file_content = file.readAll();
    socket->write(file_content);
   // socket->waitForBytesWritten(3000);
    socket->flush();
    file.close();
}
//*************************************************************************************
void Server::set_picture(struct buttons crd){

    switch(crd.thisCard.getId()){
    case 1:{
        switch(crd.thisCard.getNumber()){
        case 1:
            crd.cards_button->setStyleSheet("border-image: url(:/resource/treasure1.png);");
            crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/treasure1.png width=150 height=200/></p></body></html>");
            crd.cards_button->show();
            break;
        case 2:
            crd.cards_button->setStyleSheet("border-image: url(:/resource/treasure2.png);");
             crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/treasure2.png width=150 height=200/></p></body></html>");
            crd.cards_button->show();
            break;
        case 3:
            crd.cards_button->setStyleSheet("border-image: url(:/resource/treasure3.png);");
             crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/treasure3.png width=150 height=200/></p></body></html>");
             crd.cards_button->show();
            break;
        case 4:
            crd.cards_button->setStyleSheet("border-image: url(:/resource/treasure4.png);");
             crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/treasure4.png width=150 height=200/></p></body></html>");
            break;
        case 5:
            crd.cards_button->setStyleSheet("border-image: url(:/resource/treasure5.png);");
             crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/treasure5.png width=150 height=200/></p></body></html>");
                crd.cards_button->show();
            break;
        case 6:
            crd.cards_button->setStyleSheet("border-image: url(:/resource/treasure6.png);");
             crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/treasure6.png width=150 height=200/></p></body></html>");
            crd.cards_button->show();
            break;
        case 7:
            crd.cards_button->setStyleSheet("border-image: url(:/resource/treasure7.png);");
             crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/treasure7.png width=150 height=200/></p></body></html>");
           crd.cards_button->show();
            break;
        case 8:
            crd.cards_button->setStyleSheet("border-image: url(:/resource/treasure8.png);");
             crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/treasure8.png width=150 height=200/></p></body></html>");
            crd.cards_button->show();
            break;
        }

    }
        break;
    case 2:
        switch(crd.thisCard.getNumber()){
        case 1:
            crd.cards_button->setStyleSheet("border-image: url(:/resource/mapcard1.png);");
            crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/mapcard1.png width=150 height=200/></p></body></html>");
           crd.cards_button->show();
            break;
        case 2:
            crd.cards_button->setStyleSheet("border-image: url(:/resource/mapcard2.png);");
             crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/mapcard2.png width=150 height=200/></p></body></html>");
          crd.cards_button->show();
            break;
        case 3:
           crd.cards_button->setStyleSheet("border-image: url(:/resource/mapcard3.png);");
            crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/mapcard3.png width=150 height=200/></p></body></html>");
          crd.cards_button->show();
            break;
        case 4:
            crd.cards_button->setStyleSheet("border-image: url(:/resource/mapcard4.png);");
             crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/mapcard4.png width=150 height=200/></p></body></html>");
           crd.cards_button->show();
            break;
        case 5:
            crd.cards_button->setStyleSheet("border-image: url(:/resource/mapcard5.png);");
             crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/mapcard5.png width=150 height=200/></p></body></html>");
           crd.cards_button->show();
            break;
        case 6:
            crd.cards_button->setStyleSheet("border-image: url(:/resource/mapcard6.png);");
             crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/mapcard6.png width=150 height=200/></p></body></html>");
            crd.cards_button->show();
            break;
        case 7:
           crd.cards_button->setStyleSheet("border-image: url(:/resource/mapcard7.png);");
            crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/mapcard7.png width=150 height=200/></p></body></html>");
           crd.cards_button->show();
            break;
        case 8:
            crd.cards_button->setStyleSheet("border-image: url(:/resource/mapcard8.png);");
             crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/mapcard8.png width=150 height=200/></p></body></html>");
           crd.cards_button->show();
            break;
        }
        break;
    case 3:
        switch(crd.thisCard.getNumber()){
        case 1:
            crd.cards_button->setStyleSheet("border-image: url(:/resource/parrot1.png);");
            crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/parrot1.png  width=150 height=200 /></p></body></html>");
           crd.cards_button->show();
            break;
        case 2:
           crd.cards_button->setStyleSheet("border-image: url(:/resource/parrot2.png);");
           crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/parrot2.png  width=150 height=200 /></p></body></html>");
           crd.cards_button->show();
            break;
        case 3:
            crd.cards_button->setStyleSheet("border-image: url(:/resource/parrot3.png);");
            crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/parrot3.png  width=150 height=200 /></p></body></html>");
           crd.cards_button->show();
            break;
        case 4:
            crd.cards_button->setStyleSheet("border-image: url(:/resource/parrot4.png);");
            crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/parrot4.png  width=150 height=200 /></p></body></html>");
           crd.cards_button->show();
            break;
        case 5:
              crd.cards_button->setStyleSheet("border-image: url(:/resource/parrot5.png);");
              crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/parrot5.png  width=150 height=200 /></p></body></html>");
           crd.cards_button->show();
            break;
        case 6:
               crd.cards_button->setStyleSheet("border-image: url(:/resource/parrot6.png);");
               crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/parrot6.png  width=150 height=200 /></p></body></html>");
           crd.cards_button->show();
            break;
        case 7:
             crd.cards_button->setStyleSheet("border-image: url(:/resource/parrot7.png);");
             crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/parrot7.png  width=150 height=200 /></p></body></html>");
           crd.cards_button->show();
            break;
        case 8:
            crd.cards_button->setStyleSheet("border-image: url(:/resource/parrot8.png);");
            crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/parrot8.png  width=150 height=200 /></p></body></html>");
            crd.cards_button->show();
            break;
        }
        break;
    case 4:
        switch(crd.thisCard.getNumber()){
        case 1:
            crd.cards_button->setStyleSheet("border-image: url(:/resource/flagcard1.png);");
            crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/flagcard1.png width=150 height=200/></p></body></html>");
           crd.cards_button->show();
            break;
        case 2:
            crd.cards_button->setStyleSheet("border-image: url(:/resource/flagcard2.png);");
            crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/flagcard2.png width=150 height=200/></p></body></html>");
          crd.cards_button->show();
            break;
        case 3:
             crd.cards_button->setStyleSheet("border-image: url(:/resource/flagcard3.png);");
             crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/flagcard3.png width=150 height=200/></p></body></html>");
           crd.cards_button->show();
            break;
        case 4:
             crd.cards_button->setStyleSheet("border-image: url(:/resource/flagcard4.png);");
             crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/flagcard4.png width=150 height=200/></p></body></html>");
           crd.cards_button->show();
            break;
        case 5:
              crd.cards_button->setStyleSheet("border-image: url(:/resource/flagcard5.png);");
              crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/flagcard5.png width=150 height=200/></p></body></html>");
           crd.cards_button->show();
            break;
        case 6:
               crd.cards_button->setStyleSheet("border-image: url(:/resource/flagcard6.png);");
               crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/flagcard6.png width=150 height=200/></p></body></html>");
           crd.cards_button->show();
            break;
        case 7:
             crd.cards_button->setStyleSheet("border-image: url(:/resource/flagcard7.png);");
             crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/flagcard7.png width=150 height=200/></p></body></html>");
            crd.cards_button->show();
            break;
        case 8:
             crd.cards_button->setStyleSheet("border-image: url(:/resource/flagcard8.png);");
             crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/flagcard8.png width=150 height=200/></p></body></html>");
             crd.cards_button->show();
            break;
        }
        break;
    case 5:
         crd.cards_button->setStyleSheet("border-image: url(:/resource/king.png);");
         crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/king.png width=150 height=200/></p></body></html>");
         crd.cards_button->show();
        break;
    case 6:
        crd.cards_button->setStyleSheet("border-image: url(:/resource/queen.png);");
        crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/queen.png width=150 height=200/></p></body></html>");
        crd.cards_button->show();
        break;
    case 7:
        crd.cards_button->setStyleSheet("border-image: url(:/resource/dozd.png);");
        crd.cards_button->setToolTip("<html><head/><body><p><img src=:/resource/dozd.png width=150 height=200/></p></body></html>");
        crd.cards_button->show();
        break;
    }
}
//*************************************************************************************
void Server::availbleCards(buttons rivalCard){
    //mitooni bhine tar koni
    int rivalCardId=rivalCard.thisCard.getId();
    //simple cards......
    if(rivalCardId==1 ||rivalCardId==2||rivalCardId==3)
    {
        auto findIt=find_if(pushButtons.begin(),pushButtons.end(),[rivalCardId](buttons currbut){return(currbut.thisCard.getId()==rivalCardId);});
        //age dashte bashe.....
        if(findIt!=pushButtons.end()){
            for(auto it=pushButtons.begin();it!=pushButtons.end();it++){
                if(it->thisCard.getId()!=rivalCardId && it->thisCard.getId()!=5 &&it->thisCard.getId()!=6 &&it->thisCard.getId()!=7){
                    it->cards_button->disconnect();
                }
            }
        }
        //age nadashte bashe...........
        else{
            int counter=0;
                counter=count_if(pushButtons.begin(),pushButtons.end(),[](buttons currbut){return (currbut.thisCard.getId()>=4);});
            if(counter>0){
                for(auto it=pushButtons.begin();it!=pushButtons.end();it++){
                    if(it->thisCard.getId()!=rivalCardId &&it->thisCard.getId()!=5 &&it->thisCard.getId()!=6 &&it->thisCard.getId()!=7 && it->thisCard.getId()!=4)
                       it->cards_button->disconnect();
                 }
           }
        }
        return;
    }

    //hokm.................
    else if(rivalCardId==4){
        //age hokm dashtebashe
        auto it=find_if(pushButtons.begin(),pushButtons.end(),[](buttons b){return(b.thisCard.getId()==4);});
        if(it!=pushButtons.end()){
            for(auto it=pushButtons.begin();it!=pushButtons.end();it++){
                if(it->thisCard.getId()!=4) it->cards_button->disconnect();
            }
        }
        //age hokm nadashte bashe
        else{
            int counter=count_if(pushButtons.begin(),pushButtons.end(),[](buttons b){return (b.thisCard.getId()>=5);});
            //age cart naghsh dashte bashe
            if(counter>0){
                for(auto it=pushButtons.begin();it!=pushButtons.end();it++){
                    if(it->thisCard.getId()==1 ||it->thisCard.getId()==2||it->thisCard.getId()==3)it->cards_button->disconnect();
                }
            }
        }
        return;
    }

    //important cards......................
   //fk konam hamaro mitoone bazi kone
}
//********************************************************************************
void Server :: set_client_card(struct buttons cCard){
    client_card =cCard;
}
//********************************************************************************************
void Server :: set_server_card(struct buttons sCard){
    server_card =sCard;
}
//********************************************************************************************
buttons Server::get_client_card(){
    return client_card;
}
//**********************************************************************************************
buttons Server::get_server_card(){
    return server_card;
}
//*************************************************************************************************
void Server::on_Buttons0_clicked(){
    if(!currentPlayer.get_turn()){
        QMessageBox MQ;
        MQ.warning(0,"","it's not you'r turn...");
        return;
    }
    client_card = pushButtons[0];
    sendCard.push_back(pushButtons[0].thisCard);
    writeToFileCards("sendCard.bin",sendCard);
    QFile file("sendCard.bin");
    file.open(QFile::ReadOnly | QFile::Text);
    QByteArray file_content = file.readAll();

    /// animaition

    socket->write(file_content);
    socket->flush();
    file.close();
    currentPlayer.set_turn(false);

}
//**************************************************************************************************
void Server::on_Buttons1_clicked(){
    if(!currentPlayer.get_turn()){
        QMessageBox MQ;
        MQ.warning(0,"","it's not you'r turn...");
        return;
    }
    client_card = pushButtons[1];
    sendCard.push_back(pushButtons[1].thisCard);
    writeToFileCards("sendCard.bin",sendCard);
    QFile file("sendCard.bin");
    file.open(QFile::ReadOnly | QFile::Text);
    QByteArray file_content = file.readAll();

    /// animaition

    socket->write(file_content);
    socket->flush();
    file.close();
    currentPlayer.set_turn(false);

}
//**************************************************************************************************
void Server::on_Buttons2_clicked(){
    if(!currentPlayer.get_turn()){
        QMessageBox MQ;
        MQ.warning(0,"","it's not you'r turn...");
        return;
    }
    client_card = pushButtons[2];
    sendCard.push_back(pushButtons[2].thisCard);
    writeToFileCards("sendCard.bin",sendCard);
    QFile file("sendCard.bin");
    file.open(QFile::ReadOnly | QFile::Text);
    QByteArray file_content = file.readAll();

    /// animaition

    socket->write(file_content);
    socket->flush();
    file.close();
    currentPlayer.set_turn(false);

}
//**************************************************************************************************
void Server::on_Buttons3_clicked(){
    if(!currentPlayer.get_turn()){
        QMessageBox MQ;
        MQ.warning(0,"","it's not you'r turn...");
        return;
    }
    client_card = pushButtons[3];
    sendCard.push_back(pushButtons[3].thisCard);
    writeToFileCards("sendCard.bin",sendCard);
    QFile file("sendCard.bin");
    file.open(QFile::ReadOnly | QFile::Text);
    QByteArray file_content = file.readAll();

    /// animaition

    socket->write(file_content);
    socket->flush();
    file.close();
    currentPlayer.set_turn(false);

}
//**************************************************************************************************
void Server::on_Buttons4_clicked(){
    if(!currentPlayer.get_turn()){
        QMessageBox MQ;
        MQ.warning(0,"","it's not you'r turn...");
        return;
    }
    client_card = pushButtons[4];
    sendCard.push_back(pushButtons[4].thisCard);
    writeToFileCards("sendCard.bin",sendCard);
    QFile file("sendCard.bin");
    file.open(QFile::ReadOnly | QFile::Text);
    QByteArray file_content = file.readAll();

    /// animaition

    socket->write(file_content);
    socket->flush();
    file.close();
    currentPlayer.set_turn(false);

}
//**************************************************************************************************
void Server::on_Buttons5_clicked(){
    if(!currentPlayer.get_turn()){
        QMessageBox MQ;
        MQ.warning(0,"","it's not you'r turn...");
        return;
    }
    client_card = pushButtons[5];
    sendCard.push_back(pushButtons[5].thisCard);
    writeToFileCards("sendCard.bin",sendCard);
    QFile file("sendCard.bin");
    file.open(QFile::ReadOnly | QFile::Text);
    QByteArray file_content = file.readAll();

    /// animaition

    socket->write(file_content);
    socket->flush();
    file.close();
    currentPlayer.set_turn(false);

}
//**************************************************************************************************
void Server::on_Buttons6_clicked(){
    if(!currentPlayer.get_turn()){
        QMessageBox MQ;
        MQ.warning(0,"","it's not you'r turn...");
        return;
    }
    client_card = pushButtons[6];
    sendCard.push_back(pushButtons[6].thisCard);
    writeToFileCards("sendCard.bin",sendCard);
    QFile file("sendCard.bin");
    file.open(QFile::ReadOnly | QFile::Text);
    QByteArray file_content = file.readAll();

    /// animaition

    socket->write(file_content);
    socket->flush();
    file.close();
    currentPlayer.set_turn(false);

}
//**************************************************************************************************
void Server::on_Buttons7_clicked(){
    if(!currentPlayer.get_turn()){
        QMessageBox MQ;
        MQ.warning(0,"","it's not you'r turn...");
        return;
    }
    client_card = pushButtons[7];
    sendCard.push_back(pushButtons[7].thisCard);
    writeToFileCards("sendCard.bin",sendCard);
    QFile file("sendCard.bin");
    file.open(QFile::ReadOnly | QFile::Text);
    QByteArray file_content = file.readAll();

    /// animaition

    socket->write(file_content);
    socket->flush();
    file.close();
    currentPlayer.set_turn(false);

}
//**************************************************************************************************
void Server::on_Buttons8_clicked(){
    if(!currentPlayer.get_turn()){
        QMessageBox MQ;
        MQ.warning(0,"","it's not you'r turn...");
        return;
    }
    client_card = pushButtons[8];
    sendCard.push_back(pushButtons[8].thisCard);
    writeToFileCards("sendCard.bin",sendCard);
    QFile file("sendCard.bin");
    file.open(QFile::ReadOnly | QFile::Text);
    QByteArray file_content = file.readAll();

    /// animaition

    socket->write(file_content);
    socket->flush();
    file.close();
    currentPlayer.set_turn(false);

}
//**************************************************************************************************
void Server::on_Buttons9_clicked(){
    if(!currentPlayer.get_turn()){
        QMessageBox MQ;
        MQ.warning(0,"","it's not you'r turn...");
        return;
    }
    client_card = pushButtons[9];
    sendCard.push_back(pushButtons[9].thisCard);
    writeToFileCards("sendCard.bin",sendCard);
    QFile file("sendCard.bin");
    file.open(QFile::ReadOnly | QFile::Text);
    QByteArray file_content = file.readAll();

    /// animaition

    socket->write(file_content);
    socket->flush();
    file.close();
    currentPlayer.set_turn(false);

}
//**************************************************************************************************
void Server::on_Buttons10_clicked(){
    if(!currentPlayer.get_turn()){
        QMessageBox MQ;
        MQ.warning(0,"","it's not you'r turn...");
        return;
    }
    client_card = pushButtons[10];
    sendCard.push_back(pushButtons[10].thisCard);
    writeToFileCards("sendCard.bin",sendCard);
    QFile file("sendCard.bin");
    file.open(QFile::ReadOnly | QFile::Text);
    QByteArray file_content = file.readAll();

    /// animaition

    socket->write(file_content);
    socket->flush();
    file.close();
    currentPlayer.set_turn(false);

}
//**************************************************************************************************
void Server::on_Buttons11_clicked(){
    if(!currentPlayer.get_turn()){
        QMessageBox MQ;
        MQ.warning(0,"","it's not you'r turn...");
        return;
    }
    client_card = pushButtons[11];
    sendCard.push_back(pushButtons[11].thisCard);
    writeToFileCards("sendCard.bin",sendCard);
    QFile file("sendCard.bin");
    file.open(QFile::ReadOnly | QFile::Text);
    QByteArray file_content = file.readAll();

    /// animaition

    socket->write(file_content);
    socket->flush();
    file.close();
    currentPlayer.set_turn(false);

}
//**************************************************************************************************
void Server::on_Buttons12_clicked(){
    if(!currentPlayer.get_turn()){
        QMessageBox MQ;
        MQ.warning(0,"","it's not you'r turn...");
        return;
    }
    client_card = pushButtons[12];
    sendCard.push_back(pushButtons[12].thisCard);
    writeToFileCards("sendCard.bin",sendCard);
    QFile file("sendCard.bin");
    file.open(QFile::ReadOnly | QFile::Text);
    QByteArray file_content = file.readAll();

    /// animaition

    socket->write(file_content);
    socket->flush();
    file.close();
    currentPlayer.set_turn(false);

}
//**************************************************************************************************
void Server::on_Buttons13_clicked(){
    if(!currentPlayer.get_turn()){
        QMessageBox MQ;
        MQ.warning(0,"","it's not you'r turn...");
        return;
    }
    client_card = pushButtons[13];
    sendCard.push_back(pushButtons[13].thisCard);
    writeToFileCards("sendCard.bin",sendCard);
    QFile file("sendCard.bin");
    file.open(QFile::ReadOnly | QFile::Text);
    QByteArray file_content = file.readAll();
    /// animaition
    socket->write(file_content);
    socket->flush();
    file.close();
    currentPlayer.set_turn(false);

}
//**************************************************************************************************


