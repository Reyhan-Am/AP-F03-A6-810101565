#include <string>
#include <sstream>
#include "handlers.hpp"
#include "response.hpp"
#include "request.hpp"
using namespace std;
std::string generateNewSessionId()
{
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_int_distribution<> dis(0, 15);

  std::ostringstream sessionId;
  for (int i = 0; i < 32; ++i)
  {
    sessionId << std::hex << dis(gen);
  }
  return sessionId.str();
}

Response *SignupH::callback(Request *req, string msg)
{
  string temp = "";
  std::string username = '"' + req->getBodyParam("username") + '"';
  std::string password = '"' + req->getBodyParam("password") + '"';
  Response *res = new Response;
  try
  {
    utaste->checkCommand({"POST", "signup", "?", "username", username, "password", password}, temp);
  }
  catch (Exception e)
  {
    if (e.getErrorMessage() != "OK")
    {
      Response *res = new Response;
      res->setHeader("Location", "/error_handling?errorMessage=" + e.getErrorMessage());
      res->setStatus(302);
      return res;
    }
  }
  res->setHeader("Location", "/myHome");
  string session_id = generateNewSessionId();
  res->setSessionId(session_id);
  sessionData[session_id] = "logged_in";
  res->setStatus(302);
  return res;
}

Response *ErrorHandler::callback(Request *req, string msg)
{
  string errorMessage = req->getQueryParam("errorMessage");
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  std::ostringstream pageContent;
  pageContent << "<!DOCTYPE html>" << std::endl
              << "<html>" << std::endl
              << "    <head><title>Error Message</title></head>" << std::endl
              << "    <body>" << std::endl
              << "        <h1>Error: " << errorMessage << "</h1>" << std::endl
              << "        <button onclick='window.history.back()'>Go Back</button>" << std::endl
              << "    </body>" << std::endl
              << "</html>" << std::endl;

  res->setBody(pageContent.str());
  return res;
}

Response *LoginH::callback(Request *req, string msg)
{
  string temp = "";
  std::string username = '"' + req->getBodyParam("username") + '"';
  std::string password = '"' + req->getBodyParam("password") + '"';
  Response *res = new Response;
  try
  {
    utaste->checkCommand({"POST", "login", "?", "username", username, "password", password}, temp);
  }
  catch (Exception e)
  {
    if (e.getErrorMessage() != "OK")
    {
      Response *res = new Response;
      res->setHeader("Location", "/error_handling?errorMessage=" + e.getErrorMessage());
      res->setStatus(302);
      return res;
    }
  }
  res->setHeader("Location", "/myHome");
  string session_id = generateNewSessionId();
  res->setSessionId(session_id);
  sessionData[session_id] = "logged_in";
  res->setStatus(302);
  return res;
}

Response *PostReserveH::callback(Request *req, string msg)
{
  string restaurant_name = '"' + req->getBodyParam("restaurant_name") + '"';
  string table_id = '"' + req->getBodyParam("table_id") + '"';
  string start_time = '"' + req->getBodyParam("start_time") + '"';
  string end_time = '"' + req->getBodyParam("end_time") + '"';
  string foods = '"' + req->getBodyParam("foods") + '"';
  string result = "";
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  try
  {
    utaste->checkCommand({"POST", "reserve", "?", "restaurant_name", restaurant_name, "table_id", table_id, "start_time", start_time, "end_time", end_time, "foods", foods}, result);
  }
  catch (Exception e)
  {
    if (e.getErrorMessage() != "OK")
    {
      Response *res = new Response;
      res->setHeader("Location", "/error_handling?errorMessage=" + e.getErrorMessage());
      res->setStatus(302);
      return res;
    }
  }
  size_t pos = 0;
  while ((pos = result.find("\n", pos)) != std::string::npos)
  {
    result.replace(pos, 1, "<br>");
    pos += 4;
  }
  ostringstream body;
  body
      << "<html>" << endl
      << "    <head><title>Restaurant Detail</title>" << endl
      << "        <p>" << result << "</p>" << endl
      << "<br><br>"
      << "        <a href='/myHome' "
      << "style='text-decoration: none; padding: 5px 10px; background-color: #007BFF; color: white; border-radius: 5px; font-size: 12px;'>Home</a>"
      << "    </div></body>" << endl
      << "</html>" << endl;
  res->setBody(body.str());
  return res;
}

