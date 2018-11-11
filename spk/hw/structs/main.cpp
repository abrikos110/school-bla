#include <iostream>
#include <chrono>
#include <cstdlib>
#include <vector>
#include <algorithm>

#include "list.hpp"
#include "stack.hpp"
#include "queue.hpp"
#include "sorted_array.hpp"
#include "treap.hpp"
#include "dyn_array.hpp"
#include "heap.hpp"

long long int time_ns(long long int tp = 0) {
    return
        std::chrono::duration_cast<std::chrono::nanoseconds>
        (
            std::chrono::steady_clock::now()
            .time_since_epoch()
        ).count()
        - tp;
}

template<typename T>
int treap_max_depth(typename treap<T>::node *cur) {
    if (cur == nullptr)
        return 0;
    int ans = 0;
    if (cur->left != nullptr)
        ans = treap_max_depth<T>(cur->left);
    if (cur->right != nullptr)
        ans = std::max(ans, treap_max_depth<T>(cur->right));
    return ans+1;
}

std::string pretty(int n) {
    std::string s = std::to_string(n);
    if (s.size() > 3)
        s.insert(s.size()-3, 1, ' ');
    if (s.size() > 7)
        s.insert(s.size()-7, 1, ' ');
    if (s.size() > 11)
        s.insert(s.size()-11, 1, ' ');
    return s;
}

int rnd(int n) {
    return (std::rand()+std::rand()*(RAND_MAX+1ll)) % n;
}

const int N = 100'000;
int *A = nullptr;

list<int> lst;
stack<int> stk;
queue<int> que;
sorted_array<int> arr;
treap<int> trp;
dyn_array<int> vec;
heap<int> hp;

long long int tp;

int main() {
    int __a = time_ns() % (1<<30); std::srand(__a);

    std::cout << "\nAllocating memory for A[" << pretty(N) << "]\n  time: ";
    tp = time_ns();
    A = new int[N];
    std::cout << time_ns(tp) / 1e9 << "\n";

    std::cout << "Filling array A with random numbers\n  time: ";
    tp = time_ns();
    for (int i = 0; i < N; ++i)
        A[i] = rnd(N);
    std::cout << time_ns(tp) / 1e9 << "\n";

    // treap =======================================
    std::cout << "\n\nInserting numbers from A to treap\n  time: ";
    tp = time_ns();
    for (int i = 0; i < N; ++i)
        trp.insert(A[i]);
    std::cout << time_ns(tp) / 1e9 << "\n";

    std::cout << "Counting max depth of treap = ";
    tp = time_ns();
    int max_depth = treap_max_depth<int>(trp.root);
    tp = time_ns() - tp;
    std::cout << max_depth << "\n  time: " << tp/1e9 << "\n";

    int num = N;
    std::cout << "Checking if " << pretty(num)
              << " random numbers are in treap\n";
    int cnt = 0;
    tp = time_ns();
    for (int i = 0; i < num; ++i)
        cnt += trp.contains(rnd(N));
    std::cout << "  time: " << time_ns(tp) / 1e9
              << "\n  proportion of numbers in treap: " << cnt / 1. / num
              << "\n    // it is approximately 1-1/e, e is Euler's number!\n";

    num = N/2;
    std::cout << "Deleting " << pretty(num) << " numbers in cycle\n";
    tp = time_ns();
    for (int i = 0; i < num; ++i)
        trp.remove(A[rnd(N-1)]);
    std::cout << "  time: " << time_ns(tp) / 1e9 << "\n";

    std::cout << "Deleting " << pretty(N - num)
              << " numbers by recursion\n";
    tp = time_ns();
    trp.~treap(); trp.root = nullptr;
    std::cout << "  time: " << time_ns(tp) / 1e9 << "\n";
    //std::cout << "  root: " << trp.root << "\n";
    // treap =======================================

    // list ========================================
    std::cout << "\n\nInserting numbers from A to linked list\n  time: ";
    tp = time_ns();
    for (int i = 0; i < N; ++i)
        lst.insert(lst.end(), A[i]);
    std::cout << time_ns(tp) / 1e9 << "\n";

    std::cout << "Iterating through list\n  time: ";
    tp = time_ns();
    list<int>::iterator it = lst.begin(), it_one_third, it_two_thirds;
    for (int i = 0; i < N/3; ++i, ++it);
    it_one_third = it;
    for (int i = N/3; i < 2*N/3; ++i, ++it);
    it_two_thirds = it;
    for (int i = 2*N/3; i < N; ++i);
    std::cout << time_ns(tp) / 1e9 << "\n";

    std::cout << "Deleting sublist from 1/3 to 2/3 of list\n  time: ";
    tp = time_ns();
    lst.remove(it_one_third, it_two_thirds);
    std::cout << time_ns(tp) / 1e9 << "\n";
    // list ========================================

    // stack =======================================
    std::cout << "\n\nPushing numbers from A to stack\n  time: ";
    tp = time_ns();
    for (int i = 0; i < N; ++i)
        stk.push(A[i]);
    std::cout << time_ns(tp) / 1e9 << "\n";

    std::cout << "Popping from stack\n  time: ";
    tp = time_ns();
    for (int i = 0; i < N; ++i)
        stk.pop();
    std::cout << time_ns(tp) / 1e9 << "\n";
    // stack =======================================

    // dyn_array ===================================
    std::cout << "\n\nInserting numbers from A to dynamic array\n  time: ";
    tp = time_ns();
    for (int i = 0; i < N; ++i)
        vec.insert(A[i]);
    std::cout << time_ns(tp) / 1e9 << "\n";

    std::cout << "Iterating dynamic array\n  time: ";
    tp = time_ns();
    for (int i = 0; i < N; ++i)
        if (A[i] != vec[i])
            return 32;
    std::cout << time_ns(tp) / 1e9 << "\n";
    // dyn_array ===================================

    std::cout << "\n\nDeleting A\n  time: ";
    tp = time_ns();
    delete A;
    std::cout << time_ns(tp) / 1e9 << "\n";

    //

    return 0;
}
