#include <fstream>
#include <iostream>
#include <string.h>


#define FILE_NAME "fileExample-01.dat"
#define NUMBER 10

int main(int argc,char **argv)
{

  int i;
  double x;
  std::ifstream theFile(FILE_NAME,std::ios::in|std::ios::binary);

  struct output 
  {
    double x;
    int    i;
  };
  output basicInfo;
  char   buffer[1024];


    while(!theFile.eof())
    {
      theFile.read(buffer,sizeof(basicInfo));
      memcpy(&basicInfo,buffer,sizeof(basicInfo));
      std::cout << "Int: " << basicInfo.i << "/" << sizeof(i) 
                << " Double: " << basicInfo.x << "/" << sizeof(x) << std::endl;
    }
    std::cout << std::endl;


    /*
    for(i=0;i<NUMBER;++i)
      {
        theFile.read(buffer,sizeof(basicInfo));
        memcpy(&basicInfo,buffer,sizeof(basicInfo));
        std::cout << "Int: " << basicInfo.i << "/" << sizeof(i) 
                  << " Double: " << basicInfo.x << "/" << sizeof(x) << std::endl;
      }
    */

  theFile.close();
  return(0);
}
