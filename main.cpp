#include <iostream>
#include "IniFileManager.h"

int main() {
    IniFileManager iniFile;
    //project workflows

    iniFile.create("TestingFile.ini");
    iniFile.printFile("TestingFile.ini");
    iniFile.addKeyValue("identifier", "Oualid Hamdi", "Owner", "TestingFile.ini");
    iniFile.addSection("Database","TestingFile.ini");
    iniFile.addKeyValue("SchemaDb", "test_db", "Database", "TestingFile.ini");
    iniFile.addKeyValue("SchemaDb", "prod_db", "Database", "TestingFile.ini");
    iniFile.addKeyValue("SchemaDb", "svil_db", "Database", "TestingFile.ini");
    iniFile.addSection("Connection","TestingFile.ini");
    iniFile.addKeyValue("ServerIp", "123.1.2.3", "Connection", "TestingFile.ini");
    iniFile.addKeyValue("ServerPort", "8080", "Connection", "TestingFile.ini");
    iniFile.printAllSection("TestingFile.ini");
    iniFile.renameSection("Database","DataBaseProperty", "TestingFile.ini");
    iniFile.addKeyValue("file1.lib", "libName", "Lib", "TestingFile.ini");
    iniFile.addKeyValue("file2.lib", "libName", "Lib", "TestingFile.ini");
    iniFile.commentRecord(IniFileManager::enumCharComment::semicolon, "ServerPort", "Connection", "TestingFile.ini"); //commenta il record della chiave indicata
    iniFile.commentSection(IniFileManager::enumCharComment::semicolon, "Owner", "TestingFile.ini");
    iniFile.setSectionComments("#File di test creato il 18/11", "Owner","TestingFile.ini");
    iniFile.setRecordComments("#versione deprecata","file2.lib", "Lib","TestingFile.ini");
    //iniFile.deleteRecord("ServerIp","Connection", "TestingFile.ini");
    //iniFile.deleteRecord("file2.lib","Lib", "TestingFile.ini");
    iniFile.printValue("ServerIp","Connection","TestingFile.ini");
    //iniFile.deleteSection("Connection", "TestingFile.ini");

    //  iniFile.commentSection(IniFileManager::enumCharComment::semicolon, "Esami", "TestingFile.ini");
    iniFile.printFile("TestingFile.ini");

    return 0;
}
