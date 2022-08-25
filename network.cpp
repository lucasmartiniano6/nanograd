#include "kernel.cpp"

#include <iostream>
#include <map>

template<typename T>
void print(Vector<T>& vector)
{
  static std::map<Vector<T>*,bool> visited;
  Vector<T>* vertex = &vector; 

  if (visited[vertex] == true) return;

  visited[vertex] = true;    

  if(vertex->m_prev[0] && vertex->m_prev[1])
    std::cout << vertex->m_label << " : " << vertex->m_data << " (grad:"<< vertex->m_grad << ")"
    << " got from: " << vertex->m_prev[0]->m_label << vertex->m_op << vertex->m_prev[1]->m_label << std::endl;
  else if (vertex->m_op=="tanh")
    std::cout << vertex->m_label << " : " << vertex->m_data << " (grad:"<< vertex->m_grad << ")"
    << " got from: " << "tanh " << vertex->m_prev[0]->m_label << std::endl;
  else
    std::cout << vertex->m_label << " : " << vertex->m_data << " (grad:"<<vertex->m_grad << ")" << std::endl;

  if(vertex->m_prev[0]) print(*vertex->m_prev[0]);
  if(vertex->m_prev[1]) print(*vertex->m_prev[1]);
}

int main()
{
  Vector<double> a(2,"a"), b(3,"b"), c(4,"c"), d(5,"d"), e(6,"e");
  auto f = ( (a+b) + d ) * c;
  f.backward(); f.m_label="f";
  print(f);
  return 0;
}
