signal signal_0;
signal signal_x;
signal signal_y;
signal signal_x_y;
 
module module1()
{
    int x = 1;
    int y = 2;
    output(signal_x, 1);
    output(signal_y, 2);
}
 
module module2()
{
    int x;
    int y;
 
    input(signal_x, x);
    input(signal_y, y);
    output(signal_x_y, x+y);
}
 
module module0()
{
    module1();
    module2();
    int output_value;
    read(signal_x_y, output_value);
    output(signal_0, output_value);
}
 
module module_print()
{
    int read_value;
    input(signal_x_y, read_value)
    printf("value is read: %d\n", read_value);
}
 
int main(){
    module0();
    module_print();
}
