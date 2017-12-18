#include "x86test.h"

TEST_CASE( "8-bit Add flags are correct", "[flags]" ) {
    x86CPU cpu;
    cpu.Add8(0, 0);
    REQUIRE((int) cpu.freg.bits.zf);
    REQUIRE((int) !cpu.freg.bits.of);
    REQUIRE((int) !cpu.freg.bits.cf);
}

TEST_CASE("asm test", "[test]") {
    x86Tester test;
    x86Checkpoint check = test.LoadCheckpoint();
    test.Run("mov eax, 0x12345678");
    check.SetReg32(EAX, 0x12345678);
    check.AdvanceEIP(5);
    test.Compare(check, true);
}