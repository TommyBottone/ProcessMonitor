#include <iostream>
#include <algorithm>
#include "ProcessMonitor.h"

int main(int argc, char** argv)
{  
  std::vector<std::string> processes;
  if(argc == 2)
  {
    processes = ProcessMonitor::readDataFile(argv[argc-1]);
  }
  else
  {
    std::cout <<"Add parameter of data file with scripts\n";
    return 0;
  }

  std::cout << "Type exit to end program\n";
  ProcessMonitor* proc = new ProcessMonitor();

  for(std::string p : processes)
  {
    auto lambda = [=](std::string p)
    {
      std::cout << p << std::endl;
      system(p.c_str());
    };
    proc->startProcess(p, lambda);
  }
  std::string input;
  do
  {
    std::cin>>input;
    std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c){return std::tolower(c);});
    std::cout <<input<<std::endl;
  }while(input != "exit");
  delete proc;
}