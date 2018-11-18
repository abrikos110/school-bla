#include <iostream>
#include <chrono>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <climits>

#include "list.hpp"
#include "stack.hpp"
#include "queue.hpp"
#include "sorted_array.hpp"
#include "treap.hpp"
#include "dyn_array.hpp"
#include "heap.hpp"
#include "hash_string.hpp"

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

int rnd() {
    return (std::rand()+std::rand()*(RAND_MAX+1ll));
}

template<typename T>
void print_heap(heap<T> &hp) {
    int j = 1;
    for (int i = 0; i < hp.data.size; ++i) {
        if ((i+1) & j) {
            std::cout << "\n";
            j <<= 1;
        }
        std::cout << hp.data[i] << " ";
    }
}

const int N = 1'000'000;
int *A = nullptr;

list<int> lst;
stack<int> stk;
queue<int> que;
sorted_array<int> arr;
treap<int> trp;
dyn_array<int> vec;
heap<int> hp;
hash_string<> hs;

long long int tp;
int num, cnt, max_depth;

int main(int argc, char **args) {
    int __a = time_ns() % (1<<30); std::srand(__a);

    std::cout << "\nAllocating memory for A[" << pretty(N)
              << "]\n  time: ";
    tp = time_ns();
    A = new int[N];
    std::cout << time_ns(tp) / 1e9 << "\n";

    std::cout << "Filling array A with random numbers\n  time: ";
    tp = time_ns();
    for (int i = 0; i < N; ++i)
        A[i] = rnd()%N;
    std::cout << time_ns(tp) / 1e9 << "\n";

    // treap =======================================
    std::cout << "\n\nInserting numbers from A to treap\n  time: ";
    tp = time_ns();
    for (int i = 0; i < N; ++i)
        trp.insert(A[i]);
    std::cout << time_ns(tp) / 1e9 << "\n";

    std::cout << "Counting max depth of treap = ";
    tp = time_ns();
    max_depth = treap_max_depth<int>(trp.root);
    tp = time_ns() - tp;
    std::cout << max_depth << "\n  time: " << tp/1e9 << "\n";

    num = N;
    std::cout << "Checking if " << pretty(num)
              << " random numbers are in treap\n";
    cnt = 0;
    tp = time_ns();
    for (int i = 0; i < num; ++i)
        cnt += trp.contains(rnd()%N);
    std::cout << "  time: " << time_ns(tp) / 1e9
              << "\n  proportion of numbers in treap: "
              << cnt / 1. / num << "\n";

    num = N/2;
    std::cout << "Deleting " << pretty(num) << " numbers in cycle\n";
    tp = time_ns();
    for (int i = 0; i < num; ++i)
        trp.remove(A[rnd()%(N-1)]);
    std::cout << "  time: " << time_ns(tp) / 1e9 << "\n";

    std::cout << "Deleting " << pretty(N - num)
              << " numbers by recursion\n";
    tp = time_ns();
    trp.~treap(); trp.root = nullptr;
    std::cout << "  time: " << time_ns(tp) / 1e9 << "\n";
    //std::cout << "  root: " << trp.root << "\n";
    // treap =======================================

    // list ========================================
    std::cout
        << "\n\nInserting numbers from A to linked list\n  time: ";
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
    std::cout
        << "\n\nInserting numbers from A to dynamic array\n  time: ";
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

    // heap ========================================
    num = N/2;
    std::cout << "\n\nInserting " << pretty(num)
              << " numbers to heap by iterating\n  time: ";
    tp = time_ns();
    for (int i = 0; i < num; ++i)
        hp.insert(A[i]);
    std::cout << time_ns(tp) / 1e9 << "\n";

    std::cout << "Inserting " << pretty(N-num)
              << " numbers to heap with O(n) algorithm\n  time: ";
    tp = time_ns();
    hp.insert_from(A+num, A+N);
    std::cout << time_ns(tp) / 1e9 << "\n";

    /*for (int ii = 0; ii < 2; ++ii) {
        print_heap(hp);
        std::cout << "</LAYERS>\n";
        hp.pop_max();
    }*/

    std::cout << "Popping all numbers from heap\n  time: ";
    tp = time_ns();
    int last = INT_MAX;
    for (int i = 0; i < N; ++i) {
        int cur = hp.pop_max();
        if (cur > last)
            std::cerr << "_" << i << " " << cur << "\n";;
        last = cur;
    }
    std::cout << time_ns(tp) / 1e9 << "\n";
    // heap ========================================

    std::cout << "\n\nDeleting A\n  time: ";
    tp = time_ns();
    delete A;
    std::cout << time_ns(tp) / 1e9 << "\n";

    //

    return 0;
}

