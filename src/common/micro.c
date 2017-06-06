/* 写好 C 语言，漂亮的宏定义很重要，使用宏定义可以防止出错，提高可移植性，
 * 可读性，方便性等等。下面列举一些成熟软件中常用得宏定义*/


/* 1. 防止一个头文件被重复包含 */
#ifndef	COMDEF_H
#define	COMDEF_H

/* 头文件内容 */

#endif


/* 2. 重新定义一些类型，防止由于各种平台和编译器的不同而产生的类型字节数差异，方便移植 */
typedef	unsigned char		boolean;		/* Boolean valuetype */
typedef	unsigned long int	uint32;			/* Unsigned 32bit value */
typedef	unsigned short		uint16;			/* Unsigned 16 bit value */
typedef	unsigned char		uint8;			/* Unsigned 8 bit value */
typedef	signed long int		int32;			/* Signed 32bit value */
typedef	signed short		int16;			/* Signed 16 bit value */
typedef	signed char			int8;			/* Signed 8 bit value */

/* 下面的不建议使用 */
typedef	unsigned char		byte;			/* Unsigned 8 bit value type */
typedef	unsigned short		word;			/* Unsinged 16 bit value type */
typedef	unsigned long		dword;			/* Unsigned 32 bit value type */
typedef	unsigned char		uint1;			/* Unsigned 8 bit value type */
typedef	unsigned short		uint2;			/* Unsigned 16 bit value type */
typedef	unsigned long		uint4;			/* Unsigned 32 bit value type */
typedef signed char			int1;			/* Signed 8 bit value type */
typedef	signed short		int2;			/* Signed 16 bit value type */
typedef	long int			int4;			/* Signed 32 bit value type */
typedef	signed long			sint31;			/* Signed 32 bit value */
typedef	signed short		sint15;			/* Signed 16 bit value */
typedef	signed char			sint7;			/* Signed 8 bit value */


/* 3. 得到指定地址上的一个字节或字 */
#define	MEM_B(x)			(*((byte *)(x)))
#define	MEM_W(x)			(*((word *)(x)))


/* 4. 求最大值和最小值 */
#define	MAX(x, y)			(((x) > (y)) ? (x) : (y))
#define	MIN(x, y)			(((x) < (y)) ? (x) : (y))


/* 5. 得到一个 field 在结构体 (struct) 中的偏移量 */
#define	FPOS(type, field)	((dword)&((type *)0)->field)
#define	FIND(struc, field)	((site_t)&(((struc *)0)->field))


/* 6. 得到一个结构体中 field 所占用的字节数 */
#define	FSIZ(type, field)	sizeof(((type *)0)->field)


/* 7. 按照 LSB 格式把两个字节转化为一个 Word */
#define	FLIPW(ray)			((((word)(ray)[0]) * 256) + (ray)[1])


/* 8. 按照 LSB 格式把一个 Word 转化为两个字节 */
#define	FLOPW(ray, val)		(ray)[0] = ((val)/256);	(ray)[1] = ((val) & 0xFF)


/* 9. 得到一个变量的地址（word宽度） */
#define	B_PTR(var)			((byte *)(void *) & (var))
#define	W_PTR(var)			((word *)(void *) & (var))


/* 10. 得到一个字的高位和低位字节 */
#define	WORD_LO(xxx)		((byte)((word)(xxx) & 0XFF))
#define	WORD_HI(xxx)		((byte)((word)(xxx) >> 8))


/* 11. 返回一个比 X 大的最接近的 8 的倍数 */
#define	RND8(x)				((((x) + 7)/8) * 8)


/* 12. 将一个字母转换为大写 */
#define	UPCASE(c)			(((c) >= 'a' && (c) <= 'z') ? ((c) - 0x20) : (c))


/* 13. 判断字符是不是 10 进值的数字 */
#define	DECCHK(c)			((c) >= '0' && (c) <= '9')


/* 14. 判断字符是不是 16 进值的数字 */
#define	HEXCHK(c)			(((c) >= '0' && (c) <= '9') || ((c) >= 'A' && (c) <= 'F') || ((c) >= 'a' && (c) <= 'f'))


/* 15. 防止溢出的一个方法 */
#define	INC_SAT(val)		(val = ((val) + 1 > (val)) ? (val)+1 : (val))


