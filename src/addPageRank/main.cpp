#include "../utils/Aggregate.h"
#include <cstdio>
using namespace std;
int main(int argc, char const *argv[]){
    Graph g = readAggregate();
    printf("Eigen: %.5f", g.eigenvalue());
    return 0;
}
