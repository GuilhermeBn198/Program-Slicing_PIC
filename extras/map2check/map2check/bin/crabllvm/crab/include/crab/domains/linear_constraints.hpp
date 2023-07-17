/*******************************************************************************
 *
 * Data structures for the symbolic manipulation of linear constraints.
 *
 * Author: Arnaud J. Venet (arnaud.j.venet@nasa.gov)
 *
 * Notices:
 *
 * Copyright (c) 2011 United States Government as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All Rights Reserved.
 *
 * Disclaimers:
 *
 * No Warranty: THE SUBJECT SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY OF
 * ANY KIND, EITHER EXPRESSED, IMPLIED, OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, ANY WARRANTY THAT THE SUBJECT SOFTWARE WILL CONFORM TO SPECIFICATIONS,
 * ANY IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
 * OR FREEDOM FROM INFRINGEMENT, ANY WARRANTY THAT THE SUBJECT SOFTWARE WILL BE
 * ERROR FREE, OR ANY WARRANTY THAT DOCUMENTATION, IF PROVIDED, WILL CONFORM TO
 * THE SUBJECT SOFTWARE. THIS AGREEMENT DOES NOT, IN ANY MANNER, CONSTITUTE AN
 * ENDORSEMENT BY GOVERNMENT AGENCY OR ANY PRIOR RECIPIENT OF ANY RESULTS,
 * RESULTING DESIGNS, HARDWARE, SOFTWARE PRODUCTS OR ANY OTHER APPLICATIONS
 * RESULTING FROM USE OF THE SUBJECT SOFTWARE.  FURTHER, GOVERNMENT AGENCY
 * DISCLAIMS ALL WARRANTIES AND LIABILITIES REGARDING THIRD-PARTY SOFTWARE,
 * IF PRESENT IN THE ORIGINAL SOFTWARE, AND DISTRIBUTES IT "AS IS."
 *
 * Waiver and Indemnity:  RECIPIENT AGREES TO WAIVE ANY AND ALL CLAIMS AGAINST
 * THE UNITED STATES GOVERNMENT, ITS CONTRACTORS AND SUBCONTRACTORS, AS WELL
 * AS ANY PRIOR RECIPIENT.  IF RECIPIENT'S USE OF THE SUBJECT SOFTWARE RESULTS
 * IN ANY LIABILITIES, DEMANDS, DAMAGES, EXPENSES OR LOSSES ARISING FROM SUCH
 * USE, INCLUDING ANY DAMAGES FROM PRODUCTS BASED ON, OR RESULTING FROM,
 * RECIPIENT'S USE OF THE SUBJECT SOFTWARE, RECIPIENT SHALL INDEMNIFY AND HOLD
 * HARMLESS THE UNITED STATES GOVERNMENT, ITS CONTRACTORS AND SUBCONTRACTORS,
 * AS WELL AS ANY PRIOR RECIPIENT, TO THE EXTENT PERMITTED BY LAW.
 * RECIPIENT'S SOLE REMEDY FOR ANY SUCH MATTER SHALL BE THE IMMEDIATE,
 * UNILATERAL TERMINATION OF THIS AGREEMENT.
 *
 ******************************************************************************/

#pragma once

#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/container/flat_map.hpp>
#include <boost/container/slist.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/functional/hash.hpp>
#include <crab/common/types.hpp>
#include <crab/domains/patricia_trees.hpp>

namespace ikos {
  
  template< typename Number, typename VariableName >
  class linear_expression: public writeable {
    
  public:
    typedef Number number_t;
    typedef VariableName varname_t;
    typedef variable< Number, VariableName > variable_t;
    typedef linear_expression< Number, VariableName > linear_expression_t;
    typedef std::pair< Number, variable_t > component_t;
    typedef patricia_tree_set< variable_t > variable_set_t;
    
  private:
    typedef boost::container::flat_map< variable_t, Number > map_t;
    typedef boost::shared_ptr< map_t > map_ptr;
    typedef typename map_t::value_type pair_t;
    
  private:
    map_ptr _map;
    Number _cst;
    
  private:
    linear_expression(map_ptr map, Number cst): 
        _map(map), _cst(cst) { }
    
    linear_expression(const map_t& map, Number cst): 
        _map(map_ptr(new map_t)), _cst(cst) {
      *this->_map = map;
    }
    
    void add(variable_t x, Number n) {
      typename map_t::iterator it = this->_map->find(x);
      if (it != this->_map->end()) {
        Number r = it->second + n;
        if (r == 0) {
          this->_map->erase(it);
        } else {
          it->second = r;
        }
      } else {
        if (n != 0) {
          this->_map->insert(pair_t(x, n));
        }
      }
    }
    
   public:
    class iterator: public boost::iterator_facade< iterator,
                                                   component_t,
                                                   boost::forward_traversal_tag,
                                                   component_t> {
      
      friend class boost::iterator_core_access;
      
     private:
      typename map_t::const_iterator _it;
      map_ptr _m;
      
     public:
      iterator(map_ptr m, bool b): _it(b ? m->begin() : m->end()), _m(m) { }
      
     private:
      void increment() { 
        ++this->_it;
      }
      
      bool equal(const iterator& other) const {
        return (this->_m == other._m && this->_it == other._it);
      }
      
      component_t dereference() const {
        if (this->_it != this->_m->end()) {
          return component_t(this->_it->second, this->_it->first);
        } else {
          CRAB_ERROR("Linear expression: trying to dereference an empty iterator");
        }
      }
      
    }; // class iterator
    
  public:
    linear_expression(): 
        _map(map_ptr(new map_t)), _cst(0) { }
    
    linear_expression(Number n): 
        _map(map_ptr(new map_t)), _cst(n) { }
    
    linear_expression(signed long long int n): 
        _map(map_ptr(new map_t)), _cst(Number(n)) { }
    
    linear_expression(variable_t x): 
        _map(map_ptr(new map_t)), _cst(0) {
      this->_map->insert(pair_t(x, Number(1)));
    }
    
    linear_expression(Number n, variable_t x): 
        _map(map_ptr(new map_t)), _cst(0) {
      this->_map->insert(pair_t(x, n));
    }

    linear_expression_t& operator=(const linear_expression_t &e) {
      if (this != &e) {
        this->_map = e._map;
        this->_cst = e._cst;
      }
      return *this;
    }
    
