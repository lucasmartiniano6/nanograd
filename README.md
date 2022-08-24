# Nanograd
Toy backpropagation framework around scalar 1d vectors. Automatically differentiates and computes all the necessary gradient vectors. Written in C++.

![full_graph_autograd](https://user-images.githubusercontent.com/103335583/186056952-56dc4734-b9cf-4a9e-af7d-e6316567aee4.png)
Nice TODO
-----
* Add suport for multi-dimensional scalar vectors

Usage
-----
```c++
Vector<float> a = 2; 
Vector<float> b(4, "b");
Vector<float> c = a + b;

Vector<float> d = ((a*b).pow(c)) + a;

a.m_label="a"; c.m_label="c"; d.m_label="d";

d.backward(); // backpropagation; updates all the gradients accordingly
d.print(); // recursively prints the whole chain of operations up to d; including data & gradients

std::cout << a.m_grad << std::endl; // prints only the gradient of vector a
```
Implementation
-----
Based on:
  * https://pytorch.org/docs/stable/autograd.html
  * https://github.com/karpathy/micrograd/
