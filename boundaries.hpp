/*
 * Super simple interval bounding class
 * @author Robert Cofield, 2015-07-23
 *
 */
#ifndef BOUNDARIES_HPP
#define BOUNDARIES_HPP

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <sstream>


// L: lower bound type
// U: upper bound type
template <typename L, typename U>
class Boundary 
{
  public:

    /*
     * constructors
     */

    Boundary()
      : lower(0), upper(1), rule("()") {}

    Boundary(const L lower_, const U upper_) 
      : lower(lower_), upper(upper_), rule("()") {}

    Boundary(const std::string rule_)
      : lower(0), upper(1), rule(rule_) {}

    Boundary(const L lower_, const U upper_, const std::string rule_) 
      : lower(lower_), upper(upper_), rule(rule_) {}

    ~Boundary(){};

    /*
     * Setters
     */

    inline void set(const L lower_, const U upper_) {
      lower = lower_;
      upper = upper_;
    }

    inline void set(const L lower_, const U upper_, const std::string rule_) {
      lower = lower_;
      upper = upper_;
      rule = rule_;
    }

    inline void setLower(const L lower_) {lower = lower_;}
    inline void setUpper(const U upper_) {upper = upper_;}
    inline void setRule(const std::string rule_) {rule = rule_;}

    /* Getters */

    inline L getLower() {L lower_ = lower; return lower_;}
    inline U getUpper() {L upper_ = upper; return upper_;}
    inline std::string getRule() {return std::string(rule);}
    
    inline std::string toString() {
      std::ostringstream o;
      if (!(o << rule[0] << lower << std::string(", ") << upper << rule[1]))
        return "ERROR OUTPUTTING TO STRING";
      return o.str();
    }

    /* what we're here for */

    template<typename V>
    inline bool check(const V value) {
      if      (rule.compare("()") == 0)
        return (lower <  value) && (value <  upper);
      else if (rule.compare("[]") == 0)
        return (lower <= value) && (value <= upper);
      else if (rule.compare("[)") == 0)
        return (lower <= value) && (value <  upper);
      else if (rule.compare("(]") == 0)
        return (lower <  value) && (value <= upper);
      std::cerr << "edge code must be length 2 whose values are one of: [, (, ], )" << std::endl;
      return false;
    }

  protected:

    L lower;
    U upper;
    std::string rule;

};


// stream inserter
template <typename L, typename U>
std::ostream & operator << (std::ostream & os, const Boundary<L,U> & bnd) {
  os << bnd.toString();
  return os;
}

#endif