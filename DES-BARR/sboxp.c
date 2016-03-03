#include "desdefs.h"

/*
 * Optimization 13: sBoxes  with pTr and emod built-in
 */
u32 sBoxp[8][64] = {
   {
      0x00808200, 0x00000000, 0x00008000, 0x00808202, 
      0x00808002, 0x00008202, 0x00000002, 0x00008000, 
      0x00000200, 0x00808200, 0x00808202, 0x00000200, 
      0x00800202, 0x00808002, 0x00800000, 0x00000002, 
      0x00000202, 0x00800200, 0x00800200, 0x00008200, 
      0x00008200, 0x00808000, 0x00808000, 0x00800202, 
      0x00008002, 0x00800002, 0x00800002, 0x00008002, 
      0x00000000, 0x00000202, 0x00008202, 0x00800000, 
      0x00008000, 0x00808202, 0x00000002, 0x00808000, 
      0x00808200, 0x00800000, 0x00800000, 0x00000200, 
      0x00808002, 0x00008000, 0x00008200, 0x00800002, 
      0x00000200, 0x00000002, 0x00800202, 0x00008202, 
      0x00808202, 0x00008002, 0x00808000, 0x00800202, 
      0x00800002, 0x00000202, 0x00008202, 0x00808200, 
      0x00000202, 0x00800200, 0x00800200, 0x00000000, 
      0x00008002, 0x00008200, 0x00000000, 0x00808002, 
   }, {
      0x40084010, 0x40004000, 0x00004000, 0x00084010, 
      0x00080000, 0x00000010, 0x40080010, 0x40004010, 
      0x40000010, 0x40084010, 0x40084000, 0x40000000, 
      0x40004000, 0x00080000, 0x00000010, 0x40080010, 
      0x00084000, 0x00080010, 0x40004010, 0x00000000, 
      0x40000000, 0x00004000, 0x00084010, 0x40080000, 
      0x00080010, 0x40000010, 0x00000000, 0x00084000, 
      0x00004010, 0x40084000, 0x40080000, 0x00004010, 
      0x00000000, 0x00084010, 0x40080010, 0x00080000, 
      0x40004010, 0x40080000, 0x40084000, 0x00004000, 
      0x40080000, 0x40004000, 0x00000010, 0x40084010, 
      0x00084010, 0x00000010, 0x00004000, 0x40000000, 
      0x00004010, 0x40084000, 0x00080000, 0x40000010, 
      0x00080010, 0x40004010, 0x40000010, 0x00080010, 
      0x00084000, 0x00000000, 0x40004000, 0x00004010, 
      0x40000000, 0x40080010, 0x40084010, 0x00084000, 
   }, {
      0x00000104, 0x04010100, 0x00000000, 0x04010004, 
      0x04000100, 0x00000000, 0x00010104, 0x04000100, 
      0x00010004, 0x04000004, 0x04000004, 0x00010000, 
      0x04010104, 0x00010004, 0x04010000, 0x00000104, 
      0x04000000, 0x00000004, 0x04010100, 0x00000100, 
      0x00010100, 0x04010000, 0x04010004, 0x00010104, 
      0x04000104, 0x00010100, 0x00010000, 0x04000104, 
      0x00000004, 0x04010104, 0x00000100, 0x04000000, 
      0x04010100, 0x04000000, 0x00010004, 0x00000104, 
      0x00010000, 0x04010100, 0x04000100, 0x00000000, 
      0x00000100, 0x00010004, 0x04010104, 0x04000100, 
      0x04000004, 0x00000100, 0x00000000, 0x04010004, 
      0x04000104, 0x00010000, 0x04000000, 0x04010104, 
      0x00000004, 0x00010104, 0x00010100, 0x04000004, 
      0x04010000, 0x04000104, 0x00000104, 0x04010000, 
      0x00010104, 0x00000004, 0x04010004, 0x00010100, 
   }, {
      0x80401000, 0x80001040, 0x80001040, 0x00000040, 
      0x00401040, 0x80400040, 0x80400000, 0x80001000, 
      0x00000000, 0x00401000, 0x00401000, 0x80401040, 
      0x80000040, 0x00000000, 0x00400040, 0x80400000, 
      0x80000000, 0x00001000, 0x00400000, 0x80401000, 
      0x00000040, 0x00400000, 0x80001000, 0x00001040, 
      0x80400040, 0x80000000, 0x00001040, 0x00400040, 
      0x00001000, 0x00401040, 0x80401040, 0x80000040, 
      0x00400040, 0x80400000, 0x00401000, 0x80401040, 
      0x80000040, 0x00000000, 0x00000000, 0x00401000, 
      0x00001040, 0x00400040, 0x80400040, 0x80000000, 
      0x80401000, 0x80001040, 0x80001040, 0x00000040, 
      0x80401040, 0x80000040, 0x80000000, 0x00001000, 
      0x80400000, 0x80001000, 0x00401040, 0x80400040, 
      0x80001000, 0x00001040, 0x00400000, 0x80401000, 
      0x00000040, 0x00400000, 0x00001000, 0x00401040, 
   }, {
      0x00000080, 0x01040080, 0x01040000, 0x21000080, 
      0x00040000, 0x00000080, 0x20000000, 0x01040000, 
      0x20040080, 0x00040000, 0x01000080, 0x20040080, 
      0x21000080, 0x21040000, 0x00040080, 0x20000000, 
      0x01000000, 0x20040000, 0x20040000, 0x00000000, 
      0x20000080, 0x21040080, 0x21040080, 0x01000080, 
      0x21040000, 0x20000080, 0x00000000, 0x21000000, 
      0x01040080, 0x01000000, 0x21000000, 0x00040080, 
      0x00040000, 0x21000080, 0x00000080, 0x01000000, 
      0x20000000, 0x01040000, 0x21000080, 0x20040080, 
      0x01000080, 0x20000000, 0x21040000, 0x01040080, 
      0x20040080, 0x00000080, 0x01000000, 0x21040000, 
      0x21040080, 0x00040080, 0x21000000, 0x21040080, 
      0x01040000, 0x00000000, 0x20040000, 0x21000000, 
      0x00040080, 0x01000080, 0x20000080, 0x00040000, 
      0x00000000, 0x20040000, 0x01040080, 0x20000080, 
   }, {
      0x10000008, 0x10200000, 0x00002000, 0x10202008, 
      0x10200000, 0x00000008, 0x10202008, 0x00200000, 
      0x10002000, 0x00202008, 0x00200000, 0x10000008, 
      0x00200008, 0x10002000, 0x10000000, 0x00002008, 
      0x00000000, 0x00200008, 0x10002008, 0x00002000, 
      0x00202000, 0x10002008, 0x00000008, 0x10200008, 
      0x10200008, 0x00000000, 0x00202008, 0x10202000, 
      0x00002008, 0x00202000, 0x10202000, 0x10000000, 
      0x10002000, 0x00000008, 0x10200008, 0x00202000, 
      0x10202008, 0x00200000, 0x00002008, 0x10000008, 
      0x00200000, 0x10002000, 0x10000000, 0x00002008, 
      0x10000008, 0x10202008, 0x00202000, 0x10200000, 
      0x00202008, 0x10202000, 0x00000000, 0x10200008, 
      0x00000008, 0x00002000, 0x10200000, 0x00202008, 
      0x00002000, 0x00200008, 0x10002008, 0x00000000, 
      0x10202000, 0x10000000, 0x00200008, 0x10002008, 
   }, {
      0x00100000, 0x02100001, 0x02000401, 0x00000000, 
      0x00000400, 0x02000401, 0x00100401, 0x02100400, 
      0x02100401, 0x00100000, 0x00000000, 0x02000001, 
      0x00000001, 0x02000000, 0x02100001, 0x00000401, 
      0x02000400, 0x00100401, 0x00100001, 0x02000400, 
      0x02000001, 0x02100000, 0x02100400, 0x00100001, 
      0x02100000, 0x00000400, 0x00000401, 0x02100401, 
      0x00100400, 0x00000001, 0x02000000, 0x00100400, 
      0x02000000, 0x00100400, 0x00100000, 0x02000401, 
      0x02000401, 0x02100001, 0x02100001, 0x00000001, 
      0x00100001, 0x02000000, 0x02000400, 0x00100000, 
      0x02100400, 0x00000401, 0x00100401, 0x02100400, 
      0x00000401, 0x02000001, 0x02100401, 0x02100000, 
      0x00100400, 0x00000000, 0x00000001, 0x02100401, 
      0x00000000, 0x00100401, 0x02100000, 0x00000400, 
      0x02000001, 0x02000400, 0x00000400, 0x00100001, 
   }, {
      0x08000820, 0x00000800, 0x00020000, 0x08020820, 
      0x08000000, 0x08000820, 0x00000020, 0x08000000, 
      0x00020020, 0x08020000, 0x08020820, 0x00020800, 
      0x08020800, 0x00020820, 0x00000800, 0x00000020, 
      0x08020000, 0x08000020, 0x08000800, 0x00000820, 
      0x00020800, 0x00020020, 0x08020020, 0x08020800, 
      0x00000820, 0x00000000, 0x00000000, 0x08020020, 
      0x08000020, 0x08000800, 0x00020820, 0x00020000, 
      0x00020820, 0x00020000, 0x08020800, 0x00000800, 
      0x00000020, 0x08020020, 0x00000800, 0x00020820, 
      0x08000800, 0x00000020, 0x08000020, 0x08020000, 
      0x08020020, 0x08000000, 0x00020000, 0x08000820, 
      0x00000000, 0x08020820, 0x00020020, 0x08000020, 
      0x08020000, 0x08000800, 0x08000820, 0x00000000, 
      0x08020820, 0x00020800, 0x00020800, 0x00000820, 
      0x00000820, 0x00020020, 0x08000000, 0x08020800, 
   },
};
