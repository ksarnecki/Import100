#include "DataUtil.h"

void DataUtil::printInfoCSV(Info& info) {
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

void DataUtil::printInfosCSV(Infos& infos) {
  for(int i=0;i<infos.Size();i++)
    printInfoCSV(infos[i]);
}