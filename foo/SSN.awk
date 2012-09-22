#!/usr/bin/awk -f
BEGIN {
    code["A"] = 10; code["B"] = 11; code["C"] = 12; code["D"] = 13;
    code["E"] = 14; code["F"] = 15; code["G"] = 16; code["H"] = 17;
    code["I"] = 34; code["J"] = 18; code["K"] = 19; code["L"] = 20;
    code["M"] = 21; code["N"] = 22; code["O"] = 35; code["P"] = 23;
    code["Q"] = 24; code["R"] = 25; code["S"] = 26; code["T"] = 27;
    code["U"] = 28; code["V"] = 29; code["W"] = 32; code["X"] = 30;
    code["Y"] = 31; code["Z"] = 33;
}

{
    first = toupper(substr($1, 0, 1))
    sum = int(code[first] / 10) + code[first] % 10 * 9
    for (i = 2; i <= 10; i++)
        sum += substr($1, i, 1) * (10 - i)

    sum %= 10
    check = substr($1, 10, 1)
    
    if ((10 - sum) == check)
        print "yes"
    else
        print "no"
}
