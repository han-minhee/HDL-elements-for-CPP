signal signal_x;
signal signal_y;
module thread_module1()
{
    int x = 1;
    int y = 2;
 
    output(signal_x, 1);
    output(signal_y, 2);
}
 
module thread_module2()
{
    int x;
    int y;
 
    input(signal_x, x);
    input(signal_y, y);
    printf("%d\n", x+y);
}
 
int main(){
    module1;
    module2;
}