    iterator begin() const {
      return iterator(this->_map, true);
    }

    iterator end() const {
      return iterator(this->_map, false);
    }

    size_t hash () const {
      size_t res = 0;
      for (iterator it=begin(), et=end (); it!=et; ++it) {
        boost::hash_combine (res, std::make_pair((*it).second, (*it).first));
      }
      boost::hash_combine (res, _cst);
      return res;
    }

    // syntactic equality
    bool equal(const linear_expression_t& o) const {
      if (is_constant()) {
	if (!o.is_constant()) {
	  return false;
	} else {
	  return (constant() == o.constant());
	}
      } else {
	if (constant() != o.constant()) {
	  return false;
	}
	
	if (size() != o.size()) {
	  return false;
	} else {
	  for (iterator it=begin(), jt=o.begin(), et=end (); it!=et; ++it,++jt) {
	    if (((*it).first != (*jt).first) || ((*it).second != (*jt).second)) {
	      return false;
	    }
	  }
	  return true;
	}
      }
    }
    
    bool is_constant() const {
      return (this->_map->size() == 0);
    }

    Number constant() const {
      return this->_cst;
    }
    
    std::size_t size() const {
      return this->_map->size();
    }

    Number operator[](variable_t x) const {
      typename map_t::const_iterator it = this->_map->find(x);
      if (it != this->_map->end()) {
	return it->second;
      } else {
	return 0;
      }
    }

    template<typename VarMap>
    boost::optional<linear_expression_t> rename (const VarMap& map) const {
      Number cst(this->_cst);
      linear_expression_t ren_exp(cst);
      for(auto v : this->variables()) {
        auto const it = map.find(v);
        if (it != map.end()) {
          variable_t v_out ((*it).second);
          ren_exp = ren_exp + this->operator[](v) * v_out;
        }
        else
          return boost::optional<linear_expression_t>();
      }
      return ren_exp;
    }

    linear_expression_t operator+(Number n) const {
      linear_expression_t r(this->_map, this->_cst + n);
      return r;
    }

    linear_expression_t operator+(int n) const {
      return this->operator+(Number(n));
    }
    
    linear_expression_t operator+(variable_t x) const {
      linear_expression_t r(*this->_map, this->_cst);
      r.add(x, Number(1));
      return r;
    }
    
    linear_expression_t operator+(const linear_expression_t &e) const {
      linear_expression_t r(*this->_map, this->_cst + e._cst);
      for (typename map_t::const_iterator it = e._map->begin(); 
           it != e._map->end(); ++it) {
        r.add(it->first, it->second);
      }
      return r;
    }

    linear_expression_t operator-(Number n) const {
      return this->operator+(-n);
    }

    linear_expression_t operator-(int n) const {
      return this->operator+(-Number(n));
    }

    linear_expression_t operator-(variable_t x) const {
      linear_expression_t r(*this->_map, this->_cst);
      r.add(x, Number(-1));
      return r;      
    }

    linear_expression_t operator-() const {
      return this->operator*(Number(-1));
    }

    linear_expression_t operator-(const linear_expression_t &e) const {
      linear_expression_t r(*this->_map, this->_cst - e._cst);
      for (typename map_t::const_iterator it = e._map->begin(); 
           it != e._map->end(); ++it) {
        r.add(it->first, -it->second);
      }
      return r;      
    }
    
    linear_expression_t operator*(Number n) const {
      if (n == 0) {
        return linear_expression_t();
      } else {
        map_ptr map = map_ptr(new map_t);
        for (typename map_t::const_iterator it = this->_map->begin(); 
             it != this->_map->end(); ++it) {
          Number c = n * it->second;
          if (c != 0) {
            map->insert(pair_t(it->first, c));
          }
        }
        return linear_expression_t(map, n * this->_cst);
      }
    }
    
    linear_expression_t operator*(int n) const {
      return operator*(Number(n));
    }
    
    variable_set_t variables() const {
      variable_set_t variables;
      for (iterator it = this->begin(); it != this->end(); ++it) {
	variables += it->second;
      }
      return variables;
    }

    boost::optional<variable_t> get_variable() const {
      if (this->is_constant())
        return boost::optional<variable_t>();
      else{
        if ((this->constant() == 0) && (this->size() == 1)){
          typename linear_expression_t::iterator it = this->begin();
          Number coeff = it->first;
          if (coeff == 1)
            return boost::optional<variable_t>(it->second);
        }
        return boost::optional<variable_t>();
      }
    }
    
    void write(crab::crab_os& o) {
      for (typename map_t::iterator it = this->_map->begin(); 
           it != this->_map->end(); ++it) {
        Number n = it->second;
        variable_t v = it->first;
        if (n > 0 && it != this->_map->begin()) {
          o << "+";
        }
        if (n == -1) {
          o << "-";
        } else if (n != 1) {
          o << n << "*";
        }
        o << v;
      }
      if (this->_cst > 0 && this->_map->size() > 0) {
        o << "+";
      }
      if (this->_cst != 0 || this->_map->size() == 0) {
        o << this->_cst;
      }
    }

    // for dgb
    void dump() {
      write(crab::outs());
    }
    
  }; // class linear_expression

  template<typename Number, typename VariableName>
  inline std::size_t hash_value(const linear_expression<Number,VariableName>& e) {
    return e.hash ();
  }

  template< typename Number, typename VariableName >
  inline linear_expression< Number, VariableName > 
  operator*(Number n, variable< Number, VariableName > x) {
    return linear_expression< Number, VariableName >(n, x);
  }
  
  template< typename Number, typename VariableName >
  inline linear_expression< Number, VariableName > 
  operator*(int n, variable< Number, VariableName > x) {
    return linear_expression< Number, VariableName >(Number(n), x);
  }

  template< typename Number, typename VariableName >
  inline linear_expression< Number, VariableName > 
  operator*(variable< Number, VariableName > x, Number n) {
    return linear_expression< Number, VariableName >(n, x);
  }
  
  template< typename Number, typename VariableName >
  inline linear_expression< Number, VariableName > 
  operator*(variable< Number, VariableName > x, int n) {
    return linear_expression< Number, VariableName >(Number(n), x);
  }

