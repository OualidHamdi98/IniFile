//
// Created by Benefind on 06/11/2022.
//

#include "IniFileManager.h"

IniFileManager::IniFileManager(void){}

IniFileManager::~IniFileManager(void){}

// crea e salva un nuovo file vuoto
bool IniFileManager::create(string fileName)
{
    vector<IniStruct> fileContent;
    return save(fileName,fileContent);
}

bool IniFileManager::save(string fileName, vector<IniStruct>& fileContent)
{
    //creo un output str

    //if (!outFile.is_open()) return false;
    try{
        ofstream outFile (fileName.c_str());
        for (int i=0;i<(int)fileContent.size();i++)
        {
            outFile << fileContent[i].commentsStruct;
            if(fileContent[i].keyStruct == "")
                outFile << fileContent[i].charCommentStruct << "["
                        << fileContent[i].sectionStruct << "]" << endl;
            else
                outFile << fileContent[i].charCommentStruct << fileContent[i].keyStruct
                        << "=" << fileContent[i].valueStruct << endl;
        }
        outFile.close();
        return true;
    } catch (std::ofstream::failure &writeErr) {
        std::cerr << "Errore in fase di scrittura del file\n";
        return false;
    }
    catch (std::ifstream::failure &readErr) {
    std::cerr << "Errore in fase di lettura del file\n";
    return false;
    }
}

void trim(std::string& str)
{
    //regex che individua tutti gli spazi in una stringa
    std::regex r("\\s+");
    str=std::regex_replace(str,r,"");
}

bool IniFileManager::load(string fileName, vector<IniStruct>& content)
{
    string s;
    string CurrentSection;
    try{
        ifstream inFile (fileName.c_str());
        content.clear();
        string comments = "";
        //scorro fino alla fine del file;
        while(!std::getline(inFile, s).eof()){
            //pulisco la stringa dagli spazi vuoti;
            trim(s);
            if(!s.empty())
            {
                IniStruct r;
                //controllo se è una linea commentata;
                if((s[0]=='#')||(s[0]==';'))
                {
                    //non ci sono chiavi o valori
                    if ((s.find('[')==string::npos)&&
                        (s.find('=')==string::npos))
                    {
                        comments += s + '\n';
                        //vado a capo;
                    } else {
                        //salvo il caratterre e lo cancello per le iterazioni future;
                        r.charCommentStruct = s[0];
                        s.erase(s.begin());
                        trim(s);
                    }
                }
                //non ci sono linee commentate
                else r.charCommentStruct = ' ';
                //controllo se è una sezione
                if(s.find('[')!=string::npos)
                {
                    //cancello le quadre, e salvo la sezione;
                    s.erase(s.begin());
                    s.erase(s.find(']'));
                    r.commentsStruct = comments;
                    comments = "";
                    r.sectionStruct = s;
                    r.keyStruct = "";
                    r.valueStruct = "";
                    CurrentSection = s;
                }
                //controllo se ho chiave = valore
                if(s.find('=')!=string::npos)
                {
                    r.commentsStruct = comments;
                    comments = "";
                    r.sectionStruct = CurrentSection;
                    r.keyStruct = s.substr(0, s.find('='));
                    r.valueStruct = s.substr(s.find('=') + 1);
                }
                if(comments == "")
                    content.push_back(r);
            }
        }
        inFile.close();

    }catch(std::exception const& e){
        cout << "Errore di gestione del file: " << e.what() << endl;
        return false;
    }
    return true;
}

void IniFileManager::printFile(string fileName)
{
    string s="";
    vector<IniStruct> content;
    if (load(fileName, content))
    {
        for (int i=0;i<(int)content.size();i++)
        {
            if(content[i].commentsStruct != "") s += content[i].commentsStruct;
            if(content[i].charCommentStruct != ' ') s += content[i].charCommentStruct;
            if((content[i].keyStruct == "")) s += '[' + content[i].sectionStruct + ']';
            else s += content[i].keyStruct + '=' + content[i].valueStruct;
            //vai a capo
            if (i != content.size()) s += '\n';
        }
    }
    cout << s;
}

void IniFileManager::printAllSection(string fileName)
{
    vector<string> allSection;
    vector<IniStruct> content;

    if (load(fileName, content))
    {
        for (int i=0;i<(int)content.size();i++)
        {
            //se non esiste una chiave allora è una sezione;
            if(content[i].keyStruct == "")
                allSection.push_back(content[i].sectionStruct);
        }
    }
    //lambda function per stampare il vettore
    std::for_each(  allSection.begin(),
                    allSection.end(),
                    [](const auto & elem ) {
                        std::cout<<elem<<"\n";
                    });
}

bool IniFileManager::addSection(string sectionName, string fileName)
{
    vector<IniStruct> content;

    if (load(fileName, content) && !checkSection(sectionName,fileName))
    {
        //definisco una nuova iniStruct
        IniStruct s = {"",' ',sectionName,"",""};
        content.push_back(s);
        return save(fileName,content);
    }

    return false;
}

