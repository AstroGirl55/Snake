//HTTP credits: http://lcs.ios.ac.cn/~maxt/SPelton/reports/report-9aa0d3.html
//JSON credits: https://github.com/nlohmann/json
#include <iostream>
#include <vector>
#include "./json.hpp"
#include "./http_stuff.h"
using namespace std;
using namespace nlohmann;
int main(void) {
  httplib::Server svr;
  svr.Get("/", [](const auto &, auto &res) {
    string head = "shades"; //TODO: Change head
    string tail = "freckled"; //TODO: Change tail
    string author = ""; //TODO: Change your battlesnake username
    string color = "#ffaa00";  //TODO: Change a hex color
    res.set_content("{\"apiversion\":\"1\", \"head\":\"" + head + "\", \"tail\":\"" + tail + "\", \"color\":\"" + color + "\", " + "\"author\":\"" + author + "\"}", "text/json");
  });
  svr.Post("/end", [](const auto &, auto &res){
    res.set_content("ok", "text/plain");
  });
  svr.Post("/start", [](const auto &, auto &res){
    res.set_content("ok", "text/plain");
  });
  svr.Post("/move", [](auto &req, auto &res){
    const json data = json::parse(req.body);
    cout << data;
    cout << "\n\n";
    //You can get the "you" property like this:
    //data["you"];
    //Almost alike python dictionary parsing, but with a semicolon at the end of each line.
    //You might need to make some structs to store some data in a variable
    //Example:
    //you_struct you = data["you"];

    vector <string> movevec;
    string moves[4] = {"up", "down", "left", "right"};
    int index = rand() % 4;
    const json you = data["you"];
    int headx = you["head"]["x"];
    int heady = you["head"]["y"];
    int width = data["board"]["width"];
    int height = data["board"]["height"];

    string move = "";
    if (headx != 0){
      movevec.push_back( "left");
    }
    if (heady != 0){
      movevec.push_back("down");
    }
    if (headx < width - 1){
      movevec.push_back("right");
    }
    if (heady < height - 1){
      movevec.push_back("up");
    }
    if (movevec.size() > 0){
      move = movevec[rand() % movevec.size()];
    }else{
      move = moves[rand() % 4];
    }

    res.set_content("{\"move\": \"" + move + "\"}", "text/plain");
  });
  svr.listen("0.0.0.0", 8080);
  cout << "Server started";
}
