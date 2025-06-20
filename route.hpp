#ifndef __ROUTE__
#define __ROUTE__
#include "include.hpp"
#include "request.hpp"
#include "response.hpp"
#include <string>
using namespace std;

class RequestHandler;

class Route
{
private:
  Method method;
  std::string path;
  RequestHandler *handler;

public:
  Route(Method _method, std::string _path);
  ~Route();
  bool isMatch(Method, std::string url);
  Response *handle(Request *req);
  void setHandler(RequestHandler *_handler);
};
#endif
