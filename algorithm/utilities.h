//
// Created by lukas on 20/10/2022.
//

#ifndef KERNALS_UTILITIES_H
#define KERNALS_UTILITIES_H

#include <vector>
#include <algorithm>

bool contains(const std::vector<int>& data, int element) {
    return std::find(data.begin(), data.end(), element) != data.end();
}

#endif //KERNALS_UTILITIES_H
