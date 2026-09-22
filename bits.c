/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(x & y) & ~(~x & ~y);
}


/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if(!x) return !y;
    if(!y) return 0;
    return !((x>>31)^(y>>31));
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int result = 0, shift;

    shift = (v > 0xFFFF) << 4;
    v = v >> shift;
    result |= shift;


    shift = (v > 0xFF) << 3;
    v = v >> shift;
    result |= shift;
    
    shift = (v > 0xF) << 2;
    v = v >> shift;
    result |= shift;

    shift = (v > 0x3) << 1;
    v = v >> shift;
    result |= shift;

    result |= v > 0x1;

    return result;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int ns = n << 3; // 
    int ms = m << 3;

    int nb = (x >> ns) & 0xFF; //0x56
    int mb = (x >> ms) & 0xFF; //0x12

    int tmp = (nb <<ms)|(mb << ns); //0x56001200 x=0x12345678

    int nb2 = ~(0xFF << ns); //0xFFFF00FF 
    int mb2 = ~(0xFF << ms); //0x00FFFFFF
    int bit = nb2 & mb2; //0x00FF00FF

    return tmp|(x&bit);
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
 // 1010 0111 
unsigned reverse(unsigned v) {
    unsigned result = 0;
    unsigned sign = 0xFFFFFFFF;
    while(sign){
        result = result << 1;
        result|=(v&0x1);
        v = v >> 1;
        sign = sign>>1;
    }
    return result;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    // 0x87654321, 4 -> 0xF8765432
    int i = 0x80000000;
    int mask = (i >> n) << 1;
    return (~mask) & (x>>n);
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int fx = ~x; // 取反，问题等价于左边连续的0 x=0x7FFFFFFF -> 0x80000000
    int shift, result = 0;
    shift = !!(fx >> 16) << 4; // 10000
    fx = fx >> shift; // 0x00008000
    result |= shift; // 10000

    shift = !!(fx >> 8) << 3; // 1000
    fx = fx >> shift; // 0x00000080
    result |= shift; // 11000

    shift = !!(fx >> 4) << 2; // 100
    fx = fx >> shift; // 0x00000008
    result |= shift; // 11100

    shift = !!(fx >> 2) << 1; // 10
    fx = fx >> shift; // 0x00000002
    result |= shift; // 11110

    result |= !!(fx >> 1); // 11111

    return 32 + ((~result) & ((!!(~x) << 31) >> 31)); 
    // if (x == 0xFFFFFFFF) return 32    ~x=0
    // else return 32-result
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned ux = x, s, e, m, lost, half;
    int pos = 0;

    // 0 -> 0.0
    if(!x) return 0;

    s = ux & 0x80000000;
    if(s) ux = ~ux + 1; // 溢出！

    while((ux >> pos) > 1) pos += 1;

    e = pos + 127;

    if(pos < 24) m = ux << (23 - pos);
    else{
        // 有效数字超过24位，舍入 丢弃低位
        int r = pos - 23;
        m = ux >> r;

        lost = ux&((1u<<r)-1u);

        half = 1u<<(r-1);

        if(lost>half) m=m+1;
        else if (lost==half){
            if(m&0x1) m=m+1;
        }

        // 舍入1.1111... 
        e = e + (m>>24);
    }

    return s | (e <<23) |(m & 0x7FFFFF);
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    // uf = 0x7f800000  = 0|111 1111 1|000 0000 0000 0000 0000 0000
    // should get       = 0|111 
    // but get          = 

    unsigned sign = uf & 0x80000000;
    unsigned exp = uf & 0x7F800000;
    unsigned frac = uf & 0x007FFFFF;

    // NaN + 无穷
    if(exp==0x7F800000){
        return uf;
    }

    // 非规格化
    if(exp==0x0){
        return sign | (frac << 1);
    }

    exp = exp + 0x00800000;

    // 无穷
    if(exp==0x7F800000) frac = 0;

    return sign|exp|frac;

}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned sign = uf2 >> 31;
    unsigned exp = (uf2 >> 20) & 0x7FF;
    unsigned fracHigh = uf2 & 0xFFFFF;
    unsigned fracLow = uf1;
    unsigned result;
    int e = exp - 1023;
    
    if(!(exp - 0x7FF)) return 0x80000000;

    if(e < 0)  return 0;

    if(e>=31) return 0x80000000;

    if(e <= 20) result = (1 << e) | (fracHigh >> (20-e));
    else result = (1 << e) | (fracHigh << (e-20) | (fracLow >> (52-e))); // 52=20+32
    
    if(sign) return -result;
    else return result;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    // x = 0x7fffffff = 0111 1111 1111 1111 1111 1111 1111 1111
    // should get     = 0111 1111 1000 0000 0000 0000 0000 0000
    // but get        = 1000 0000 0000 0000 0000 0000 0000 0000
    int exp;
    unsigned frac = 0;

    if(x <= -127){
        if(x<-149) return 0;
        frac = 0x1 << (23-(1-(127+x)));
        return frac;
    }

    if(x >= 128){
        return 0x7F800000;
    }

    exp=x+127;
    return ( exp<<23 );
}
