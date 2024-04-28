#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>

typedef __int128 really_long_t;

struct a_b_diff_t
{
    really_long_t x0, x1;
};

std::string long2str(really_long_t x)
{
    if (x==0)
        return "0";
    else
    {
        std::string res = "";
        while (x != 0)
        {
            int digit = (int) (x % 10);
            char chars[2] = { char('0' + digit), '\0' };
            res = (std::string) chars + res;
            x /= 10;
        }
        return res;
    }
}

struct alice_bob_t
{
    really_long_t awins, bwins;
};

alice_bob_t count(unsigned turns)
{
    std::vector<a_b_diff_t> z, y;
    z.resize(4*turns);
    y.resize(4*turns);

    a_b_diff_t *in = & z[2*turns], *out = & y[2*turns];
    in->x0 = in->x1 = 1;

    for (unsigned t=2; t<=turns; ++t)
    {
        // Clean out[±t]
        memset(out-t, 0, sizeof(*out) * (2*t+1));

        for (signed i = - (signed) (t-2); i <= (signed) (t-2); ++i)
        {
            out[i+1].x1 += in[i].x1;
            out[i-1].x0 += in[i].x1;
            out[i].x1 += in[i].x0;
            out[i].x0 += in[i].x0;
        }
        a_b_diff_t *tmp = in;
        in = out, out = tmp;
    }

    alice_bob_t res = { .awins = 0, .bwins = 0 };

    for (signed i = - (signed) (turns-1); i <= (signed) (turns-1); ++i)
    {
        if (i<0)
            res.bwins += in[i].x1 + in[i].x0;
        else if (i>0)
            res.awins += in[i].x1 + in[i].x0;
    }

    return res;
}

alice_bob_t avva_count(unsigned turns)
{
    uint64_t maxn = ((uint64_t) 1 << turns);
    alice_bob_t res = { .awins = 0, .bwins = 0 };
    for (uint64_t i=0; i < maxn; ++i)
    {
      uint64_t ascore = __builtin_popcount(i&(i>>1));
      uint64_t bscore = __builtin_popcount(i&((~i & (maxn-1))>>1));
      res.awins += (ascore > bscore);
      res.bwins += (ascore < bscore);
    }
    return res;
}

int main()
{
#ifndef ONLY_100
    for (unsigned turns=1; turns<=25; ++turns)
    {
        alice_bob_t wins = avva_count(turns);
        alice_bob_t my_wins = count(turns);
        if (wins.awins != my_wins.awins or wins.bwins != my_wins.bwins)
        {
            printf("turns=%u, awins=%s, bwins=%s\n", turns, long2str(wins.awins).c_str(), long2str(wins.bwins).c_str());
            printf("_____=%u, awins=%s, bwins=%s\n", turns, long2str(my_wins.awins).c_str(), long2str(my_wins.bwins).c_str());
            exit(1);
        }
    }
#endif // testing: avva's count gives the same result as mine

    unsigned start = 1;

#ifdef ONLY_100
    start = 100;
#endif

    for (unsigned turns=start; turns<=100; ++turns)
    {
        alice_bob_t w = count(turns);
        printf("turns=%u, awins=%s, bwins=%s\n", turns, long2str(w.awins).c_str(), long2str(w.bwins).c_str());
    }

}


