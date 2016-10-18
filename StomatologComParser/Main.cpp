#include <iostream>

#include "DynSet.h"
#include "AnsiString.h"

#include "DataUtil.h"

#include "Data.h"

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

static bool checkArg(int argc, const char* argv[], const AnsiString& v) {
  for (int i=1;i<argc;i++)
    if (v==argv[i])
      return true;
  return false;
}

int main(int argc, const char* argv[]) {
  DynSet<AnsiString> lines = readData();
  Infos infos;
  process(infos, lines);
  AnsiString jsonArg = "-json";
  bool json = checkArg(argc, argv, jsonArg);
  if(!json)
    DataUtil::printInfosCSV(infos); 
  else
    std::cout<<(infos.toJSON()).c_str()<<std::endl;
}
