#pragma once

#include<bits/stdc++.h>
#include"orderbook.h"

/*
struct Comparator {
  bool operator()(const Order& a, const Order& b)
  {
    return a.price < b.price;
  }
};
*/

template<typename T = Order, typename Comparator = std::less<T>>
class PriorityQueue : public std::priority_queue<T, std::vector<T>, Comparator> {
  public:
    PriorityQueue() {
    }

    typedef typename std::vector<T>::iterator iterator;
    iterator searchIterator(const std::string& orderId) {
      auto& c = this->c;
      auto& it = *std::find_if(c.begin(), c.end(), [&](const T& order) {
          return order.orderId == orderId;
        });
      return it;
    }

    void update(const std::string& orderId, T newOrder) {
      auto& it = searchIterator(orderId);
      it = newOrder;
    }

    T search(const std::string& orderId) {
      auto& it = searchIterator(orderId);
      return *it;
    }

    bool remove(const std::string orderId) {
      auto& it = searchIterator(orderId);
      if (it != this->c.end()) {
        this->c.erase(it);
        std::make_heap(this->c.begin(), this->c.end(),this->comp);
        return true;
      }
      else {
        return false;
      }
     }
};
