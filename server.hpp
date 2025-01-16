#ifndef __SERVER__
#define __SERVER__
#include "include.hpp"
#include "request.hpp"
#include "response.hpp"
#include "route.hpp"
#include "head.hpp"
#include "Utaste.hpp"
#include <random>
using namespace std;


class RequestHandler
{
public:
  virtual ~RequestHandler();
  virtual Response *callback(Request *req, string msg = "") = 0;
};

class ShowFile : public RequestHandler
{
  std::string filePath;
  std::string fileType;

public:
  ShowFile(std::string filePath, std::string fileType);
  Response *callback(Request *req, string msg = "");
};

class ShowPage : public ShowFile
{

public:
  ShowPage(std::string _filePath);
};

class Server
{
public:
  Server(int port = 8080);
  ~Server();
  void run();
  void get(std::string path, RequestHandler *handler);
  void post(std::string path, RequestHandler *handler);

private:
  int sc;
  int port;
  std::vector<Route *> routes;
};

#endif
