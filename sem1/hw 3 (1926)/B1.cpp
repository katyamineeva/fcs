#include<iostream>
#include<vector>

template <typename SourceIterator, typename DestinationIterator, typename Predicate>
DestinationIterator copy_backward_if(SourceIterator source_first,
                                     SourceIterator source_last,
                                     DestinationIterator destination_last,
                                     Predicate condition) {
    for (; source_first != source_last; ++source_first) {
        if (condition(*source_first)) {
            --destination_last;
            *destination_last = *source_first;
        }
    }
    return destination_last;
}


template<typename intNum>
bool isOdd(intNum x) {
    return (x % 2) != 0;
}

using std::cout;
using std::vector;

int main() {
    vector<int> v_in = {1, 2, 3, 4};
    vector<int> v_out (4, 0);
    auto it_end = v_out.end();

    vector<int>::iterator it_begin = copy_backward_if(v_in.begin(), v_in.end(), it_end, isOdd<int>);

    return 0;
}
