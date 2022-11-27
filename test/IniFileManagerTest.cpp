
#include "gtest/gtest.h"
#include "../IniFileManager.h"


//Verifico aggiungendo la stessa sezione il risultato
TEST(IniFileManager,AddeSection){
    IniFileManager iniFile("testFile1.ini");
    ASSERT_TRUE(iniFile.addSection("test1"));
    ASSERT_FALSE(iniFile.addSection("test1"));
}
//Verifico aggiungendo lo stesso valore il risultato
TEST(IniFileManager,AddKeyValue){
    IniFileManager iniFile("testFile2.ini");
    ASSERT_TRUE(iniFile.addKeyValue("Chiave","valore","Sezione"));
    ASSERT_FALSE(iniFile.addKeyValue("Chiave","valore","Sezione"));
}
//Verifico aggiungendo commento a sezione
//Aggingendo commento a sezione insesistente
//Cancello commento esistente e non da record
TEST(IniFileManager,Comments){
    IniFileManager iniFile("testFile3.ini");
    bool val1 = iniFile.addKeyValue("ServerPort", "8080", "Connection");
    bool val2 = iniFile.commentRecord(IniFileManager::enumCharComment::semicolon, "ServerPort", "Connection");
    ASSERT_EQ(val1,val2);
    ASSERT_FALSE(iniFile.setSectionComments("#File di test creato il 18/11", "Owner"));
    ASSERT_TRUE(iniFile.setRecordComments("#versione deprecata","ServerPort", "Connection"));
    ASSERT_TRUE(iniFile.deleteComment("ServerPort", "Connection"));
}


