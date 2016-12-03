#include <iostream>
#include <vector>
#include <algorithm>


typedef std::vector<int>::iterator Iter;


std::vector<int> merge (Iter databegin, Iter dataend) {
std::vector<int> merged1, merged2, result;
if (dataend - databegin == 0) {
    result.push_back(*dataend);
    return result;
}
merged1=merge(databegin, databegin + (dataend - databegin) / 2);
merged2=merge(databegin + (dataend - databegin) / 2 + 1, dataend);
Iter temp1 = merged1.begin();
Iter temp2 = merged2.begin();
Iter end1  = merged1.end();
Iter end2  = merged2.end();
while ((temp1 != end1) || (temp2 != end2)) {
if (temp1 == end1) {
result.push_back(*(temp2++));
} else if ((temp2 == end2) || (*temp1 < *temp2)) {
result.push_back(*(temp1++));
} else {
result.push_back(*(temp2++));
}
}
return result;
}


int main() {
int n;
std::cin >> n;
std::vector<int> data(n),vect;
for(int i=0 ; i<n ; ++i) {
    std::cin >> data[i];
}
vect=merge(data.begin(),data.end());

for(auto i=vect.begin();i!=vect.end();++i) {
    std::cout<<*i<<" ";
}

}
