#include <future>
#include <thread>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <functional>
class ProcessMonitor
{
public:
  ProcessMonitor() ;
  ~ProcessMonitor();
	inline const std::future<void>& getProcess(const std::string& s) 
	{ 
		return _processMap[s];
	}
	bool removeProcess(const std::string& id);
	void startProcess(void(*func)());
	void startProcess(const std::string &s, const std::function<void(std::string)>& func);

  inline static const bool getRunning(){return _RUNNING;}
  static std::vector<std::string> readDataFile(const std::string &filename);
  static const void killProc(const std::string &proc);
private:
	std::unordered_map<std::string, std::future<void>> _processMap;
  inline static bool _RUNNING = true;
};