  template< typename Number, typename VariableName >
  inline linear_expression< Number, VariableName > 
  operator*(Number n, const linear_expression< Number, VariableName > &e) {
    return e.operator*(n);
  }
  
  template< typename Number, typename VariableName >
  inline linear_expression< Number, VariableName > 
  operator*(int n, const linear_expression< Number, VariableName > &e) {
    return e.operator*(n);
  }

  template< typename Number, typename VariableName >
  inline linear_expression< Number, VariableName > 
  operator+(variable< Number, VariableName > x, Number n) {
    return linear_expression< Number, VariableName >(x).operator+(n);
  }

  template< typename Number, typename VariableName >
  inline linear_expression< Number, VariableName > 
  operator+(variable< Number, VariableName > x, int n) {
    return linear_expression< Number, VariableName >(x).operator+(n);
  }

  template< typename Number, typename VariableName >
  inline linear_expression< Number, VariableName > 
  operator+(Number n, variable< Number, VariableName > x) {
    return linear_expression< Number, VariableName >(x).operator+(n);
  }

  template< typename Number, typename VariableName >
  inline linear_expression< Number, VariableName > 
  operator+(int n, variable< Number, VariableName > x) {
    return linear_expression< Number, VariableName >(x).operator+(n);
  }

  template< typename Number, typename VariableName >
  inline linear_expression< Number, VariableName > 
  operator+(variable< Number, VariableName > x, 
            variable< Number, VariableName > y) {
    return linear_expression< Number, VariableName >(x).operator+(y);
  }

  template< typename Number, typename VariableName >
  inline linear_expression< Number, VariableName > 
  operator+(Number n, const linear_expression< Number, VariableName > &e) {
    return e.operator+(n);
  }
  
  template< typename Number, typename VariableName >
  inline linear_expression< Number, VariableName > 
  operator+(int n, const linear_expression< Number, VariableName > &e) {
    return e.operator+(n);
  }

  template< typename Number, typename VariableName >
  inline linear_expression< Number, VariableName > 
  operator+(variable< Number, VariableName > x, 
            const linear_expression< Number, VariableName > &e) {
    return e.operator+(x);
  }

  template< typename Number, typename VariableName >
  inline linear_expression< Number, VariableName > 
  operator-(variable< Number, VariableName > x, Number n) {
    return linear_expression< Number, VariableName >(x).operator-(n);
  }

  template< typename Number, typename VariableName >
  inline linear_expression< Number, VariableName > 
  operator-(variable< Number, VariableName > x, int n) {
    return linear_expression< Number, VariableName >(x).operator-(n);
  }

  template< typename Number, typename VariableName >
  inline linear_expression< Number, VariableName > 
  operator-(Number n, variable< Number, VariableName > x) {
    return linear_expression< Number, VariableName >(Number(-1), x).operator+(n);
  }

  template< typename Number, typename VariableName >
  inline linear_expression< Number, VariableName > 
  operator-(int n, variable< Number, VariableName > x) {
    return linear_expression< Number, VariableName >(Number(-1), x).operator+(n);
  }

  template< typename Number, typename VariableName >
  inline linear_expression< Number, VariableName > 
  operator-(variable< Number, VariableName > x, 
            variable< Number, VariableName > y) {
    return linear_expression< Number, VariableName >(x).operator-(y);
  }

  template< typename Number, typename VariableName >
  inline linear_expression< Number, VariableName > 
  operator-(Number n, const linear_expression< Number, VariableName > &e) {
    return linear_expression< Number, VariableName >(n).operator-(e);
  }
  
  template< typename Number, typename VariableName >
  inline linear_expression< Number, VariableName > 
  operator-(int n, const linear_expression< Number, VariableName > &e) {
    return linear_expression< Number, VariableName >(Number(n)).operator-(e);
  }

  template< typename Number, typename VariableName >
  inline linear_expression< Number, VariableName > 
  operator-(variable< Number, VariableName > x, 
            const linear_expression< Number, VariableName > &e) {
    return linear_expression< Number, VariableName >(Number(1), x).operator-(e);
  }
  
  template< typename Number, typename VariableName >
  class linear_constraint: public writeable {
    
  public:
    typedef Number number_t;
    typedef VariableName varname_t;
    typedef linear_constraint< Number, VariableName > linear_constraint_t;
    typedef variable< Number, VariableName > variable_t;
    typedef linear_expression< Number, VariableName > linear_expression_t;
    typedef patricia_tree_set< variable_t > variable_set_t;
    typedef enum {
      EQUALITY,
      DISEQUATION,
      INEQUALITY,
      STRICT_INEQUALITY
    } kind_t;
    typedef typename linear_expression_t::iterator iterator;
    
  private:
    kind_t _kind;
    linear_expression_t _expr;
    // This flag has meaning only if _kind == INEQUALITY or STRICT_INEQUALITY.
    // If true the inequality is signed otherwise unsigned.
    // By default all constraints are signed.
    bool _signedness;

  public:
    
    linear_constraint(): _kind(EQUALITY), _signedness(true) { }
    
    linear_constraint(const linear_expression_t &expr, kind_t kind)
      : _kind(kind), _expr(expr), _signedness(true) { }    

    linear_constraint(const linear_expression_t &expr, kind_t kind, bool signedness)
      : _kind(kind), _expr(expr), _signedness(signedness) {
      if (_kind != INEQUALITY && _kind != STRICT_INEQUALITY) {
	CRAB_ERROR("Only inequalities can have signedness information");
      }
    }    
    
    static linear_constraint_t get_true () {
      linear_constraint_t res(linear_expression_t(Number(0)), EQUALITY);
      return res;
    }

    static linear_constraint_t get_false () {
      linear_constraint_t res(linear_expression_t(Number(0)), DISEQUATION);
      return res;
    }

    bool is_tautology() const {
      switch (this->_kind) {
        case DISEQUATION: 
          return (this->_expr.is_constant() && this->_expr.constant() != 0);
        case EQUALITY:
          return (this->_expr.is_constant() && this->_expr.constant() == 0);
        case INEQUALITY: 
	  return (this->_expr.is_constant() && this->_expr.constant() <= 0);
        case STRICT_INEQUALITY: 
	  return (this->_expr.is_constant() && this->_expr.constant() < 0);
        default: 
          CRAB_ERROR("Unreachable");
      }
    }
    
