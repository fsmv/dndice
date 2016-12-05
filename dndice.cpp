/**
 * Licensed under The MIT License:
 *
 * Copyright (c) 2016 Andrew Kallmeyer <fsmv@sapium.net>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <random>
#include <iostream>

#define isnum(c) ('0' <= (c) && (c) <= '9')

int ReadInt(char **str) {
    int result = 0;

    for (char *c = *str;
         isnum(*c) && *c;
         ++c, ++(*str))
    {
        int val = *c - '0';
        result *= 10;
        result += val;
    }

    return result;
}

int main(int argc, char *argv[]) {
{ // closes the whole function in a scope so g++ will stop complaining about my goto skipping over initilizations
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " NdK+B" << std::endl;
        return 1;
    }
    char **dndstring = argv + 1;

    int number_of_dice = 1;
    if (!(*dndstring && **dndstring == 'd')) {
        number_of_dice = ReadInt(dndstring);
        if (!number_of_dice) {
            goto fail;
        }

        if (!(*dndstring && **dndstring == 'd')) {
            goto fail;
        }
    }
    ++(*dndstring); // covers both checks for 'd'

    int faces_per_die = ReadInt(dndstring);
    if (!faces_per_die) {
        goto fail;
    }

    int bonus = 0;
    if (*dndstring && **dndstring == '+') {
        ++(*dndstring);
        bonus = ReadInt(dndstring);
    }

    std::random_device rd;
    std::mt19937 mt(rd()); // Mersenne Twister
    std::uniform_int_distribution<int> DieRoll(1, faces_per_die);

    int total = 0;
    for (int dieidx = 0; dieidx < number_of_dice; ++dieidx) {
        total += DieRoll(mt);
    }
    total += bonus;

    std::cout << total << std::endl;
}
    return 0;
fail:
    std::cerr << "Invalid dice string" << std::endl;
    return 1;
}
