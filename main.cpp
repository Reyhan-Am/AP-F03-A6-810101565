#include "head.hpp"
#include "Utaste.hpp"
#include "server.hpp"
#include "handlers.hpp"
#include "exception.hpp"

map<string, string> sessionData;

int main(int argc, char *argv[])
{
    UTaste utaste(argv[1], argv[2], argv[3]);
    Server server(5000);
    server.get("/myHome", new ShowPage("static/home.html"));
    server.get("/restaurant_detail", new ShowPage("static/restaurantDetail.html"));
    server.post("/restaurant_detail", new GetRestaurantH(&utaste));
    server.get("/exit", new ExitH(&utaste));
    server.get("/getReserves", new ShowPage("static/getReserves.html"));
    server.post("/getReserves", new GetReservesH(&utaste));
    server.get("/signup", new ShowPage("static/signup.html"));
    server.post("/signup", new SignupH(&utaste));
    server.get("/login", new ShowPage("static/login.html"));
    server.post("/login", new LoginH(&utaste));
    server.get("/reserve", new ShowPage("static/reserve.html"));
    server.post("/reserve", new PostReserveH(&utaste));
    server.get("/error_handling", new ErrorHandler(&utaste));
    server.run();

    return 0;
}