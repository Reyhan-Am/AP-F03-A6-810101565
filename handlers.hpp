#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "server.hpp"
#include "Utaste.hpp"
using namespace std;

class SignupH : public RequestHandler
{
public:
	SignupH(UTaste *utaste_ref) : utaste(utaste_ref) {}
	Response *callback(Request *req, string msg = "");

private:
	UTaste *utaste;
};

class ErrorHandler : public RequestHandler
{
public:
	ErrorHandler(UTaste *utaste_ref) : utaste(utaste_ref) {}
	Response *callback(Request *req, std::string msg = "");

private:
	UTaste *utaste;
};

class LoginH : public RequestHandler
{
public:
	LoginH(UTaste *utaste_ref) : utaste(utaste_ref) {}
	Response *callback(Request *req, string msg = "");

private:
	UTaste *utaste;
};

class ErrorH : public RequestHandler
{
public:
	ErrorH(UTaste *utaste_ref, string msg_) : utaste(utaste_ref), msg(msg_) {}
	Response *callback(Request *req, string msg_ = "");

private:
	UTaste *utaste;
	string msg;
};

class MainH : public RequestHandler
{
public:
	MainH(UTaste *utaste_ref) : utaste(utaste_ref) {}
	Response *callback(Request *req);

private:
	UTaste *utaste;
};

class GetRestaurantH : public RequestHandler
{
public:
	GetRestaurantH(UTaste *utaste_ref) : utaste(utaste_ref) {}
	Response *callback(Request *req, string msg = "");

private:
	UTaste *utaste;
};

class ShowRestaurantH : public RequestHandler
{
public:
	ShowRestaurantH(UTaste *utaste_ref) : utaste(utaste_ref) {}
	Response *callback(Request *req, string msg = "");

private:
	UTaste *utaste;
};

class ExitH : public RequestHandler
{
public:
	ExitH(UTaste *utaste_ref) : utaste(utaste_ref) {}
	Response *callback(Request *req, string msg = "");

private:
	UTaste *utaste;
};

class PostReserveH : public RequestHandler
{
public:
	PostReserveH(UTaste *utaste_ref) : utaste(utaste_ref) {}
	Response *callback(Request *req, string msg = "");
	string getString(string n, string t, string e, string s, string f);

private:
	UTaste *utaste;
};

class GetReservesH : public RequestHandler
{
public:
	GetReservesH(UTaste *utaste_ref) : utaste(utaste_ref) {}
	Response *callback(Request *req, string msg = "");

private:
	UTaste *utaste;
};

#endif
