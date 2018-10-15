// C++ Code to demonstrate getppid()
#include <iostream>
#include <unistd.h>
using namespace std;
 
// Driver Code
int main()
{
    int pid;
    pid = fork();
    if (pid == 0)
    {
        cout << "\nParent Process id : "
             << getpid() << endl;
        cout << "\nChild Process with parent id : "
             << getppid() << endl;
    }
    return 0;
}
