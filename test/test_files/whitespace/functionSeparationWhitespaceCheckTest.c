// Some correct spacing for this one
void blah(void) {
    return;
}

// A comment for luck
void blah2(void) {
    return;
}

enum Fruit {
    APPLE, PEAR
};


struct Blah {
    int x;
    int y;
};


typedef enum Fruit Fruit;


typedef int MyInt;
typedef struct Blah Blah;
struct Fred {
    int a;
};

void blah3(void) {
    // Bad spacing - no comments
    return;
}


// A comment here as well
void blah4(void) {
    return;
}

/*
 Some code that has been commented out
 for no reason at all
*/

// How about some more commented code...

// Main is randomly commented
int main(int argc, char** argv) {
    return 0;    
}