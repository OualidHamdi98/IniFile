
#include "gtest/gtest.h"
#include "../IniFileManager.h"

TEST(IniFileManager,AddeSection){
    IniFileManager iniFile;
    ASSERT_TRUE(iniFile.create("testFile.ini"));
    ASSERT_TRUE(iniFile.addSection("test2","testFile.ini"));
}

TEST(IniFileManager,AddKeyValue){
    IniFileManager iniFile;
    ASSERT_TRUE(iniFile.create("testFile.ini"));
    ASSERT_TRUE(iniFile.addKeyValue("Chiave","valore","Sezione","testFile.ini"));
}

TEST(IniFileManager,AddComments){
    IniFileManager iniFile;
    ASSERT_TRUE(iniFile.create("TestingFile.ini"));
    bool val1 = iniFile.addKeyValue("ServerPort", "8080", "Connection", "TestingFile.ini");
    bool val2 = iniFile.commentRecord(IniFileManager::enumCharComment::semicolon, "ServerPort", "Connection", "TestingFile.ini");
    ASSERT_EQ(val1,val2);
    ASSERT_EQ(iniFile.addSection("Owner", "TestingFile.ini"),
              iniFile.commentSection(IniFileManager::enumCharComment::semicolon, "Owner", "TestingFile.ini"));
    ASSERT_TRUE(iniFile.setSectionComments("#File di test creato il 18/11", "Owner","TestingFile.ini"));
    ASSERT_TRUE(iniFile.setRecordComments("#versione deprecata","ServerPort", "Connection","TestingFile.ini"));

}