Response *ExitH::callback(Request *req, string msg)
{
  string temp = "";
  string session_id = req->getSessionId();
  Response *res = new Response;
  try
  {
    utaste->checkCommand({"POST", "logout", "?"}, temp);
  }
  catch (Exception e)
  {
    if (e.getErrorMessage() != "OK")
    {
      res->setHeader("Location", "/error_handling?errorMessage=" + e.getErrorMessage());
      res->setStatus(302);
      return res;
    }
  }
  res->setSessionId(session_id);
  res->setHeader("Location", "/login");
  res->setStatus(302);
  return res;
}

Response *GetReservesH::callback(Request *req, string msg)
{
  string result = "";
  std::string reserve_id = req->getBodyParam("reserve_id");
  std::string restaurant_name = req->getBodyParam("restaurant_name");
  if (!reserve_id.empty())
  {
    reserve_id = '"' + reserve_id + '"';
  }
  if (!restaurant_name.empty())
  {
    restaurant_name = '"' + restaurant_name + '"';
  }
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  try
  {
    utaste->checkCommand({"GET", "reserves", "?", "restaurant_name", restaurant_name, "reserve_id", reserve_id}, result);
    size_t pos = 0;
    while ((pos = result.find("\n", pos)) != std::string::npos)
    {
      result.replace(pos, 1, "<br>");
      pos += 4;
    }
  }
  catch (Exception e)
  {
    if (e.getErrorMessage() != "OK")
    {
      cout << "error" << endl;
      Response *res = new Response;
      res->setHeader("Location", "/error_handling?errorMessage=" + e.getErrorMessage());
      res->setStatus(302);
      return res;
    }
  }
  ostringstream body;
  body
      << "<html>" << endl
      << "    <head><title>Restaurant Detail</title>" << endl
      << "        <p>" << result << "</p>" << endl
      << "<br><br>"
      << "        <a href='/myHome' "
      << "style='text-decoration: none; padding: 5px 10px; background-color: #007BFF; color: white; border-radius: 5px; font-size: 12px;'>Home</a>"
      << "    </div></body>" << endl
      << "</html>" << endl;
  res->setBody(body.str());
  return res;
}

Response *GetRestaurantH::callback(Request *req, string msg)
{
  string temp = "";
  std::string restaurant_name = '"' + req->getBodyParam("restaurant_name") + '"';
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string captured_output;
  std::stringstream ss;
  std::streambuf *coutbuf = std::cout.rdbuf();
  std::cout.rdbuf(ss.rdbuf());
  try
  {
    utaste->checkCommand({"GET", "restaurant_detail", "?", "restaurant_name", restaurant_name}, temp);
    std::cout.rdbuf(coutbuf);
    captured_output = ss.str();
    size_t pos = 0;
    while ((pos = captured_output.find("\n", pos)) != std::string::npos)
    {
      captured_output.replace(pos, 1, "<br>");
      pos += 4;
    }
  }
  catch (Exception e)
  {
    if (e.getErrorMessage() != "OK")
    {
      cout << "error" << endl;
      Response *res = new Response;
      res->setHeader("Location", "/error_handling?errorMessage=" + e.getErrorMessage());
      res->setStatus(302);
      return res;
    }
  }
  ostringstream body;
  body
      << "<html>" << endl
      << "    <head><title>Restaurant Detail</title>" << endl
      << "        <p>" << captured_output << "</p>" << endl
      << "<br><br>"
      << "        <a href='/myHome' "
      << "style='text-decoration: none; padding: 5px 10px; background-color: #007BFF; color: white; border-radius: 5px; font-size: 12px;'>Home</a>"
      << "    </div></body>" << endl
      << "</html>" << endl;
  res->setBody(body.str());
  return res;
}
