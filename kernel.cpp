#include <functional>
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

  void print()
  {
    if(this->m_prev[0])
      std::cout << this->m_data << " (grad:"<<this->m_grad << ")"<<" got from: " << this->m_prev[0]->m_data << this->m_op << this->m_prev[1]->m_data << std::endl;
    else
      std::cout << this->m_data <<" (grad:"<<this->m_grad<< ") "<<std::endl;
  }
};

 

int main()
{
 Vector<int> a(2);
 Vector<int> b(3);
 Vector<int> c = a + b;
 Vector<int> d(2);
 Vector<int> e = c * d;

 e.backward();

 a.print();
 b.print();
 c.print();
 d.print();
 e.print();

 return 0;
}
