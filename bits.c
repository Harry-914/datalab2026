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
    int ns = n << 3;
    int ms = m << 3;

    int nb = (x >> ns) & 0xFF; 
    int mb = (x >> ms) & 0xFF; 

    int mask = ~((0xFF << ns) | (0xFF << ms));

    return (x & mask) | (nb << ms) | (mb << ns);
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned result = 0;
    unsigned counter = 0xFFFFFFFF;
    while(counter){
        result = result << 1;
        result|=(v&0x1);
        v = v >> 1;
        counter = counter>>1;
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
    int fx = ~x; 
    int shift, result = 0;
    shift = !!(fx >> 16) << 4;
    fx = fx >> shift;
    result |= shift; 

    shift = !!(fx >> 8) << 3; 
    fx = fx >> shift; 
    result |= shift;

    shift = !!(fx >> 4) << 2; 
    fx = fx >> shift; 
    result |= shift;

    shift = !!(fx >> 2) << 1; 
    fx = fx >> shift; 
    result |= shift; 

    result |= !!(fx >> 1);

    return 32 + ~result + !~x;
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
    unsigned ux = x, sign, exp, frac;
    int pos = 0;

    // 0 -> 0.0
    if(!x) return 0;

    sign = ux & 0x80000000;
    if(sign) ux = ~ux + 1; // 负数取绝对值

    // 找到最高位1的位置
    while((ux >> pos) > 1) pos += 1;

    exp = pos + 127;

    if(pos <= 23) {
        // 有效数字不超过24位，不需要舍入
        frac = ux << (23 - pos);
    }
    else{
        // 有效数字超过24位，舍入
        int shift = pos - 23;
        unsigned half, lost;
        // 保留最高24位
        frac = ux >> shift;

        // 丢弃低shift位
        lost = ux&((1u<<shift)-1u);

        // 被丢弃部分恰好为一半时的值
        half = 1u<<(shift-1);

        // 舍入
        if(lost>half) frac+=1;
        else if (lost==half){
            if(frac&0x1) frac+=1;
        }

        // 如果舍入导致1.1111...->10.00... 
        exp = exp + (frac>>24);
    }

    return sign | (exp <<23) |(frac & 0x7FFFFF);
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

    unsigned sign = uf & 0x80000000;
    unsigned exp = uf & 0x7F800000;
    unsigned frac = uf & 0x007FFFFF;

    // NaN + 无穷，直接返回
    if(exp==0x7F800000){
        return uf;
    }

    // 非规格化
    if(exp==0x0){
        return sign | (frac << 1);
    }

    // 规格化
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
    
    // NaN + 无穷
    if(!(exp - 0x7FF)) return 0x80000000;

    // 指数小于0，返回0
    if(e < 0)  return 0;

    // 指数大于等于31，返回0x80000000
    if(e>=31) return 0x80000000;

    if(e <= 20) result = (1 << e) | (fracHigh >> (20-e)); // 整数部分在fracHigh
    else result = (1 << e) | (fracHigh << (e-20) | (fracLow >> (32+20-e))); 
    
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
    int exp;
    unsigned frac = 0;

    if(x <= -127){
        if(x<-149) return 0;
        frac = 0x1 << (149+x);
        return frac;
    }

    if(x > 127){
        return 0x7F800000;
    }

    exp=x+127;
    return ( exp<<23 );
}
