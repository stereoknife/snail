#include "glad/glad.h" // glad needs to be included first
#include "Root.h"

int main() {
    Root::init();
    Root::loop();
    Root::cleanup();
    return 0;
}
