/*
 *
 */
#ifndef BOUNDARIES_HPP
#define BOUNDARIES_HPP

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>


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

    /* what we're here for */

    template<typename V>
    inline bool check(const V value) {
      return check(value, rule);
    }

    template<typename V>
    inline bool check(const V value, const std::string rule_) {
      if      (rule_.compare("()") == 0)
        return (lower <  value) && (value <  upper);
      else if (rule_.compare("[]") == 0)
        return (lower <= value) && (value <= upper);
      else if (rule_.compare("[)") == 0)
        return (lower <= value) && (value <  upper);
      else if (rule_.compare("(]") == 0)
        return (lower <  value) && (value <= upper);
      else
        std::cerr << "edge code must be length 2 whose values are one of: [, (, ], )" << std::endl;
    }

  protected:

    L lower;
    U upper;
    std::string rule;

};

#endif