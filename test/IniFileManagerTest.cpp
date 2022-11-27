
#include "gtest/gtest.h"
#include "../IniFileManager.h"

TEST(IniFileManager,AddeSection){
    IniFileManager iniFile("testFile.ini");
    ASSERT_TRUE(iniFile.addSection("test2"));
}

TEST(IniFileManager,AddKeyValue){
    IniFileManager iniFile("testFile.ini");
    ASSERT_TRUE(iniFile.addKeyValue("Chiave","valore","Sezione"));
}

TEST(IniFileManager,AddComments){
    IniFileManager iniFile("testFile.ini");
    bool val1 = iniFile.addKeyValue("ServerPort", "8080", "Connection");
    bool val2 = iniFile.commentRecord(IniFileManager::enumCharComment::semicolon, "ServerPort", "Connection");
    ASSERT_EQ(val1,val2);
    ASSERT_EQ(iniFile.addSection("Owner"),
              iniFile.commentSection(IniFileManager::enumCharComment::semicolon, "Owner"));
    ASSERT_TRUE(iniFile.setSectionComments("#File di test creato il 18/11", "Owner"));
    ASSERT_TRUE(iniFile.setRecordComments("#versione deprecata","ServerPort", "Connection"));

}



