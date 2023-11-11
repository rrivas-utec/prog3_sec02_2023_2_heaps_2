//
// Created by rrivas on 10/11/2023.
//

#ifndef PROG3_SEC02_2023_2_HEAPS_HEAP_H
#define PROG3_SEC02_2023_2_HEAPS_HEAP_H

#include <vector>
using namespace std;

namespace utec {
    template <
            typename T,
            template<typename ...> class Container = vector
            >
    class heap {
        Container<T> cnt;
        static size_t get_left(size_t parent_index) { return parent_index * 2; }
        static size_t get_right(size_t parent_index) { return parent_index * 2 + 1; }
        static size_t get_parent(size_t child_index) { return child_index / 2; }
        bool is_root(size_t index) { return index == 1; }
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
                return cnt[left_index] > cnt[right_index]? left_index: right_index;
            }
            return left_index;
        }

        void percolate_up(size_t index) {
            // CONDICIONES BASE
            if (is_root(index)) return;
            auto parent_index = get_parent(index);
            if (cnt[index] < cnt[parent_index]) return;

            // CONDICIONES RECURSIVAS
            swap(cnt[index], cnt[parent_index]);
            percolate_up(parent_index);
        }

        void percolate_down(size_t index) {
            // CONDICIONES BASE
            if (!has_children(index)) return;
            auto select_child = get_selected_index(index);
            if (cnt[index] > cnt[select_child]) return;
            // CONDICIONES RECURSIVAS
            swap(cnt[index], cnt[select_child]);
            percolate_down(select_child);
        }

    public:
        heap(): cnt(1) {}
        T top() { return cnt[1]; }
        size_t size() { return cnt.size() - 1; }

        void push(T value) {
            cnt.push(value);
            percolate_up(size());
        }
        void pop() {
            swap(cnt[1], cnt.back());
            cnt.pop_back();
            percolate_down(1);
        }

    };

}

#endif //PROG3_SEC02_2023_2_HEAPS_HEAP_H
