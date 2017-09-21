#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

void prompt(){
  cout << "mini-shell$ " << flush;
}

bool read_command(){
  string line;
  char* args[2];

  cin >> line;

  if (line == "quit" || line == "exit"){
    return false;
  }
  args[0] = (char*)line.c_str();
  args[1] = NULL;

  pid_t PID;

  PID = fork();
  if (PID == 0){
    if(execvp(args[0], args) == -1){
      cout << "command error" << endl;
    }
  }
  if (PID > 0){
    if(wait(0) == -1){
      cout << "command error" << endl;
    }
  }
  return true;
}

int main(){

  while( true ){
    prompt();
    if(!read_command()) return 0;
  }
  return 0;
}
