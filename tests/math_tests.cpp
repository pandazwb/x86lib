#include "catch.hpp"

#define private public
#define protected public
#include "x86lib.h"
#include "x86lib_internal.h"
#include "x86test.h"

using namespace x86Lib;
using namespace std;

TEST_CASE("Or", "[math ops]"){
    x86CPU cpu;
    REQUIRE(cpu.Or8(0x16, 0x89) == 0x9f);
    REQUIRE(cpu.freg.bits.pf == 1);
    REQUIRE(cpu.freg.bits.sf == 1);
    REQUIRE(cpu.freg.bits.zf == 0);

    REQUIRE(cpu.Or8(0x76, 0x09) == 0x7f);
    REQUIRE(cpu.freg.bits.pf == 0);
    REQUIRE(cpu.freg.bits.sf == 0);
    REQUIRE(cpu.freg.bits.zf == 0);

    REQUIRE(cpu.Or8(0x0, 0x0) == 0x0);
    REQUIRE(cpu.freg.bits.pf == 1);
    REQUIRE(cpu.freg.bits.sf == 0);
    REQUIRE(cpu.freg.bits.zf == 1);

    REQUIRE(cpu.Or16(0x1616, 0x8989) == 0x9f9f);
    REQUIRE(cpu.freg.bits.pf == 1);
    REQUIRE(cpu.freg.bits.sf == 1);
    REQUIRE(cpu.freg.bits.zf == 0);

    REQUIRE(cpu.Or16(0x7674, 0x0909) == 0x7f7d);
    REQUIRE(cpu.freg.bits.pf == 0);
    REQUIRE(cpu.freg.bits.sf == 0);
    REQUIRE(cpu.freg.bits.zf == 0);

    REQUIRE(cpu.Or16(0, 0) == 0x0);
    REQUIRE(cpu.freg.bits.pf == 1);
    REQUIRE(cpu.freg.bits.sf == 0);
    REQUIRE(cpu.freg.bits.zf == 1);

    REQUIRE(cpu.Or32(0x16161616, 0x89898989) == 0x9f9f9f9f);
    REQUIRE(cpu.freg.bits.pf == 1);
    REQUIRE(cpu.freg.bits.sf == 1);
    REQUIRE(cpu.freg.bits.zf == 0);

    REQUIRE(cpu.Or32(0x76747674, 0x09090909) == 0x7f7d7f7d);
    REQUIRE(cpu.freg.bits.pf == 1);
    REQUIRE(cpu.freg.bits.sf == 0);
    REQUIRE(cpu.freg.bits.zf == 0);

    REQUIRE(cpu.Or32(0, 0) == 0x0);
    REQUIRE(cpu.freg.bits.pf == 1);
    REQUIRE(cpu.freg.bits.sf == 0);
    REQUIRE(cpu.freg.bits.zf == 1);

}


//opcode tests.. 
TEST_CASE("op_or_rmW_rW", "[or]") {
    x86Tester test;
    x86Checkpoint check = test.LoadCheckpoint();
    test.Run(
            "mov bl, 0x16\n"
            //"mov cl, 0x89\n"
            "or bl, 0x89\n");
    check.SetReg32(EBX, 0x9f);
    check.SetPF();
    check.SetSF();
    check.UnsetZF();
    test.Compare(check);
}
