# Nanograd
Toy backpropagation framework around scalar 1d vectors. Automatically differentiates and computes all the necessary gradient vectors. Written in C++.

![full_graph_autograd](https://user-images.githubusercontent.com/103335583/186056952-56dc4734-b9cf-4a9e-af7d-e6316567aee4.png)
Nice TODO
-----
* Add suport for multi-dimensional scalar vectors

Usage
-----
```c++
Vector<float> a = 2, b = 3;
Vector<float> c = a + b;
Vector<float> d = 2;
Vector<float> e = c * d;

e.print(); // prints the value of e and its parent vectors (c and d)
e.backward(); // backpropagation; updates all the gradients accordingly

std::cout << c.m_grad << std::endl; // prints the gradient of c; 
```
Implementation
-----
Based on:
  * https://pytorch.org/docs/stable/autograd.html
  * https://github.com/karpathy/micrograd/
