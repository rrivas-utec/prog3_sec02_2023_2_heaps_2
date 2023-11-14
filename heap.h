//
// Created by rrivas on 10/11/2023.
//

#ifndef PROG3_SEC02_2023_2_HEAPS_HEAP_H
#define PROG3_SEC02_2023_2_HEAPS_HEAP_H

#include <vector>
#include <functional>
using namespace std;

namespace utec {
    template <
            typename T,
            template<typename ...> class Container = std::vector,
            typename Comparable = std::less<T>
            >
    class heap {
        Container<T> cnt;
        Comparable cmp {};
        static size_t get_left(size_t parent_index) { return parent_index * 2; }
        static size_t get_right(size_t parent_index) { return parent_index * 2 + 1; }
        static size_t get_parent(size_t child_index) { return child_index / 2; }
        static bool is_root(size_t index) { return index == 1; }
        bool has_children(size_t parent_index) {
            return get_left(parent_index) < cnt.size();
        }
        bool has_right(size_t parent_index) {
            return get_right(parent_index) < cnt.size();
        }
        size_t get_selected_index(size_t parent_index) {
            auto left_index = get_left(parent_index);
            if (has_right(parent_index)) {
                auto right_index = get_right(parent_index);
                return cmp(cnt[right_index], cnt[left_index]) ? left_index: right_index;
            }
            return left_index;
        }

        void percolate_up(size_t index) {
            // CONDICIONES BASE
            if (is_root(index)) return;
            auto parent_index = get_parent(index);
            if (cmp(cnt[index], cnt[parent_index])) return;

            // CONDICIONES RECURSIVAS
            swap(cnt[index], cnt[parent_index]);
            percolate_up(parent_index);
        }

        void percolate_down(size_t index) {
            // CONDICIONES BASE
            if (!has_children(index)) return;
            auto select_child = get_selected_index(index);
            if (cmp(cnt[select_child],cnt[index])) return;
            // CONDICIONES RECURSIVAS
            swap(cnt[index], cnt[select_child]);
            percolate_down(select_child);
        }

        void heapify(size_t index) {
            auto cur_index = get_parent(index);
            while (cur_index > 0) {
                percolate_down(cur_index);
                --cur_index;
            }
        }
    public:
        heap(): cnt(1) {}
        T top() { return cnt[1]; }
//        explicit heap(Container<T> c): cnt(c.size()+1) {
//            copy(begin(c), end(c), next(begin(cnt)));
//            heapify(size());
//        }
        explicit heap(Container<T> c): cnt(1) {
            copy(begin(c), end(c), back_inserter(cnt));
            heapify(size());
        }
        heap(Container<T> c, Comparable cmp): cnt(1), cmp{cmp} {
            copy(begin(c), end(c), back_inserter(cnt));
            heapify(size());
        }
        size_t size() { return cnt.size() - 1; }

        void push(T value) {
            cnt.push_back(value);
            percolate_up(size());
        }
        void pop() {
            swap(cnt[1], cnt.back());
            cnt.pop_back();
            percolate_down(1);
        }
        bool replace(T old_value, T new_value) {
            auto it = find(begin(cnt)+1, end (cnt), old_value);
            if (it != end(cnt)) {
                *it = new_value;
                heapify(size());
                return true;
            }
            return false;
        }

        bool empty() { return size() == 0; }

    };

}

#endif //PROG3_SEC02_2023_2_HEAPS_HEAP_H
