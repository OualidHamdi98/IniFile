#include <iostream>
#include "IniFileManager.h"

int main() {
    //IniFileManager *iniFile = new IniFileManager("Testing.ini");
    IniFileManager iniFile("Testing.ini");

    iniFile.addSection("DataBase");
    iniFile.addKeyValue("identifier", "Oualid Hamdi", "Owner");
    iniFile.addKeyValue("SchemaDbTest", "test_db", "DataBase");
    iniFile.addKeyValue("SchemaDbPrd", "prod_db", "DataBase");
    iniFile.addKeyValue("SchemaDbSvil", "svil_db", "DataBase");
    iniFile.addSection("Connection");
    iniFile.addKeyValue("ServerIp", "123.1.2.3", "Connection");
    iniFile.addKeyValue("ServerPort", "8080", "Connection");
    iniFile.addKeyValue("file1.lib", "libName", "Lib");
    iniFile.addKeyValue("file2.lib", "libName", "Lib");
    iniFile.commentRecord(IniFileManager::enumCharComment::semicolon, "ServerPort", "Connection"); //commenta il record della chiave indicata
    iniFile.commentSection(IniFileManager::enumCharComment::semicolon, "Owner");
    iniFile.setSectionComments("#File di test creato il 18/11", "Owner");
    iniFile.setRecordComments("#versione deprecata","file2.lib", "Lib");
    iniFile.deleteRecord("ServerIp","Connection");
    iniFile.deleteRecord("file2.lib","Lib");
    iniFile.printValue("ServerIp","Connection");
    iniFile.deleteSection("Owner");
    iniFile.commentSection(IniFileManager::enumCharComment::semicolon, "Esami");

    //project workflows


    return 0;
}
