//Original:/testcases/core/c_logi2op_bittgl/c_logi2op_bittgl.dsp
// Spec Reference: Logi2op functions: bittgl
# mach: bfin

.include "testutils.inc"
	start



imm32 r0, 0x00000000;
imm32 r1, 0x00000000;
imm32 r2, 0x00000000;
imm32 r3, 0x00000000;
imm32 r4, 0x00000000;
imm32 r5, 0x00000000;
imm32 r6, 0x00000000;
imm32 r7, 0x00000000;

// bit 0-7
BITTGL( R0 , 0 ); /* r0 = 0x00000001 */
BITTGL( R1 , 1 ); /* r1 = 0x00000002 */
BITTGL( R2 , 2 ); /* r2 = 0x00000004 */
BITTGL( R3 , 3 ); /* r3 = 0x00000008 */
BITTGL( R4 , 4 ); /* r4 = 0x00000010 */
BITTGL( R5 , 5 ); /* r5 = 0x00000020 */
BITTGL( R6 , 6 ); /* r6 = 0x00000040 */
BITTGL( R7 , 7 ); /* r7 = 0x00000080 */
CHECKREG r0, 0x00000001;
CHECKREG r1, 0x00000002;
CHECKREG r2, 0x00000004;
CHECKREG r3, 0x00000008;
CHECKREG r4, 0x00000010;
CHECKREG r5, 0x00000020;
CHECKREG r6, 0x00000040;
CHECKREG r7, 0x00000080;

// bit 8-15
BITTGL( R0 , 8 ); /* r0 = 0x00000100 */
BITTGL( R1 , 9 ); /* r1 = 0x00000200 */
BITTGL( R2 , 10 ); /* r2 = 0x00000400 */
BITTGL( R3 , 11 ); /* r3 = 0x00000800 */
BITTGL( R4 , 12 ); /* r4 = 0x00001000 */
BITTGL( R5 , 13 ); /* r5 = 0x00002000 */
BITTGL( R6 , 14 ); /* r6 = 0x00004000 */
BITTGL( R7 , 15 ); /* r7 = 0x00008000 */
CHECKREG r0, 0x00000101;
CHECKREG r1, 0x00000202;
CHECKREG r2, 0x00000404;
CHECKREG r3, 0x00000808;
CHECKREG r4, 0x00001010;
CHECKREG r5, 0x00002020;
CHECKREG r6, 0x00004040;
CHECKREG r7, 0x00008080;

// bit 16-23
BITTGL( R0 , 16 ); /* r0 = 0x00000100 */
BITTGL( R1 , 17 ); /* r1 = 0x00000200 */
BITTGL( R2 , 18 ); /* r2 = 0x00000400 */
BITTGL( R3 , 19 ); /* r3 = 0x00000800 */
BITTGL( R4 , 20 ); /* r4 = 0x00001000 */
BITTGL( R5 , 21 ); /* r5 = 0x00002000 */
BITTGL( R6 , 22 ); /* r6 = 0x00004000 */
BITTGL( R7 , 23 ); /* r7 = 0x00008000 */
CHECKREG r0, 0x00010101;
CHECKREG r1, 0x00020202;
CHECKREG r2, 0x00040404;
CHECKREG r3, 0x00080808;
CHECKREG r4, 0x00101010;
CHECKREG r5, 0x00202020;
CHECKREG r6, 0x00404040;
CHECKREG r7, 0x00808080;

// bit 24-31
BITTGL( R0 , 24 ); /* r0 = 0x00000100 */
BITTGL( R1 , 25 ); /* r1 = 0x00000200 */
BITTGL( R2 , 26 ); /* r2 = 0x00000400 */
BITTGL( R3 , 27 ); /* r3 = 0x00000800 */
BITTGL( R4 , 28 ); /* r4 = 0x00001000 */
BITTGL( R5 , 29 ); /* r5 = 0x00002000 */
BITTGL( R6 , 30 ); /* r6 = 0x00004000 */
BITTGL( R7 , 31 ); /* r7 = 0x00008000 */
CHECKREG r0, 0x01010101;
CHECKREG r1, 0x02020202;
CHECKREG r2, 0x04040404;
CHECKREG r3, 0x08080808;
CHECKREG r4, 0x10101010;
CHECKREG r5, 0x20202020;
CHECKREG r6, 0x40404040;
CHECKREG r7, 0x80808080;