bool IniFileManager::commentSection(char commentChar, string section, string fileName)
{
    vector<IniStruct> content;

    if (load(fileName, content))
    {
        for(vector<IniStruct>::iterator iter = content.begin(); iter < content.end(); iter++)
        {

            if(iter->sectionStruct == section)
                //Cambia il commento e salva
                iter->charCommentStruct = commentChar;
        }
        return save(fileName,content);
    }
    return false;
}

bool IniFileManager::checkKeyValue(string section,string key, string fileName)
{
    vector<IniStruct> content;

    if (load(fileName, content))
    {
        vector<IniStruct>::iterator iter = content.begin();
        while(iter != content.end() ){
            if((iter->sectionStruct == section) && (iter->keyStruct == key)) return true;
            else iter++;
        }
    }
    return false;
}

bool IniFileManager::renameSection(string oldName, string newName, string fileName)
{
    vector<IniStruct> content;

    if (load(fileName, content))
    {
        for(vector<IniStruct>::iterator iter = content.begin();
            iter < content.end(); iter++)
        {
            if(iter->sectionStruct == oldName)
                iter->sectionStruct = newName;
        }
        return save(fileName,content);
    }
    return false;
}

bool IniFileManager::setSectionComments(string comments, string sectionName, string fileName)
{
    vector<IniStruct> content;

    if (load(fileName, content))
    {
        for(vector<IniStruct>::iterator iter = content.begin(); iter < content.end(); iter++)
        {
            // cerco la sezione corretta con record vuoto;
            if((iter->sectionStruct == sectionName) && (iter->keyStruct == ""))
            {
                // aggiungo a capo se non presente
                if (comments.size() >= 2 && comments.substr(comments.size()-2) != "\n")
                    comments += "\n";
                //salvo il commento
                iter->commentsStruct = comments;


            }
        }
    }
    return save(fileName,content);
}

bool IniFileManager::deleteSection(string section, string fileName)
{
    vector<IniStruct> content;
    if (load(fileName, content))
    {
        for(int i=(int)content.size()-1;i>=0;i--)
        {
            if(content[i].sectionStruct == section)
                content.erase (content.begin()+i);
        }
        return save(fileName,content);
    }
    return false;
}

bool IniFileManager::setValue(string key, string value, string section, string fileName)
{
    vector<IniStruct> content;

    if (load(fileName, content) )
    {
        if(!checkSection(section,fileName))
        {
            IniStruct s = {"",' ',section,"",""};
            IniStruct r = {"",' ',section,key,value};
            content.push_back(s);
            content.push_back(r);
            return save(fileName,content);
        }
        if(!checkKeyValue(section,key,fileName))
        {
            vector<IniStruct>::iterator iter = content.begin();
            //non faccio altri controlli tanto so che esiste una sezione = section;
            while(iter->sectionStruct != section)
                iter++;
            IniStruct r = {"",' ',section,key,value};
            content.insert(iter+1,r);
            //iter.push_back(r);
            //content.insert(iter,r);
            return save(fileName,content);
        }
    }
    return false;
}

bool IniFileManager::commentRecord(enumCharComment cc, string key, string section, string fileName)
{
    vector<IniStruct> content;

    if (load(fileName, content))
    {
        vector<IniStruct>::iterator iter = content.begin();
        while((iter != content.end()) && (iter->sectionStruct != section))
               iter++;
        if (iter == content.end()) return false;
        iter->charCommentStruct = cc;
        return save(fileName,content);
    }
    return false;
}

bool IniFileManager::checkSection(string sectionName, string FileName)
{
    vector<IniStruct> content;
    if (load(FileName, content))
    {
        vector<IniStruct>::iterator iter = content.begin();
        while(iter != content.end() ){
            if(iter->sectionStruct == sectionName) return true;
            else iter++;
        }
    }
    return false;
}

void IniFileManager::printValue(string key, string section, string fileName)
{
    IniStruct data;
    vector<IniStruct> content;

    if (load(fileName, content))
    {
        vector<IniStruct>::iterator iter = content.begin();
        while(iter !=  content.end() || (iter->sectionStruct != section && iter->keyStruct != key))
            iter++;
        if (iter != content.end())
            cout <<"\n value of key : "<<key <<" in section : "<<section<< " is : " << iter->keyStruct ;
        else cout << "\n there is no value for for this section or this key in this file; " ;
    }
}

bool IniFileManager::deleteRecord(string key, string section, string fileName)
{
    vector<IniStruct> content;

    if (load(fileName, content))
    {
        vector<IniStruct>::iterator iter = content.begin();
        while(iter !=  content.end() || (iter->sectionStruct != section && iter->keyStruct != key))
            iter++;
        if (iter == content.end()) return false;
        content.erase(iter);
        return save(fileName,content);
    }
    return false;
}

bool IniFileManager::setRecordComments(string comments, string key, string section, string fileName)
{
    vector<IniStruct> content;

    if (load(fileName, content))
    {
        vector<IniStruct>::iterator iter = content.begin();
        while(iter !=  content.end() || (iter->sectionStruct != section && iter->keyStruct != key))
            iter++;

        if (iter == content.end()) return false;
        if (comments.size() >= 2)
        {
            //se il precedente commento non finisce con newLine vado a capo
            if (comments.substr(comments.size()-2) != "\n")
                comments += "\n";
        }
        iter->commentsStruct = comments;
        return save(fileName,content);
    }
    return false;
}








