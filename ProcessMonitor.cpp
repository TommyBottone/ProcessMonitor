#include "ProcessMonitor.h"
#include <fstream>
///////////////////////////////////////////////////////////////////////////////

  ProcessMonitor::ProcessMonitor() 
  { 
    ProcessMonitor::_RUNNING = true;  
  }
  ProcessMonitor::~ProcessMonitor()
  {
    ProcessMonitor::_RUNNING = false; 
    for(auto& [s, proc]: _processMap)
      {
        ProcessMonitor::killProc(s);
      }
  }
    
bool ProcessMonitor::removeProcess(const std::string& s)
{
    bool retVal = false;
    if (_processMap.find(s) != _processMap.end())
    {
        _processMap.erase(s);
        retVal = true;
    }

    return retVal;
}

void ProcessMonitor::startProcess(const std::string &s, const std::function<void(std::string)>& func)
{
    if (_processMap.find(s) == _processMap.end())
    {
        _processMap.insert({s, std::future<void>(std::async(std::launch::async, func, s))});
    }
}

std::vector<std::string> ProcessMonitor::readDataFile(const std::string &filename)
{
  std::vector<std::string> processes;

  std::string line;
  std::ifstream file(filename);
  if(file.good())
  {
    while (getline (file, line)) 
    {
      if(line.length() == 0)
      {
        continue;
      }
      if(line[0] == '#')
      {
        continue;
      }
      if(line.substr(0,2) != "./")
      {
        line = "./" + line;
      }
      processes.emplace_back(line);
    }
    
    file.close();
    }
  else 
  {
    std::cout << "File does not exist: " << filename <<std::endl;
  }
  return processes;
}

const void ProcessMonitor::killProc(const std::string &proc)
{
  //remove parameters
  std::string p = proc.substr(0, proc.find(" "));
  
  std::string kill = "pkill -f " + p;
  system(kill.c_str());
}