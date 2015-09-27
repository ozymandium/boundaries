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
#include <iomanip>      // std::setprecision


template<typename T>
inline std::string boundToString(const T* bnd, std::string rule) {
  std::ostringstream o;
  if (!(o << rule[0] << bnd[0] << ", " << bnd[1] << rule[1]))
    return "ERROR OUTPUTTING TO STRING";
  return o.str();
}


template<typename V, typename T>
inline int8_t
within(
  const V value,
  const std::string rule,
  const T* bnd
) {
  bool satisfied = false;
  // check lower
  if      (std::string(rule, 0, 1) == std::string("(")) satisfied = bnd[0] <  value;
  else if (std::string(rule, 0, 1) == std::string("[")) satisfied = bnd[0] <= value;
  else
    std::cerr << "Lower edge code (rule[0]) must be one of (, [" << std::endl;
  if (!satisfied) return -1;
  // check upper
  if      (std::string(rule, 1, 1) == std::string(")")) satisfied = value <  bnd[1];
  else if (std::string(rule, 1, 1) == std::string("]")) satisfied = value <= bnd[1];
  else
    std::cerr << "Upper edge code (rule[1]) must be one of ), ]" << std::endl;
  return satisfied ? 0 : -1;
}


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

    /*
     * Getters
     */

    inline L getLower() const {return lower;}
    inline U getUpper() const {return upper;}
    inline std::string getRule() const {return rule;}

    /* Generate string representation*/
    inline std::string toString() const {
      std::ostringstream o;
      if (!(o << rule[0] << lower << ", " << upper << rule[1]))
        return "ERROR OUTPUTTING TO STRING";
      return o.str();
    }

    /* check the value with int codes for violations: -1 for lower, 1 for upper.
     * 0 indicates no violation
     */
    template<typename V>
    int check(const V value) {
      if (!checkLower<V>(value)) return -1;
      if (!checkUpper<V>(value)) return 1;
      return 0;
    }

  protected:

    template<typename V>
    inline bool checkLower(const V value) {
      if      (std::string(rule, 0, 1) == std::string("(")) return lower <  value;
      else if (std::string(rule, 0, 1) == std::string("[")) return lower <= value;
      else
        std::cerr << "Lower edge code (rule[0]) must be one of (, [" << std::endl;
    }

    template<typename V>
    inline bool checkUpper(const V value) {
      if      (std::string(rule, 1, 1) == std::string(")")) return value <  upper;
      else if (std::string(rule, 1, 1) == std::string("]")) return value <= upper;
      else
        std::cerr << "Upper edge code (rule[1]) must be one of ), ]" << std::endl;
    }

    L lower;
    U upper;
    std::string rule;

};


/* print to std out */
template<typename L, typename U>
std::ostream & operator<< (std::ostream & out, const Boundary<L,U> & b) {
  out << b.toString();
  return out;
}


#endif