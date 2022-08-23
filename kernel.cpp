#include <functional>
#include <cmath>
#include <iostream>

using namespace std;

template<typename T>
class Vector
{
public:
  T m_data;
  float m_grad = 0.0;
  Vector* m_prev[2] = {nullptr, nullptr};
  char m_op;
  std::function<void()> _backward = [&]() {};

  Vector(T value)
  {
    this->m_data = value;
  }
  Vector(T value, Vector* a, Vector* b, char op)
  {
    this->m_prev[0] = a;
    this->m_prev[1] = b;
    this->m_data = value;
    this->m_op = op;
  }

  Vector operator+(Vector& other)
  {
    Vector<T> out(this->m_data + other.m_data, this, &other, '+');
    out._backward = [&]() {
      this->m_grad += out.m_grad;
      other.m_grad += out.m_grad;
    };
    return out;
  }

/*  Vector operator+(T in)
  {
    Vector<T> other = in;
    Vector<T> out(this->m_data + other.m_data, this, &other, '+');
    out._backward = [&]() {
      this->m_grad += out.m_grad;
    };
    return out;
  }
*/

  Vector operator*(Vector& other)
  {
    Vector<T> out(this->m_data * other.m_data, this, &other, '*');
    out._backward = [&]() {
      this->m_grad += out.m_grad * other.m_data;
      other.m_grad += out.m_grad * this->m_data;
    }; 
    return out;
  }

  Vector& operator=(Vector& other)
  {
    this->m_data = other.m_data;
    this->m_grad = other.m_grad;
    return *this;
  }

  Vector pow(T exponent)
  {
    // TODO: add support for Vector^Vector exponentiation
    Vector<T> exp = exponent;
    Vector<T> out(std::pow(this->m_data,exp.m_data), this, &exp, '^');  
    out._backward = [&](){
      this->m_grad = out.m_grad * exp.m_data * std::pow(this->m_data,exp.m_data-1);
    };
    return out;
  }
  
  void backwardUtil()
  {
    this->_backward();

    if (this->m_prev[0]) this->m_prev[0]->backwardUtil();
    if (this->m_prev[1]) this->m_prev[1]->backwardUtil();
  }

  void backward()
  {
    this->m_grad = 1.0; 
    backwardUtil();
  }

};

template<typename T>
void print(Vector<T>& vector)
{
  if(vector.m_prev[0] and vector.m_prev[1]){
    std::cout << vector.m_data << " (grad:"<<vector.m_grad << ")"<<" got from: " << vector.m_prev[0]->m_data << vector.m_op << vector.m_prev[1]->m_data << std::endl;
    print(*vector.m_prev[0]);
    print(*vector.m_prev[1]);
  }
  else
    std::cout << vector.m_data <<" (grad:"<<vector.m_grad<< ") "<<"got from: -"<<std::endl;
}

int main()
{
 Vector<float> a = 2, b = 3, d = 2;
 Vector<float> c = (a + b);
 Vector<float> e = c * d;
 
 e.backward();
 print(e);

 return 0;
}
