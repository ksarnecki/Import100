#include <iostream>
#include <fstream>
#include <string>

#include "DynSet.h"
#include "AnsiString.h"

#include "Data.h"
#include "DataUtil.h"

DynSet<AnsiString> readData() {
  char buf[1024];
  DynSet<AnsiString> ret;
  while (std::cin.getline(buf, 1024))
    ret.Insert(AnsiString(buf).Trim());
  return ret;
}

Info empyInfo() {
  return Info("","","","","","","","","","","","","");
}

const AnsiString linePrefix = "<tr><td align=\"left\">&nbsp;</td><td align=\"left\">&nbsp;</td>";

DynSet<AnsiString> getPlainText(AnsiString line) {
  DynSet<AnsiString> ret;
  AnsiString act = "";
  int beg = 0;
  int lev = 0;
  for(int i=1;i<=line.Length();i++) {
    if(line[i]=='<') {
       if(lev==0 && i !=0) {
        ret.Insert(act);
        act = "";
      }
      lev++;
    } else if(line[i]=='>') {
      lev--;
    } else if(lev==0)
      act += line[i];
  }
  if(act != "")
    ret.Insert(act);
  return ret;
}

AnsiString extractName(AnsiString line) {
  line = line.Trim();
  int ix = line.Pos(" ");
  if(ix>0)
    return line.SubString(1, ix-1);
  return line;
}

AnsiString extractSurname(AnsiString line) {
  line = line.Trim();
  int ix = line.Pos(" ");
  if(ix>0)
    return line.SubString(ix+1, line.Length());
  return line;
}

const int phonePos = 15;
const int cityPos = 11;
const int namePos = 7;

void process(DynSet<Info>& infos, DynSet<AnsiString>& lines) {
  for(int i=0;i<lines.Size();i++) {
    if(lines[i].Pos(linePrefix)>0) {
     DynSet<AnsiString> words = getPlainText(lines[i]);
     if(words.Size()>=phonePos) {
       Info i = empyInfo();
       i.getPhone() = words[phonePos];
       i.getName() = extractSurname(words[namePos]);
       i.getSurname() = extractName(words[namePos]);
       i.getStreet() = words[cityPos];
       i.getSource()="stomatolog.com";
       infos.Insert(i);
     }
    }
  }
}

void printInfoCSV(Info& info) {
  std::cout<<info.getCrm_id().c_str()<<"#";
  std::cout<<info.getName().c_str()<<"#";
  std::cout<<info.getSurname().c_str()<<"#";
  std::cout<<info.getCompany().c_str()<<"#";
  std::cout<<info.getStreet().c_str()<<"#";
  std::cout<<info.getCity().c_str()<<"#";
  std::cout<<info.getZip().c_str()<<"#";
  std::cout<<info.getEmail().c_str()<<"#";
  std::cout<<info.getPhone().c_str()<<"#";
  std::cout<<info.getMobile().c_str()<<"#";
  std::cout<<info.getWww().c_str()<<"#";
  std::cout<<info.getSource().c_str()<<"#";
  std::cout<<info.getStatus().c_str()<<"#";
  std::cout<<std::endl;
}

void printCSV(DynSet<Info>& infos) {
  for(int i=0;i<infos.Size();i++)
    printInfoCSV(infos[i]);
}

static bool checkArg(int argc, char* argv[], const AnsiString& v) {
  for (int i=1;i<argc;i++)
    if (v==argv[i])
      return true;
  return false;
}

AnsiString readFile(AnsiString file) {
  AnsiString ret;
  try {
    std::ifstream myfile (file.c_str());
    std::string line;
    if (myfile.is_open()) 
     while (getline(myfile,line))
      ret += line + "\n";
    myfile.close();
  } catch(Exception e) {
    std::cout<<"[Error] Open "<<file.c_str()<<" fails"<< std::endl;
  }
  return ret;
}

DynSet<AnsiString> getInputFiles(int argc, const char* argv[]) {
  DynSet<AnsiString> ret;
  for (int i=1;i<argc;i++) {
    AnsiString file = argv[i];
    if(file.Pos(".json")<=0) {
      std::cout<<"[Warning] "<<file.c_str()<<" contains JSON?"<< std::endl;
    }
    ret.Insert(file);
  }
  return ret;
}

Infos mergeInfos(DynSet<AnsiString> files) {
  Infos ret;
  for(int i=0;i<files.Size();i++)
    try {
      Infos infs = Infos::fromJSON(readFile(files[i]));
      printf("[DEBUG] From %s get %d\n", files[i].c_str(), infs.Size());
      for(int j=0;j<infs.Size();j++)
        ret.Insert(infs[j]);
    } catch(Exception e) {
      std::cout<<"[Error] Parse "<<files[i].c_str()<<" fails"<< std::endl;
    }
  return ret;
}

void removePhoneDuplicates(Infos& infs) {
  
}

int main(int argc, const char* argv[]) {
  DynSet<AnsiString> files = getInputFiles(argc, argv);
  Infos s = mergeInfos(files);
  removePhoneDuplicates(s );
  DataUtil::printInfosCSV(s);
}
