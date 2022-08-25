#include "kernel.cpp"
#include <iostream>
#include <map>
#include <stack>

template<typename T>
std::stack<Vector<T>*> dfs(Vector<T>* vertex)
{
  static std::map<Vector<T>*,bool> visited;
  static std::stack<Vector<T>*> topo;

  if (visited[vertex] == true) return topo;

  visited[vertex] = true;    

  if(vertex->m_prev[0] && vertex->m_prev[1])
    std::cout << vertex->m_label << " : " << vertex->m_data << " (grad:"<< vertex->m_grad << ")"
    << " got from: " << vertex->m_prev[0]->m_label << vertex->m_op << vertex->m_prev[1]->m_label << std::endl;
  else if (vertex->m_op=="tanh")
    std::cout << vertex->m_label << " : " << vertex->m_data << " (grad:"<< vertex->m_grad << ")"
    << " got from: " << "tanh " << vertex->m_prev[0]->m_label << std::endl;
  else
    std::cout << vertex->m_label << " : " << vertex->m_data << " (grad:"<<vertex->m_grad << ")" << std::endl;

  if(vertex->m_prev[0]) dfs(vertex->m_prev[0]);
  if(vertex->m_prev[1]) dfs(vertex->m_prev[1]);
  topo.push(vertex); 
  return topo;
}

template<typename T>
void print(Vector<T>& vertex)
{
  std::stack<Vector<T>*> topo;
  topo = dfs(&vertex);
  while(!topo.empty()){
    auto v = topo.top();
    topo.pop();
    std::cout << v->m_label << std::endl;
  }
}

int main()
{
  Vector<double> a(2,"a"), b(3,"b"), c(4,"c"), d(5,"d"), e(6,"e");
  Vector<double> f = ( (a+b) + d ) * c;
// auto inter = a + b; inter.m_label="inter";
  f.backward(); f.m_label="f";

  print(f);

  return 0;
}
