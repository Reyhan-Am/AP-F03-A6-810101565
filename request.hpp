#ifndef __REQUEST__
#define __REQUEST__
#include "include.hpp"
#include "utilities.hpp"
#include <string>
#include "head.hpp"
using namespace std;

class Request
{
public:
  Request(std::string method);
  std::string getPath();
  void setPath(std::string);
  Method getMethod();
  std::string getQueryParam(std::string key);
  void setQueryParam(std::string key, std::string value, bool encode = true);
  std::string getBodyParam(std::string key);
  void setBodyParam(std::string key, std::string value, bool encode = true);
  std::string getHeader(std::string key);
  void setHeader(std::string key, std::string value, bool encode = true);
  std::string getBody();
  std::string getSessionId();
  std::string getQueryString();
  map<string, string> getHeaders();
  void log();

private:
  std::string path;
  Method method;
  map<string, string> headers;
  map<string, string> query;
  map<string, string> body;
};
#endif
