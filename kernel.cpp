#include <cmath>
#include <string>
#include <map>
#include <stack>

template<typename T>
class Vector
{
public:
  T m_data;
  double m_grad = 0.0;
  Vector* m_prev[2] = {nullptr, nullptr};
  std::string m_op = "";
  std::string m_label = "";

  Vector(T value, std::string name="-")
  {
    this->m_data = value;
    this->m_label = name;
  }
  Vector(T value, Vector* a, Vector* b, std::string op, std::string name="-")
  {
    this->m_prev[0] = a;
    this->m_prev[1] = b;
    this->m_data = value;
    this->m_op = op;
    this->m_label = name;
  }

  Vector operator+(Vector& other)
  {
    Vector<T> out(this->m_data + other.m_data, this, &other,"+");
    return out;
  }

  Vector operator+(Vector&& other)
  {
    Vector<T> out(this->m_data + other.m_data, this, &other,"+");
    return out;
  }

  Vector operator*(Vector& other)
  {
    Vector<T> out(this->m_data * other.m_data, this, &other, "*");
    return out;
  }

  Vector operator*(Vector&& other)
  {
    Vector<T> out(this->m_data * other.m_data, this, &other, "*");
    return out;
  }

  Vector operator/(Vector& other)
  {
    Vector<T> out(this->m_data * (1/other.m_data), this, &other, "/");
    return out;
  }

  Vector pow(Vector& other)
  {
    Vector<T> out(std::pow(this->m_data,other.m_data), this, &other, "^");  
    return out;
  }

  Vector tanh()
  {
    Vector<T> out(std::tanh(this->m_data), this, nullptr, "tanh");
    return out;
  }

  void _backwardUtil()
  {
    if (this->m_op == "+"){
      this->m_prev[0]->m_grad += this->m_grad;
      this->m_prev[1]->m_grad += this->m_grad;
    }
    else if(this->m_op == "*"){
      this->m_prev[0]->m_grad += this->m_grad * this->m_prev[1]->m_data;
      this->m_prev[1]->m_grad += this->m_grad * this->m_prev[0]->m_data;
    }
    else if(this->m_op == "^"){
      this->m_prev[0]->m_grad += this->m_grad * this->m_prev[1]->m_data * std::pow(this->m_prev[0]->m_data,this->m_prev[1]->m_data-1);
      this->m_prev[1]->m_grad += this->m_grad * std::pow(this->m_prev[0]->m_data,this->m_prev[1]->m_data) * std::log(this->m_prev[0]->m_data);
    }
    else if(this->m_op == "/"){
      this->m_prev[0]->m_grad += this->m_grad * (1/this->m_prev[1]->m_data);
      this->m_prev[1]->m_grad += this->m_grad * (-1 * this->m_prev[0]->m_data)/(std::pow(this->m_prev[1]->m_data,2));
    }
    else if(this->m_op == "tanh"){
      this->m_prev[0]->m_grad += this->m_grad * (1-std::pow(this->m_data,2));
    }
    else return;

    // recursion
    if (this->m_prev[0]) this->m_prev[0]->_backwardUtil();
    if (this->m_prev[1]) this->m_prev[1]->_backwardUtil();
  }

  void backward()
  {
    this->m_grad = 1.0; 
    _backwardUtil();
  }

};