    bool is_contradiction() const {
      switch (this->_kind) {
        case DISEQUATION: 
          return (this->_expr.is_constant() && this->_expr.constant() == 0);
        case EQUALITY: 
	  return (this->_expr.is_constant() && this->_expr.constant() != 0);
        case INEQUALITY: 
	  return (this->_expr.is_constant() && this->_expr.constant() > 0);
        case STRICT_INEQUALITY: 
	  return (this->_expr.is_constant() && this->_expr.constant() >= 0);
        default: 
	  CRAB_ERROR("Unreachable");
      }
    }

    bool is_inequality() const {
      return (this->_kind == INEQUALITY);
    }

    bool is_strict_inequality() const {
      return (this->_kind == STRICT_INEQUALITY);
    }
    
    bool is_equality() const {
      return (this->_kind == EQUALITY);
    }

    bool is_disequation() const {
      return (this->_kind == DISEQUATION);
    }

    const linear_expression_t& expression() const {
      return this->_expr;
    }
    
    kind_t kind() const {
      return this->_kind;
    }

    bool is_signed() const {
      if (_kind != INEQUALITY && _kind != STRICT_INEQUALITY) {
	CRAB_WARN("Only inequalities have signedness");	
      }
      return _signedness;
    }

    bool is_unsigned() const {
      return (!is_signed());
    }
    
    void set_signed() {
      if (_kind == INEQUALITY || _kind == STRICT_INEQUALITY) {
	_signedness = true;
      } else {
	CRAB_WARN("Only inequalities have signedness");
      }
    }

    void set_unsigned() {
      if (_kind == INEQUALITY || _kind == STRICT_INEQUALITY) {
	_signedness = false;
      } else {
	CRAB_WARN("Only inequalities have signedness");
      }
    }
    
    iterator begin() const {
      return this->_expr.begin();
    }

    iterator end() const {
      return this->_expr.end();
    }

    Number constant() const {
      return -this->_expr.constant();
    }

    std::size_t size() const {
      return this->_expr.size();
    }

    // syntactic equality
    bool equal(const linear_constraint_t& o) const {
      return (_kind == o._kind &&
	      _signedness == o._signedness &&
	      _expr.equal(o._expr));
    }
    
    size_t hash () const {
      size_t res = 0;
      boost::hash_combine (res, _expr);
      boost::hash_combine (res, _kind);
      if (_kind == INEQUALITY || _kind == STRICT_INEQUALITY) {
	boost::hash_combine (res, _signedness);
      }
      return res;
    }

    index_t index() const {
      // XXX: to store linear constraints in patricia trees 
      return (index_t) hash();
    }
    
    Number operator[](variable_t x) const {
      return this->_expr.operator[](x);
    }

    variable_set_t variables() const {
      return this->_expr.variables();
    }

    linear_constraint_t negate() const;

    template<typename VarMap>
    boost::optional<linear_constraint_t> rename(const VarMap& map) const {

      boost::optional<linear_expression_t> e = this->_expr.rename(map);
      if (e) {
        return linear_constraint_t(*e, this->_kind, is_signed());
      } else {
        return boost::optional<linear_constraint_t>();
      }
    }

    
    void write(crab::crab_os& o) {
      if (this->is_contradiction()) {
        o << "false";
      } else if (this->is_tautology()) {
        o << "true";
      } else {
        linear_expression_t e = this->_expr - this->_expr.constant();
        o << e;
        switch (this->_kind) {
	case INEQUALITY: {
	  if (is_signed()) {
	    o << " <= ";
	  } else {
	    o << " <=_u ";
	  } 
	  break;
	}
	case STRICT_INEQUALITY: {
	  if (is_signed()) {
	    o << " < ";
	  } else {
	    o << " <_u ";
	  }
	  break;
	}	  
	case EQUALITY: {
            o << " = ";
            break;
          }
	case DISEQUATION: {
            o << " != ";
            break;
          }
        }
        Number c = -this->_expr.constant();
        o << c;
      }
    }

    // for dgb
    void dump() {
      write(crab::outs());
    }
    
  }; // class linear_constraint

  namespace linear_constraint_impl{
    
    template<typename Number, typename VariableName>
    linear_constraint<Number, VariableName>
    negate_inequality(const linear_constraint<Number, VariableName>& c) {
      typedef linear_expression<Number, VariableName> linear_expression_t;
      typedef linear_constraint<Number, VariableName> linear_constraint_t;
      assert(c.is_inequality());
      // default implementation: negate(e <= 0) = e > 0 
      linear_expression_t e(-c.expression());
      return linear_constraint_t(e, linear_constraint_t::kind_t::STRICT_INEQUALITY,
				 c.is_signed());
    }

    // Specialized version for z_number
    template<typename VariableName>
    linear_constraint<z_number, VariableName>
    negate_inequality(const linear_constraint<z_number, VariableName>& c) {
      typedef linear_expression<z_number, VariableName> linear_expression_t;
      typedef linear_constraint<z_number, VariableName> linear_constraint_t;
      assert(c.is_inequality());
      // negate(e <= 0) = e >= 1
      linear_expression_t e(-(c.expression() - 1));  
      return linear_constraint_t (e, linear_constraint_t::kind_t::INEQUALITY, c.is_signed());
    }

    template<typename Number, typename VariableName>
    linear_constraint<Number, VariableName>
    strict_to_non_strict_inequality(const linear_constraint<Number, VariableName>& c) {
      typedef linear_constraint<Number, VariableName> linear_constraint_t;      
      assert(c.is_strict_inequality());
      // Default implementation: do nothing
      // Given constraint e < 0 we could return two linear constraints: e <= 0 and e != 0.
      // The linear interval solver lowers strict inequalities in that way.
      return c;
    }

    // Specialized version for z_number
    template<typename VariableName>
    linear_constraint<z_number, VariableName>
    strict_to_non_strict_inequality(const linear_constraint<z_number, VariableName>& c) {
      typedef linear_expression<z_number, VariableName> linear_expression_t;            
      typedef linear_constraint<z_number, VariableName> linear_constraint_t;
      assert(c.is_strict_inequality());
      // e < 0 --> e <= -1
      linear_expression_t e(c.expression() + 1); 
      return linear_constraint_t(e, linear_constraint_t::kind_t::INEQUALITY, c.is_signed());
    }
  } // end namespace linear_constraint_impl

