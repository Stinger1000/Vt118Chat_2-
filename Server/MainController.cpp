#include "MainController.h">

MainController::MainController(QObject *parent) : QObject(parent), m_server(new TcpServer(this))
{
    QFile config("base_data.dat");
    QDataStream in(&config);
    char* data = new char[50] ;
    if(config.open(QIODevice::ReadOnly)){
        while(!in.status()){
            in.readRawData(data, 50);
            client_data_model_t client;
            client.login = data;

            in.readRawData(data, 50);
            client.password = data;
        }
    }

    //connects
    connect(m_server, &TcpServer::NewDataRecv, this, &MainController::DataRecv);
    connect(this, &MainController::DataSend, m_server, &TcpServer::NewDataSend);

    m_server->StartServer();
}

MainController::~MainController()
{
    QFile config("base_data.dat");
    QDataStream out(&config);
    if(config.open(QIODevice::WriteOnly)){
        for(auto i : m_clients){
            out.writeRawData(i.login.toStdString().c_str(), 50);
            out.writeRawData(i.password.toStdString().c_str(), 50);
        }
    }
}

bool MainController::ChechLoginDublicate(const QString login)
{
    for(auto i : m_clients){
        if(i.login == login)
            return true;
    }
    return false;
}

void MainController::DataRecv(const QByteArray &data, const quintptr socketDescriptor)
{
    if(data.size() < 10)
        return;
    switch (data.at(0)) {
        case Registration:
            //begin send data from encrypting mes(registration) ADD!!
            client_data_model_t client;
            int num_byte = 0;
            int size_field = data.at(1);
            for(num_byte = 0; num_byte < size_field; num_byte++){
                client.login.push_back(data.at(num_byte + 2));
            }
            size_field = data.at(num_byte + 3);
            for(num_byte = 0; num_byte < size_field; num_byte++){
                client.password.push_back(data.at(num_byte + 3));
            }
            if(ChechLoginDublicate(client.login))
            {
                QByteArray data;
                data.push_back(0x01);
                emit DataSend(data, socketDescriptor);
            }else{
                client.status = 1;
                client.discriptor = socketDescriptor;
                //generate key, send client, add in clien
                m_clients.push_back(client);
            }
        break;
    }
}