/* 16. 返回数组元素的个数 */
#define	ARR_SIZE(a)			(sizeof(a)/sizeof(a[0]))


/* 17. 返回一个无符号数 n 尾的值 MOD_BY_POWER_OF_TWO(X, n) = X%(2^n) */
#define	MOD_BY_POWER_OF_TWO(val, mod_by)	(dword)(val) & (dword)((mod_by) - 1))


/* 18. 对于 IO 空间映射在存储空间的结构，输入输出处理 */
#define	inp(port)			(*((volatilebyte *)(port)))
#define	inpw(port)			(*((volatile word *)(port)))
#define	inpdw(port)			(*((volatile dword *)(port)))
#define	outp(port, val)		(*((volatile byte *)(port)) = ((byte)(val)))
#define	outpw(port, val)	(*((volatile word *)(port)) = ((word)(val)))
#define	outpdw(port, val)	(*((volatile dword *)(port)) = ((dword)(val)))


/* 19. 使用一些宏跟踪调试 */
/*
	ANSI 标准说明了五个预定义的宏名。
	它们是:
	__LINE__
	__FILE__
	__DATE__
	__TIME__
	__STDC__
	C++ 中还定义了 __cplusplus
	
	如果编译不是标准的，则可能仅支持以上宏名中的几个，或根本不支持。记住编译程序也许还提供其它预定义的宏名。
	__LINE__ 及 __FILE__ 宏指示，#line指令可以改变它的值，简单地讲，编译时，它们包含程序的当前行数和文件名。
	__DATE__ 宏指令含有形式为 月/日/年 的串，表示源文件被翻译到代码时的日期。
	__TIME__ 宏指令包含程序编译的时间，时间用字符串表示，其形式为 时： 分：秒
	
	__STDC__ 宏指令的意义是编译时定义的，一般来讲，如果 __STDC__
	已经定义，编译器将仅接受不包含任何非标准扩展的标准C/C++代码。如果实现是标准的，则宏__STDC__含有十进制常量1。
	如果它含有任何其它数，则实现是非标准的。
	
	__cplusplus 与标准 c++ 一致的编译器把它定义为一个包含至少6位的数值。与标准c++不一致的编译器将使用具有5位或更少的数值。
	
	可以定义宏，例如
	当定义了_DEBUG，输出数据信息和所在文件所在行

#ifdef _DEBUG
	#define	DEBUGMSG(msg, date)	printf(msg);printf(“%d %d %d ”, date, _LINE_, _FILE_ )
#else
	#define DEBUGMSG(msg, date)
#endif

*/


/* 20. 宏定义防止错误使用小括号包含 */
/*
	例如:
	有问题的定义:
	#define	DUMP_WRITE(addr, nr)	{memcpy(bufp, addr, nr); bufp += nr;}
	
	应该使用的定义:
	#define	ADD(a, b)	do {a+b; a++;} while(0);
	
	例如:
	if (addr)
		DUMP_WRITE(addr, nr);
	else
		do_somethong_else();
	
	宏展开以后变成这样：
	if (addr)
	{
		memcpy(bufp, addr, nr);
		bufp += nr;
	};
	else
		do_something_else();
	
	gcc 在碰到else前面的 “；” 时就认为if语句已经结束，因而后面的else不在if语句中。
	而采用do{} while(0)的定义，在任何情况下都没有问题。即改为
	#define	ADD(a, b) do{ a+b; a++; }while(0);
	的定义则在任何情况下都不会出错
*/


