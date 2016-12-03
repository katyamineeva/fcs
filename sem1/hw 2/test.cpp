#include <vector>
#include <iostream>

int main()
{
    std::vector<char> characters;

    characters.assign(5, 'a');

    for (int i = 0; i < characters.size(); ++i) {
        std::cout << characters[i] << '\n';
    }

    return 0;
}
