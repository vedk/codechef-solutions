/*
BUGCAL.cpp - Solution to the Codechef problem https://www.codechef.com/problems/BUGCAL
Copyright (C) 2017 Ved Khandekar

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <iostream>
#include <vector>
using namespace std;

int get_last_digit(const int);

int main()
{
    /* List of variables used:
     * t: stores number of testcases
     * a: the first number, to be taken from the user
     * b: the second number, to be taken from the user
     * ld_a, ld_b: stores the last digit of a and b
     * sum: stores the sum of the individual digits
     */
    int t, a, b;
    int ld_a, ld_b;
    vector<int> sum;
    vector<int>::reverse_iterator ir;
    cin >> t;
    
    for (int i = 0; i < t; i++)
    {
        cin >> a >> b; // get the numbers
        /*
         * The while loop below is the crux of the program.
         * 
         * The logic is as follows:
            1. Get the last digit of a and b
            2. Add the last digits and store them in the vector sum. Note that
               we have stored the last digit of the sum. This is important as
               9 + 2 shall give 11, but we require only the units digit, i.e. 1
            3. Subtract the last digits from the respective numbers, this gives
               two numbers which are multiples of 10
               e.g. if a = 243 and b = 121, the last digits are 3 and 1 respec-
               -tively. After subtracting 3 and 1, we get 240 and 120.
            4. Divide the subtracted numbers by 10, this effectively removes
               the last digit of the original number
               e.g. 240/10 = 24, thus 3 of 243 has been removed to get 24
            5. Repeat the process until we get all the digits of a and b and
               add them.
         * We keep checking that a >= 1 because when all the digits have been
           extracted, a will be 0 (it won't be a fraction as it is an int)
           e.g. 24 - 3 = 20, 20 / 10 = 2, 2 / 10 = 0.2 <= 1, thus terminate
        */
        while (a >= 1)
        {
            ld_a = get_last_digit(a); // get the last digit
            ld_b = get_last_digit(b);
            sum.push_back(get_last_digit(ld_a + ld_b)); // store the sum in the vector
            a -= ld_a; b -= ld_b; // subtract last digit
            a /= 10; b /= 10; // divide by 10
            /* NOTE: a -= ld_a is the shorthand of writing a = a - ld_a
             * Similarly b /= 10 is nothing but b = b / 10
             */
        }
        
        /* The sum vector stores the addition in reverse order of printing.
         * So access the vector from the end...
         */
        for (ir = sum.rbegin(); ir != sum.rend(); ir++)
            cout << *ir; // print each digit without space to give a number
        
        sum.clear(); // clear the contents of the vector for the next iteration
        cout << endl; // Output '\n' so that the next result is printed on the next line
    }
    return 0;
}

/*
 * get_last_digit(int) is a function which returns the last digit of the given
 * integer.
 * 
 * It works in the following way:
    1. Check if the given number (n) is a multiple of 10, if it is return 0
    2. Starting from 1, subtract each number from n to check if the difference
       is a multiple of 10. If it is, that number is the last digit.
    3. Repeat this until the last digit is found.
    e.g. 24 - 1 = 23, not multiple of 10
         24 - 2 = 22, not multiple of 10
         24 - 3 = 21, not multiple of 10
         24 - 4 = 20, a multiple of 10, hence 4 must be the last digit!
 */
int get_last_digit(const int n)
{
    if ((n % 10) == 0)
        return 0;
    
    for (int i = 1; i <= 9; i++)
    {
        // The % operator returns the remainder after dividing two numbers
        if ((n - i) % 10 == 0)
            return i;
    }
}