// bit 0-7
BITTGL( R0 , 0 ); /* r0 = 0x00000001 */
BITTGL( R1 , 1 ); /* r1 = 0x00000002 */
BITTGL( R2 , 2 ); /* r2 = 0x00000004 */
BITTGL( R3 , 3 ); /* r3 = 0x00000008 */
BITTGL( R4 , 4 ); /* r4 = 0x00000010 */
BITTGL( R5 , 5 ); /* r5 = 0x00000020 */
BITTGL( R6 , 6 ); /* r6 = 0x00000040 */
BITTGL( R7 , 7 ); /* r7 = 0x00000080 */
CHECKREG r0, 0x01010100;
CHECKREG r1, 0x02020200;
CHECKREG r2, 0x04040400;
CHECKREG r3, 0x08080800;
CHECKREG r4, 0x10101000;
CHECKREG r5, 0x20202000;
CHECKREG r6, 0x40404000;
CHECKREG r7, 0x80808000;

// bit 8-15
BITTGL( R0 , 8 ); /* r0 = 0x00000100 */
BITTGL( R1 , 9 ); /* r1 = 0x00000200 */
BITTGL( R2 , 10 ); /* r2 = 0x00000400 */
BITTGL( R3 , 11 ); /* r3 = 0x00000800 */
BITTGL( R4 , 12 ); /* r4 = 0x00001000 */
BITTGL( R5 , 13 ); /* r5 = 0x00002000 */
BITTGL( R6 , 14 ); /* r6 = 0x00004000 */
BITTGL( R7 , 15 ); /* r7 = 0x00008000 */
CHECKREG r0, 0x01010000;
CHECKREG r1, 0x02020000;
CHECKREG r2, 0x04040000;
CHECKREG r3, 0x08080000;
CHECKREG r4, 0x10100000;
CHECKREG r5, 0x20200000;
CHECKREG r6, 0x40400000;
CHECKREG r7, 0x80800000;

// bit 16-23
BITTGL( R0 , 16 ); /* r0 = 0x00000100 */
BITTGL( R1 , 17 ); /* r1 = 0x00000200 */
BITTGL( R2 , 18 ); /* r2 = 0x00000400 */
BITTGL( R3 , 19 ); /* r3 = 0x00000800 */
BITTGL( R4 , 20 ); /* r4 = 0x00001000 */
BITTGL( R5 , 21 ); /* r5 = 0x00002000 */
BITTGL( R6 , 22 ); /* r6 = 0x00004000 */
BITTGL( R7 , 23 ); /* r7 = 0x00008000 */
CHECKREG r0, 0x01000000;
CHECKREG r1, 0x02000000;
CHECKREG r2, 0x04000000;
CHECKREG r3, 0x08000000;
CHECKREG r4, 0x10000000;
CHECKREG r5, 0x20000000;
CHECKREG r6, 0x40000000;
CHECKREG r7, 0x80000000;

// bit 24-31
BITTGL( R0 , 24 ); /* r0 = 0x00000100 */
BITTGL( R1 , 25 ); /* r1 = 0x00000200 */
BITTGL( R2 , 26 ); /* r2 = 0x00000400 */
BITTGL( R3 , 27 ); /* r3 = 0x00000800 */
BITTGL( R4 , 28 ); /* r4 = 0x00001000 */
BITTGL( R5 , 29 ); /* r5 = 0x00002000 */
BITTGL( R6 , 30 ); /* r6 = 0x00004000 */
BITTGL( R7 , 31 ); /* r7 = 0x00008000 */
CHECKREG r0, 0x00000000;
CHECKREG r1, 0x00000000;
CHECKREG r2, 0x00000000;
CHECKREG r3, 0x00000000;
CHECKREG r4, 0x00000000;
CHECKREG r5, 0x00000000;
CHECKREG r6, 0x00000000;
CHECKREG r7, 0x00000000;



pass