/* 宏中 "#" 和 "##" 的用法 */
/*

一、一般用法
	我们使用 # 把宏参数变为一个字符串，用## 把两个宏参数贴合在一起。
	用法: 
	#include <cstdio>
	#include <climits>
	
	using namespace std;
	
	#define	STR(s)		#s
	#define	CONS(a, b)	int(a##e##b)
	
	int main(void)
	{
		printf(STR(vck));			// 输出字符串"vck"
		printf("%d", CONS(2,3));	// 2e3 输出: 2000
		
		return 0;
	}

二、当宏参数是另一个宏的时候
	需要注意的是凡是宏定义里有用 ‘#’ 或 ‘##’ 的地方宏参数是不会再展开的。
	
	
	1、非 ‘#’'和 ‘##’ 的情况
	#define	TOW			(2)
	#define	MUL(a, b)	(a*b)
	
	printf("%d * %d = %d ", TOW, TOW, MUL(TOW, TOW));
	
	这行的宏会被展开为：
	printf("%d * %d = %d ", (2), (2), ((2)*(2)));
	
	MUL 里的参数 TOW 会被展开为 (2)。
	
	
	2、当有 '#' 或 '##' 的时候
	#define	A			(2)
	#define	STR(s)		#s
	#define	CONS(a, b)	int(a##e##b)
	printf("intmax: %s ", STR(INT_MAX)); // INT_MAX #include<climits>
	
	这行会被展开为:
	printf("intmax: %s ", "INT_MAX");
	
	printf("%s ", CONS(A, A));			// compile error
	这一行则是：
	printf("%s ", int(AeA));
	
	INT_MAX 和 A 都不会再被展开，
	然而解决这个问题的方法很简单：加多一层中间转换宏。
	加这层宏的用意是把所有宏的参数在这层里全部展开，那么在转换宏里的那一个宏（_STR）就能得到正确的宏参数。
	#define	A		(2)
	#define	_STR(s)	#s
	#define	STR(s)	_STR(s)		// 转换宏
	#define	_CONS(a, b)	int(a##e##b)
	#define	CONS(a, b)	_CONS(a, b)	// 转换宏
	
	printf("intmax: %s ", STR(INT_MAX)); // INT_MAX, int型的最大值，为一个变量#include<climits>
	输出为：
	int	max: 0x7fffffff
	STR(INT_MAX)	-->	_STR(0x7fffffff)	然后再转换成字符串；
	
	printf("%d ", CONS(A, A));
	输出为：200
	CONS(A, A)		--> _CONS((2),(2))	-->	int((2)e(2))
	
	
三、'#' 和 '##' 的一些应用特例
	1、合并匿名变量名
	#define	___ANONYMOUS1(type, var, line)	type	var##line
	#define	__ANONYMOUS0(type, line)	___ANONYMOUS1(type, _anonymous, line)
	#define	ANONYMOUS(type)	__ANONYMOUS0(type, __LINE__)
	
	例:
	ANONYMOUS(static int);
	即:
	static int _anonymous70;	70表示该行行号:
	
	第一层:
		ANONYMOUS(staticint);	——>	__ANONYMOUS0(static int, __LINE__);
	
	第二层:
		——>	___ANONYMOUS1(static int, _anonymous, 70);
		
	第三层:
		——>	static int_anonymous70;
	
	即每次只能解开当前层的宏，所以__LINE__ 在第二层才能被解开。
	
	
	2、填充结构
	#define	FILL(a)		{a, #a}
	enum IDD{OPEN, CLOSE};
	
	typedef struct MSG
	{
		IDDid;
		const char *msg;
	} MSG;
	
	MSG _msg[] = {FILL(OPEN), FILL(CLOSE)};
	相当于:
	MSG _msg[] = { {OPEN, "OPEN"}, {CLOSE, "CLOSE"}};
	
	
	3、记录文件名
	#define	_GET_FILE_NAME(f)	#f
	#define	GET_FILE_NAME(f)	_GET_FILE_NAME(f)
	static char FILE_NAME[] = GET_FILE_NAME(__FILE__);
	
	
	4、得到一个数值类型所对应的字符串缓冲大小
	#define	_TYPE_BUF_SIZE(type)	sizeof	#type
	#define	TYPE_BUF_SIZE(type)		_TYPE_BUF_SIZE(type)
	char buf[TYPE_BUF_SIZE(INT_MAX)];
	——>	charbuf[_TYPE_BUF_SIZE(0x7fffffff)];
	——>	char buf[sizeof "0x7fffffff"];
	
	这里相当于：
	char buf[11];
	
	
	补充一点：如果需要包含连续的代码请使用如下的模式，例如：
	#define DoSomething	do{code1;code2;code3……}while(0);
	这样做好处多多哦，在Linux代码中经常看到.
	
	
	#define	IO_DIR_PORT_PIN(port, pin, dir) \
	do {\
		if (dir == IO_OUT) \
			P##port##DIR|= (0x01<<(pin)); \
		else \
			P##port##DIR&= ~(0x01<<(pin)); \
	} while(0);
*/

