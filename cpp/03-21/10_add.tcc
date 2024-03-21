#pragma once

double add() {
    return 0.0;
}
template<typename T, typename ...Args>
double add(T t, Args ...args) {
    return t + add(args...);
}