  template<typename Number, typename VariableName>
  linear_constraint<Number, VariableName>
  linear_constraint<Number,VariableName>::negate() const {
    typedef linear_constraint<Number,VariableName> linear_constraint_t;
    typedef linear_expression<Number,VariableName> linear_expression_t;
    
    if (is_tautology ()) {
      return get_false();
    } else if (is_contradiction ()) {
      return get_true();
    } else {
      switch (kind ()) {
      case INEQUALITY: {
	// negate_inequality tries to take advantage if we use z_number.
	return linear_constraint_impl::negate_inequality(*this);
      }
      case STRICT_INEQUALITY: {
	// negate(x + y < 0)  <-->  x + y >= 0 <--> -x -y <= 0
	linear_expression_t e = -this->_expr;
	return linear_constraint_t (e, INEQUALITY, is_signed());
      }
      case EQUALITY:
	return linear_constraint_t (this->_expr, DISEQUATION);
      case DISEQUATION: 
	return linear_constraint_t (this->_expr, EQUALITY);
      default:
	CRAB_ERROR("Cannot negate linear constraint");       
      }
    }
  }
  
  template<typename Number, typename VariableName>
  inline std::size_t hash_value(const linear_constraint<Number,VariableName>& e) {
    return e.hash ();
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator<=(const linear_expression< Number, VariableName > &e, Number n) {
    return linear_constraint< Number, VariableName >
        (e - n, linear_constraint< Number, VariableName >::INEQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator<=(const linear_expression< Number, VariableName > &e, int n) {
    return linear_constraint< Number, VariableName >
        (e - n, linear_constraint< Number, VariableName >::INEQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator<=(Number n, const linear_expression< Number, VariableName > &e) {
    return linear_constraint< Number, VariableName >
        (n - e, linear_constraint< Number, VariableName >::INEQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator<=(int n, const linear_expression< Number, VariableName > &e) {
    return linear_constraint< Number, VariableName >
        (n - e, linear_constraint< Number, VariableName >::INEQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator<=(const linear_expression< Number, VariableName > &e, 
             variable< Number, VariableName > x) {
    return linear_constraint< Number, VariableName >
        (e - x, linear_constraint< Number, VariableName >::INEQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator<=(variable< Number, VariableName > x, 
             const linear_expression< Number, VariableName > &e) {
    return linear_constraint< Number, VariableName >
        (x - e, linear_constraint< Number, VariableName >::INEQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator<=(variable< Number, VariableName > x, Number n) {
    return linear_constraint< Number, VariableName >
        (x - n, linear_constraint< Number, VariableName >::INEQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator<=(variable< Number, VariableName > x, int n) {
    return linear_constraint< Number, VariableName >
        (x - n, linear_constraint< Number, VariableName >::INEQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator<=(Number n, variable< Number, VariableName > x) {
    return linear_constraint< Number, VariableName >
        (n - x, linear_constraint< Number, VariableName >::INEQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator<=(int n, variable< Number, VariableName > x) {
    return linear_constraint< Number, VariableName >
        (n - x, linear_constraint< Number, VariableName >::INEQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator<=(variable< Number, VariableName > x, variable< Number, VariableName > y) {
    return linear_constraint< Number, VariableName >
        (x - y, linear_constraint< Number, VariableName >::INEQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator<=(const linear_expression< Number, VariableName >& e1, 
             const linear_expression< Number, VariableName >& e2) {
    return linear_constraint< Number, VariableName >
        (e1 - e2, linear_constraint< Number, VariableName >::INEQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator>=(const linear_expression< Number, VariableName > &e, Number n) {
    return linear_constraint< Number, VariableName >
        (n - e, linear_constraint< Number, VariableName >::INEQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator>=(const linear_expression< Number, VariableName > &e, int n) {
    return linear_constraint< Number, VariableName >
        (n - e, linear_constraint< Number, VariableName >::INEQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator>=(Number n, const linear_expression< Number, VariableName > &e) {
    return linear_constraint< Number, VariableName >
        (e - n, linear_constraint< Number, VariableName >::INEQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator>=(int n, const linear_expression< Number, VariableName > &e) {
    return linear_constraint< Number, VariableName >
        (e - n, linear_constraint< Number, VariableName >::INEQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator>=(const linear_expression< Number, VariableName > &e, 
             variable< Number, VariableName > x) {
    return linear_constraint< Number, VariableName >
        (x - e, linear_constraint< Number, VariableName >::INEQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator>=(variable< Number, VariableName > x,
             const linear_expression< Number, VariableName > &e) {
    return linear_constraint< Number, VariableName >
        (e - x, linear_constraint< Number, VariableName >::INEQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator>=(variable< Number, VariableName > x, Number n) {
    return linear_constraint< Number, VariableName >
        (n - x, linear_constraint< Number, VariableName >::INEQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator>=(variable< Number, VariableName > x, int n) {
    return linear_constraint< Number, VariableName >
        (n - x, linear_constraint< Number, VariableName >::INEQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator>=(Number n, variable< Number, VariableName > x) {
    return linear_constraint< Number, VariableName >
        (x - n, linear_constraint< Number, VariableName >::INEQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator>=(int n, variable< Number, VariableName > x) {
    return linear_constraint< Number, VariableName >
        (x - n, linear_constraint< Number, VariableName >::INEQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator>=(variable< Number, VariableName > x, 
             variable< Number, VariableName > y) {
    return linear_constraint< Number, VariableName >
        (y - x, linear_constraint< Number, VariableName >::INEQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator>=(const linear_expression< Number, VariableName > &e1, 
             const linear_expression< Number, VariableName > &e2) {
    return linear_constraint< Number, VariableName >
        (e2 - e1, linear_constraint< Number, VariableName >::INEQUALITY);
  }

  template<typename Number, typename VariableName>
  inline linear_constraint<Number, VariableName> 
  operator<(const linear_expression<Number, VariableName> &e, Number n) {
    return linear_constraint<Number, VariableName>
      (e - n, linear_constraint<Number, VariableName>::STRICT_INEQUALITY);
  }

  template<typename Number, typename VariableName>
  inline linear_constraint<Number, VariableName> 
  operator<(const linear_expression<Number, VariableName> &e, int n) {
    return linear_constraint<Number, VariableName>
      (e - n, linear_constraint<Number, VariableName>::STRICT_INEQUALITY);
  }

  template<typename Number, typename VariableName>
  inline linear_constraint<Number, VariableName> 
  operator<(Number n, const linear_expression<Number, VariableName> &e) {
    return linear_constraint<Number, VariableName>
      (n - e, linear_constraint<Number, VariableName>::STRICT_INEQUALITY);
  }

  template<typename Number, typename VariableName>
  inline linear_constraint<Number, VariableName> 
  operator<(int n, const linear_expression<Number, VariableName> &e) {
    return linear_constraint<Number, VariableName>
      (n - e, linear_constraint<Number, VariableName>::STRICT_INEQUALITY);
  }

  template<typename Number, typename VariableName>
  inline linear_constraint<Number, VariableName> 
  operator<(const linear_expression<Number, VariableName> &e, 
	    variable<Number, VariableName> x) {
    return linear_constraint<Number, VariableName>
      (e - x, linear_constraint<Number, VariableName>::STRICT_INEQUALITY);
  }

  template<typename Number, typename VariableName>
  inline linear_constraint<Number, VariableName> 
  operator<(variable<Number, VariableName> x, 
	    const linear_expression<Number, VariableName> &e) {
    return linear_constraint<Number, VariableName>
      (x - e, linear_constraint<Number, VariableName>::STRICT_INEQUALITY);
  }

  template<typename Number, typename VariableName>
  inline linear_constraint<Number, VariableName> 
  operator<(variable<Number, VariableName> x, Number n) {
    return linear_constraint<Number, VariableName>
      (x - n, linear_constraint<Number, VariableName>::STRICT_INEQUALITY);
  }

  template<typename Number, typename VariableName>
  inline linear_constraint<Number, VariableName> 
  operator<(variable<Number, VariableName> x, int n) {
    return linear_constraint<Number, VariableName>
      (x - n, linear_constraint<Number, VariableName>::STRICT_INEQUALITY);
  }

  template<typename Number, typename VariableName>
  inline linear_constraint<Number, VariableName> 
  operator<(Number n, variable<Number, VariableName> x) {
    return linear_constraint<Number, VariableName>
      (n - x, linear_constraint<Number, VariableName>::STRICT_INEQUALITY);
  }

  template<typename Number, typename VariableName>
  inline linear_constraint<Number, VariableName> 
  operator<(int n, variable<Number, VariableName> x) {
    return linear_constraint<Number, VariableName>
      (n - x, linear_constraint<Number, VariableName>::STRICT_INEQUALITY);
  }

  template<typename Number, typename VariableName>
  inline linear_constraint<Number, VariableName> 
  operator<(variable<Number, VariableName> x, variable<Number, VariableName> y) {
    return linear_constraint<Number, VariableName>
      (x - y, linear_constraint<Number, VariableName>::STRICT_INEQUALITY);
  }
  
  template<typename Number, typename VariableName>
  inline linear_constraint<Number, VariableName> 
  operator<(const linear_expression<Number, VariableName>& e1, 
	    const linear_expression<Number, VariableName>& e2) {
    return linear_constraint<Number, VariableName>
      (e1 - e2, linear_constraint<Number, VariableName>::STRICT_INEQUALITY);
  }

  template<typename Number, typename VariableName>
  inline linear_constraint<Number, VariableName> 
  operator>(const linear_expression<Number, VariableName> &e, Number n) {
    return linear_constraint<Number, VariableName>
      (n - e, linear_constraint<Number, VariableName>::STRICT_INEQUALITY);
  }
  
  template<typename Number, typename VariableName>
  inline linear_constraint<Number, VariableName> 
  operator>(const linear_expression<Number, VariableName> &e, int n) {
    return linear_constraint<Number, VariableName>
      (n - e, linear_constraint<Number, VariableName>::STRICT_INEQUALITY);
  }
  
  template<typename Number, typename VariableName>
  inline linear_constraint<Number, VariableName> 
  operator>(Number n, const linear_expression<Number, VariableName> &e) {
    return linear_constraint<Number, VariableName>
      (e - n, linear_constraint<Number, VariableName>::STRICT_INEQUALITY);
  }

  template<typename Number, typename VariableName>
  inline linear_constraint<Number, VariableName> 
  operator>(int n, const linear_expression<Number, VariableName> &e) {
    return linear_constraint<Number, VariableName>
      (e - n, linear_constraint<Number, VariableName>::STRICT_INEQUALITY);
  }

  template<typename Number, typename VariableName>
  inline linear_constraint<Number, VariableName> 
  operator>(const linear_expression<Number, VariableName> &e, 
	    variable<Number, VariableName> x) {
    return linear_constraint<Number, VariableName>
      (x - e, linear_constraint<Number, VariableName>::STRICT_INEQUALITY);
  }
  
  template<typename Number, typename VariableName>
  inline linear_constraint<Number, VariableName> 
  operator>(variable<Number, VariableName> x,
	    const linear_expression<Number, VariableName> &e) {
    return linear_constraint<Number, VariableName>
      (e - x, linear_constraint<Number, VariableName>::STRICT_INEQUALITY);
  }

  template<typename Number, typename VariableName>
  inline linear_constraint<Number, VariableName> 
  operator>(variable<Number, VariableName> x, Number n) {
    return linear_constraint<Number, VariableName>
      (n - x, linear_constraint<Number, VariableName>::STRICT_INEQUALITY);
  }

  template<typename Number, typename VariableName>
  inline linear_constraint<Number, VariableName> 
  operator>(variable<Number, VariableName> x, int n) {
    return linear_constraint<Number, VariableName>
      (n - x, linear_constraint<Number, VariableName>::STRICT_INEQUALITY);
  }

  template<typename Number, typename VariableName>
  inline linear_constraint<Number, VariableName> 
  operator>(Number n, variable<Number, VariableName> x) {
    return linear_constraint<Number, VariableName>
      (x - n, linear_constraint<Number, VariableName>::STRICT_INEQUALITY);
  }

  template<typename Number, typename VariableName>
  inline linear_constraint<Number, VariableName> 
  operator>(int n, variable<Number, VariableName> x) {
    return linear_constraint<Number, VariableName>
      (x - n, linear_constraint<Number, VariableName>::STRICT_INEQUALITY);
  }

  template<typename Number, typename VariableName>
  inline linear_constraint<Number, VariableName> 
  operator>(variable<Number, VariableName> x, 
	    variable<Number, VariableName> y) {
    return linear_constraint<Number, VariableName>
      (y - x, linear_constraint<Number, VariableName>::STRICT_INEQUALITY);
  }

  template<typename Number, typename VariableName>
  inline linear_constraint<Number, VariableName> 
  operator>(const linear_expression<Number, VariableName> &e1, 
	    const linear_expression<Number, VariableName> &e2) {
    return linear_constraint<Number, VariableName>
      (e2 - e1, linear_constraint<Number, VariableName>::STRICT_INEQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator==(const linear_expression< Number, VariableName > &e, Number n) {
    return linear_constraint< Number, VariableName >
        (e - n, linear_constraint< Number, VariableName >::EQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator==(const linear_expression< Number, VariableName > &e, int n) {
    return linear_constraint< Number, VariableName >
        (e - n, linear_constraint< Number, VariableName >::EQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator==(Number n, const linear_expression< Number, VariableName > &e) {
    return linear_constraint< Number, VariableName >
        (e - n, linear_constraint< Number, VariableName >::EQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator==(int n, const linear_expression< Number, VariableName > &e) {
    return linear_constraint< Number, VariableName >
        (e - n, linear_constraint< Number, VariableName >::EQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator==(const linear_expression< Number, VariableName > &e, 
             variable< Number, VariableName > x) {
    return linear_constraint< Number, VariableName >
        (e - x, linear_constraint< Number, VariableName >::EQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator==(variable< Number, VariableName > x, 
             const linear_expression< Number, VariableName > &e) {
    return linear_constraint< Number, VariableName >
        (e - x, linear_constraint< Number, VariableName >::EQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator==(variable< Number, VariableName > x, Number n) {
    return linear_constraint< Number, VariableName >
        (x - n, linear_constraint< Number, VariableName >::EQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator==(variable< Number, VariableName > x, int n) {
    return linear_constraint< Number, VariableName >
        (x - n, linear_constraint< Number, VariableName >::EQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator==(Number n, variable< Number, VariableName > x) {
    return linear_constraint< Number, VariableName >
        (x - n, linear_constraint< Number, VariableName >::EQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator==(int n, variable< Number, VariableName > x) {
    return linear_constraint< Number, VariableName >
        (x - n, linear_constraint< Number, VariableName >::EQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator==(variable< Number, VariableName > x, 
             variable< Number, VariableName > y) {
    return linear_constraint< Number, VariableName >
        (x - y, linear_constraint< Number, VariableName >::EQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator==(const linear_expression< Number, VariableName > &e1, 
             const linear_expression< Number, VariableName > &e2) {
    return linear_constraint< Number, VariableName >
        (e1 - e2, linear_constraint< Number, VariableName >::EQUALITY);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator!=(const linear_expression< Number, VariableName > &e, Number n) {
    return linear_constraint< Number, VariableName >
        (e - n, linear_constraint< Number, VariableName >::DISEQUATION);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator!=(const linear_expression< Number, VariableName > &e, int n) {
    return linear_constraint< Number, VariableName >
        (e - n, linear_constraint< Number, VariableName >::DISEQUATION);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator!=(Number n, const linear_expression< Number, VariableName > &e) {
    return linear_constraint< Number, VariableName >
        (e - n, linear_constraint< Number, VariableName >::DISEQUATION);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator!=(int n, const linear_expression< Number, VariableName > &e) {
    return linear_constraint< Number, VariableName >
        (e - n, linear_constraint< Number, VariableName >::DISEQUATION);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator!=(const linear_expression< Number, VariableName > &e, 
             variable< Number, VariableName > x) {
    return linear_constraint< Number, VariableName >
        (e - x, linear_constraint< Number, VariableName >::DISEQUATION);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator!=(variable< Number, VariableName > x, 
             const linear_expression< Number, VariableName > &e) {
    return linear_constraint< Number, VariableName >
        (e - x, linear_constraint< Number, VariableName >::DISEQUATION);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator!=(variable< Number, VariableName > x, Number n) {
    return linear_constraint< Number, VariableName >
        (x - n, linear_constraint< Number, VariableName >::DISEQUATION);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator!=(variable< Number, VariableName > x, int n) {
    return linear_constraint< Number, VariableName >
        (x - n, linear_constraint< Number, VariableName >::DISEQUATION);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator!=(Number n, variable< Number, VariableName > x) {
    return linear_constraint< Number, VariableName >
        (x - n, linear_constraint< Number, VariableName >::DISEQUATION);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator!=(int n, variable< Number, VariableName > x) {
    return linear_constraint< Number, VariableName >
        (x - n, linear_constraint< Number, VariableName >::DISEQUATION);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator!=(variable< Number, VariableName > x, 
             variable< Number, VariableName > y) {
    return linear_constraint< Number, VariableName >
        (x - y, linear_constraint< Number, VariableName >::DISEQUATION);
  }

  template< typename Number, typename VariableName >
  inline linear_constraint< Number, VariableName > 
  operator!=(const linear_expression< Number, VariableName > &e1, 
             const linear_expression< Number, VariableName > &e2) {
    return linear_constraint< Number, VariableName >
        (e1 - e2, linear_constraint< Number, VariableName >::DISEQUATION);
  }

  template< typename Number, typename VariableName >
  class linear_constraint_system: public writeable {

  public:
    typedef Number number_t;
    typedef VariableName varname_t;
    typedef linear_constraint< Number, VariableName > linear_constraint_t;
    typedef linear_constraint_system< Number, VariableName > linear_constraint_system_t;
    typedef variable< Number, VariableName > variable_t;
    typedef patricia_tree_set< variable_t > variable_set_t;

  private:
    typedef std::vector<linear_constraint_t> cst_collection_t;

  public:
    typedef typename cst_collection_t::const_iterator iterator;

  private:
    cst_collection_t _csts;

  public:
    linear_constraint_system() { }

    linear_constraint_system(const linear_constraint_t &cst) {
      _csts.push_back(cst);
    }

    linear_constraint_system(const linear_constraint_system_t &o)
        : _csts (o._csts) { }

    linear_constraint_system(linear_constraint_system_t &&o)
        : _csts (std::move(o._csts)) { }

    linear_constraint_system_t& 
    operator+=(const linear_constraint_t &c) {
      if (!std::any_of(_csts.begin(),_csts.end(),
		       [c](const linear_constraint_t& c1)
		       {return c1.equal(c);})) {
	_csts.push_back(c);
      }
      return *this;
    }

    linear_constraint_system_t& 
    operator+=(const linear_constraint_system_t &s) {
      for (auto c: s) {
	if (!std::any_of(_csts.begin(),_csts.end(),
			 [c](const linear_constraint_t& c1)
			 {return c1.equal(c);})) {	
	  _csts.push_back(c);
	}
      }
      return *this;
    }

    linear_constraint_system_t 
    operator+(const linear_constraint_system_t &s) const {
      linear_constraint_system_t r;
      r.operator+=(s);
      r.operator+=(*this);
      return r;
    }

    iterator begin() const { return _csts.begin(); }

    iterator end() const { return _csts.end(); }

    variable_set_t variables() const {
      variable_set_t variables;
      for (auto c: *this)
        variables |= c.variables();
      return variables;
    }

    // TODO: expensive linear operation.
    // XXX: We can keep track of whether the system is false in an
    // incremental manner.
    bool is_false () const {
      if (_csts.empty ())
	return false; // empty is considered true
      
      for (auto it = this->begin(); it != this->end(); ++it) {
        auto c = *it;
	if (!c.is_contradiction ()) {
	  return false;
	}
      }
      return true; // all constraints are false
    }

    bool is_true() const {
      return _csts.empty();
    }
    
    std::size_t size() const { return _csts.size(); }
        
    void write(crab::crab_os& o) {
      o << "{";
      for (iterator it = this->begin(); it != this->end();) {
        auto c = *it;
        o << c;
        ++it;
        if (it != end()) {
        o << "; ";
        }
      }
      o << "}";
    }

    // for dgb
    void dump() {
      write(crab::outs());
    }
    
  }; // class linear_constraint_system


  // This class contains a disjunction of linear constraints (i.e., DNF form)
  template< typename Number, typename VariableName >
  class disjunctive_linear_constraint_system: public writeable {

  public:
    typedef Number number_t;
    typedef VariableName varname_t;
    typedef linear_constraint<Number,VariableName> linear_constraint_t;
    typedef linear_constraint_system<Number,VariableName> linear_constraint_system_t;
    typedef disjunctive_linear_constraint_system<Number,VariableName> this_type;
    
  private:
    typedef std::vector<linear_constraint_system_t> cst_collection_t;
    cst_collection_t _csts;
    bool _is_false;

  public:
    typedef typename cst_collection_t::const_iterator iterator;

    disjunctive_linear_constraint_system(bool is_false = false)
      : _is_false (is_false) {}

    explicit disjunctive_linear_constraint_system(const linear_constraint_system_t &cst)
      : _is_false (false) {
      if (cst.is_false ()) {
	_is_false = true;
      } else {
	_csts.push_back(cst);
      }
    }

    disjunctive_linear_constraint_system(const this_type &o)
      : _csts (o._csts)
      , _is_false(o._is_false) { }

    disjunctive_linear_constraint_system(this_type &&o)
      : _csts (std::move(o._csts))
      , _is_false(o._is_false) { }

    bool is_false () const {
      return _is_false;
    }

    bool is_true () const {
      return (!is_false() && _csts.empty());
    }

    // make true
    void clear() {
      _is_false = false;
      _csts.clear();
    }

    /*
      c1 or ... or cn  += true  ==> error
      c1 or ... or cn  += false ==> c1 or .. or cn
      c1 or ... or cn  += c     ==> c1 or ... or cn or c
    */
    this_type& operator+=(const linear_constraint_system_t &cst) {
      if (cst.is_true()) {
	// adding true should make the whole thing true
	// but we prefer to raise an error for now.
	CRAB_ERROR("Disjunctive linear constraint: cannot add true");	
      }

      if (!cst.is_false()) {
	_csts.push_back(cst);
	_is_false = false;
      }
      return *this;
    }

    /*
      c1 or ... or cn  += true  ==> error
      c1 or ... or cn  += false ==> c1 or .. or cn
      c1 or ... or cn  += d1 or ... or dn   ==> c1 or ... or cn or d1 or ... or dn
    */
    this_type& operator+=(const this_type &s) {
      if (s.is_true()) {
	// adding true should make the whole thing true
	// but we prefer to raise an error for now.
	CRAB_ERROR("Disjunctive linear constraint: cannot add true");
      }
      if (!s.is_false()) {
	for (const linear_constraint_system_t& c: s) {
	  this->operator+=(c);
	}
      }
      return *this;
    }

    this_type operator+(const this_type &s) const {
      this_type r;
      r.operator+=(s);
      r.operator+=(*this);
      return r;
    }

    // To enumerate all the conjunctions
    iterator begin() const {      
      if (is_false ())
	CRAB_ERROR("Disjunctive Linear constraint: trying to call begin() when false");
      return _csts.begin();
    }

    iterator end() const {
      if (is_false ())
	CRAB_ERROR("Disjunctive Linear constraint: trying to call end() when false");      
      return _csts.end();
    }

    // Return the number of conjunctions
    std::size_t size() const { return _csts.size(); }
        
    void write(crab::crab_os& o) {
      if (is_false ()) {
	o << "_|_";
      } else if (is_true()) {
	o << "{}";
      } else if (size () == 1) {
	o << _csts[0];
      } else {
	assert (size () > 1);
	for (iterator it = this->begin(); it != this->end();) {
	  auto c = *it;
	  o << c;
	  ++it;
	  if (it != end()) {
	    o << " or \n";
	  }
	}
      }
    }
  }; 
  
} // namespace ikos

