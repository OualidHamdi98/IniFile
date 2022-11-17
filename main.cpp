#include <iostream>
#include "IniFileManager.h"

int main() {
    IniFileManager iniFile;
    iniFile.create("TestingFile.ini");
    //iniFile.printFile("TestingFile.ini");
    iniFile.addSection("Spesa","TestingFile.ini");
    iniFile.setValue("patate","1Kg","Spesa","TestingFile.ini");
    iniFile.addSection("Esami","TestingFile.ini");
    iniFile.addSection("Organi","TestingFile.ini");
    iniFile.setValue("Patate","3kg","Verdure","TestingFile.ini");
    iniFile.setValue("Analisi","18", "Esami", "TestingFile.ini");
    iniFile.setValue("Geometria","20","Esami","TestingFile.ini");
    iniFile.setValue("Carote","1kg","Spesa","TestingFile.ini");
    iniFile.printAllSection("TestingFile.ini");
    iniFile.commentRecord(IniFileManager::enumCharComment::semicolon, "Analisi", "Esami", "TestingFile.ini");
    iniFile.setValue("Busto","Cuore","Organi","TestingFile.ini");
    iniFile.commentSection(IniFileManager::enumCharComment::semicolon, "Organi", "TestingFile.ini");
  //  iniFile.commentSection(IniFileManager::enumCharComment::semicolon, "Esami", "TestingFile.ini");
    iniFile.setValue("Testa","Cervello","Organi","TestingFile.ini");

    return 0;
}
