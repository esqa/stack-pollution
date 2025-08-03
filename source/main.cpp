#include <iostream>

__declspec(naked) int do_stuff(int a, int b, int c)
{
    __asm
    {
        push ebp;
        mov ebp, esp;

        add eax, [ebp + 8];
        add eax, [ebp + 12];
        add eax, [ebp + 16];

        mov esp, ebp;
        pop ebp;
        ret;
    }
}


// we'll be doing some stuff here using our broken stack offsets
__declspec(naked) int do_stuff_off(int a, int b, int c)
{
    __asm
    {
        push ebp;
        mov ebp, esp;

        xor eax, eax;

        add eax, [ebp + 20];
        add eax, [ebp + 24];
        add eax, [ebp + 28];

        mov esp, ebp;
        pop ebp;
        ret;
    }
}

int main()
{
    int retval{};

    __asm
    {
        push 10; // c
        push 10; // b
        push 10; // a

        call do_stuff;

        push 10; // c
        push 10; // b
        push 10; // a

        call do_stuff_off;
        mov retval, eax;
        add esp, 24;
    }

    printf("we're here! %i", retval);

    return 0;
}