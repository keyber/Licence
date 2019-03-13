int main(void) {
    int a, b;
    a = 24;
    b = 16;
    while (a != b) {
        if (a > b) {
            a = a - b;
        }
        else {
            b = b - a;
        }
    }
    return 0;
}
