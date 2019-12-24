#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
// --------------------K-Center Problem--------------------
// This is a Greedy Algorithm, what try to solve the K-Center
// NP-Hard Problem in Polinomal Time.
// !This is NOT the standard Greedy algo for this problem!
// I try to redraft the original Mathematic formula to a
// a real life problem for a better understand.
// City ~ Graph Vertex
// Cloud Servers = Marked Graph Vertex
// Problem  description:
// The problem is try to find the most optimal placement k points in n
// n = Graph = build from cities
// k = Cloud Servers
// --------------------K-Center Problem--------------------
// Class City
// c_name = name of the city
// x = coordinate x of city
// y = coordinate y of city
// cloud_server = true, if it is a marked point in graph
class City {
public:
        City(const string, const uint32_t, const uint32_t);
        ~City();
        const string& c_name() const;
        const int32_t& x() const;
        const int32_t& y() const;
        const bool& is_on() const;
        bool set_on();
        bool set_off();
        bool& is_CS();
        bool& set_CS(const bool);
        static unsigned int REMAINDER_;
private:
        const string city;
        const int32_t x_cor;
        const int32_t y_cor;
        bool checked;
        bool cloud_server;
protected:
};
unsigned int City::REMAINDER_(0);
City::City(const string city, const uint32_t x_cor, const uint32_t y_cor) :
        city(city),
        x_cor(x_cor),
        y_cor(y_cor),
        checked(true),
        cloud_server(false) {
        City::REMAINDER_++;
}
City::~City() = default;
const string& City::c_name() const {
      return this->city;
}
const int32_t& City::x() const {
      return this->x_cor;
}
const int32_t& City::y() const {
      return this->y_cor;
}
const bool& City::is_on() const {
      return const_cast<const bool&>(this->checked);
}
bool City::set_on() {
     City::REMAINDER_++;
     return this->checked = true;
}
bool City::set_off() {
     City::REMAINDER_++;
     return this->checked = false;
}
bool& City::is_CS() {
      return this->cloud_server;
}
bool& City::set_CS(const bool enable) {
      return this->cloud_server = enable;
}
// Predicate Minimum Distance
// The algorithm calulate the pivot of cities and servers
// Collect the cities in groups. The n closest city for each other.
// Example:4 city,2 server = 2 city / 1 server.
// Make the 2 cities group. 2-2 closest cities.
template<class Arg1, class Arg2, class Result>
class Pred_Min_Dte : public binary_function<Arg1, Arg2, Result> {
public:
    Pred_Min_Dte(first_argument_type pin) : binary_function(), pin(pin) {
    }
    ~Pred_Min_Dte() = default;
    inline result_type
    operator()(first_argument_type cls_c, second_argument_type &city) {
    uint32_t dte, min_dte;
    dte = pyth_thm(abs(pin->x() - city.x()), abs(pin->y() - city.y()));
    min_dte = pyth_thm(abs(pin->x() - cls_c->x()), abs(pin->y() - cls_c->y()));
    dte < min_dte ? cls_c._Ptr = &city : NULL;
    return cls_c;
}
private:
        first_argument_type pin;
        inline double pyth_thm(unsigned int a, unsigned int b) {
                return sqrt(a ^ 2 + b ^ 2);
        }
};
// Predicate Local Optimum
// This Predicate chooe the most optimal city in a group
// The Algorithm calculate the avarage distance for every city in a group.
// It will be the local optimum.
template<class Arg1, class Arg2, class Result>
class Pred_Local_Opt : public binary_function<Arg1, Arg2, Result> {
public:
        Pred_Local_Opt(vector<City*> &city_css) :
                binary_function(),
                city_ccs(city_css) {
                min_avg_dte = avg_dte(*city_css.begin());
        }
        ~Pred_Local_Opt() = default;
        inline result_type
        operator()(first_argument_type local_opt, second_argument_type &city) {
             avg_dte(city) < this->min_avg_dte ? local_opt._Ptr = &city : NULL;
             return local_opt;
        }
private:
        vector<City*>& city_ccs;
        uint64_t min_avg_dte;
        inline double pyth_thm(unsigned int a, unsigned int b) {
                return sqrt(a ^ 2 + b ^ 2);
        }
inline double avg_dte(second_argument_type city) {
    double avg_dte = 0;
    first_argument_type ir;
    for (ir = city_ccs.begin(); ir != this->city_ccs.end(); ++ir) {
 avg_dte += pyth_thm(abs(city->x() - (*ir)->x()), abs(city->y() - (*ir)->y()));
    }
    return avg_dte /= this->city_ccs.size();
   }
};
namespace typd {
        typedef vector<City>::iterator CI;
        typedef vector<City>::const_iterator CCI;
        typedef vector<City*>::iterator CPI;
        typedef vector<vector<City*>> CPV;
        typedef Pred_Local_Opt<CPI, City*, CPI> PLO;
        typedef Pred_Min_Dte<CI, City, CI> PMD;
}
// function k_center
vector<City>& k_center(vector<City>& cts, uint32_t Servers) {
  typd::CPV ccs;
  typd::CI c_itr;
  uint32_t ratio = floor(cts.size() / Servers);
  auto lmb_fo = [](const City &city) -> bool {return city.is_on();};
  while ((c_itr = find_if(cts.begin(), cts.end(), lmb_fo)) != cts.end()) {
          ccs.push_back(vector<City*>(1,c_itr._Ptr));
          if (City::REMAINDER_ / ratio > 1) {
                c_itr->set_off();
                typd::CI cls_c;
                for (uint32_t offset(0); offset < ratio - 1; ++offset) {
                   cls_c = find_if(cts.begin(), cts.end(), lmb_fo);
                   accumulate(cts.begin(), cts.end(), cls_c, typd::PMD(c_itr));
                   cls_c->set_off();
                   ccs.back().push_back(cls_c._Ptr);
                }
          }
          else {
           for(typd::CCI c_iter = cts.cbegin(); c_iter != cts.cend(); c_iter++)
               if(c_iter->is_on())
               ccs.back().push_back(c_iter._Ptr);
          break;
        }
   }
   for (typd::CPV::iterator i = ccs.begin(); i != ccs.end(); ++i)
   (*accumulate(i->begin(), i->end(), i->begin(),typd::PLO(*i)))->set_CS(true);
   return cts;
}
// k_center Greedy Algorithm try solve the best placement 2 servers
// between New York, Tokyio, Rio and Budapest.
// You have to locate a city in a coordinate system.(x,y)
#define SERVERS 2
int main(){
    vector<City> cities = {
    City("New York",40,74),
    City("Tokyio",35,139),
    City("Rio",22,43),
    City("Budapest",47,18)};
    k_center(cities,SERVERS);
    system("pause");
    return 0;
}
