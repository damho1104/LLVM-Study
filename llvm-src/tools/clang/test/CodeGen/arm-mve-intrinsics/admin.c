// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py
// RUN: %clang_cc1 -triple thumbv8.1m.main-none-none-eabi -target-feature +mve.fp -mfloat-abi hard -fallow-half-arguments-and-returns -O0 -disable-O0-optnone -S -emit-llvm -o - %s | opt -S -mem2reg -sroa -early-cse | FileCheck %s
// RUN: %clang_cc1 -triple thumbv8.1m.main-none-none-eabi -target-feature +mve.fp -mfloat-abi hard -fallow-half-arguments-and-returns -O0 -disable-O0-optnone -DPOLYMORPHIC -S -emit-llvm -o - %s | opt -S -mem2reg -sroa -early-cse | FileCheck %s

#include <arm_mve.h>

// CHECK-LABEL: @test_vcreateq_f16(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = insertelement <2 x i64> undef, i64 [[A:%.*]], i64 0
// CHECK-NEXT:    [[TMP1:%.*]] = insertelement <2 x i64> [[TMP0]], i64 [[B:%.*]], i64 1
// CHECK-NEXT:    [[TMP2:%.*]] = bitcast <2 x i64> [[TMP1]] to <8 x half>
// CHECK-NEXT:    ret <8 x half> [[TMP2]]
//
float16x8_t test_vcreateq_f16(uint64_t a, uint64_t b)
{
    return vcreateq_f16(a, b);
}

// CHECK-LABEL: @test_vcreateq_f32(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = insertelement <2 x i64> undef, i64 [[A:%.*]], i64 0
// CHECK-NEXT:    [[TMP1:%.*]] = insertelement <2 x i64> [[TMP0]], i64 [[B:%.*]], i64 1
// CHECK-NEXT:    [[TMP2:%.*]] = bitcast <2 x i64> [[TMP1]] to <4 x float>
// CHECK-NEXT:    ret <4 x float> [[TMP2]]
//
float32x4_t test_vcreateq_f32(uint64_t a, uint64_t b)
{
    return vcreateq_f32(a, b);
}

// CHECK-LABEL: @test_vcreateq_s16(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = insertelement <2 x i64> undef, i64 [[A:%.*]], i64 0
// CHECK-NEXT:    [[TMP1:%.*]] = insertelement <2 x i64> [[TMP0]], i64 [[B:%.*]], i64 1
// CHECK-NEXT:    [[TMP2:%.*]] = bitcast <2 x i64> [[TMP1]] to <8 x i16>
// CHECK-NEXT:    ret <8 x i16> [[TMP2]]
//
int16x8_t test_vcreateq_s16(uint64_t a, uint64_t b)
{
    return vcreateq_s16(a, b);
}

// CHECK-LABEL: @test_vcreateq_s32(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = insertelement <2 x i64> undef, i64 [[A:%.*]], i64 0
// CHECK-NEXT:    [[TMP1:%.*]] = insertelement <2 x i64> [[TMP0]], i64 [[B:%.*]], i64 1
// CHECK-NEXT:    [[TMP2:%.*]] = bitcast <2 x i64> [[TMP1]] to <4 x i32>
// CHECK-NEXT:    ret <4 x i32> [[TMP2]]
//
int32x4_t test_vcreateq_s32(uint64_t a, uint64_t b)
{
    return vcreateq_s32(a, b);
}

// CHECK-LABEL: @test_vcreateq_s64(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = insertelement <2 x i64> undef, i64 [[A:%.*]], i64 0
// CHECK-NEXT:    [[TMP1:%.*]] = insertelement <2 x i64> [[TMP0]], i64 [[B:%.*]], i64 1
// CHECK-NEXT:    ret <2 x i64> [[TMP1]]
//
int64x2_t test_vcreateq_s64(uint64_t a, uint64_t b)
{
    return vcreateq_s64(a, b);
}

// CHECK-LABEL: @test_vcreateq_s8(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = insertelement <2 x i64> undef, i64 [[A:%.*]], i64 0
// CHECK-NEXT:    [[TMP1:%.*]] = insertelement <2 x i64> [[TMP0]], i64 [[B:%.*]], i64 1
// CHECK-NEXT:    [[TMP2:%.*]] = bitcast <2 x i64> [[TMP1]] to <16 x i8>
// CHECK-NEXT:    ret <16 x i8> [[TMP2]]
//
int8x16_t test_vcreateq_s8(uint64_t a, uint64_t b)
{
    return vcreateq_s8(a, b);
}

// CHECK-LABEL: @test_vcreateq_u16(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = insertelement <2 x i64> undef, i64 [[A:%.*]], i64 0
// CHECK-NEXT:    [[TMP1:%.*]] = insertelement <2 x i64> [[TMP0]], i64 [[B:%.*]], i64 1
// CHECK-NEXT:    [[TMP2:%.*]] = bitcast <2 x i64> [[TMP1]] to <8 x i16>
// CHECK-NEXT:    ret <8 x i16> [[TMP2]]
//
uint16x8_t test_vcreateq_u16(uint64_t a, uint64_t b)
{
    return vcreateq_u16(a, b);
}

// CHECK-LABEL: @test_vcreateq_u32(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = insertelement <2 x i64> undef, i64 [[A:%.*]], i64 0
// CHECK-NEXT:    [[TMP1:%.*]] = insertelement <2 x i64> [[TMP0]], i64 [[B:%.*]], i64 1
// CHECK-NEXT:    [[TMP2:%.*]] = bitcast <2 x i64> [[TMP1]] to <4 x i32>
// CHECK-NEXT:    ret <4 x i32> [[TMP2]]
//
uint32x4_t test_vcreateq_u32(uint64_t a, uint64_t b)
{
    return vcreateq_u32(a, b);
}

// CHECK-LABEL: @test_vcreateq_u64(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = insertelement <2 x i64> undef, i64 [[A:%.*]], i64 0
// CHECK-NEXT:    [[TMP1:%.*]] = insertelement <2 x i64> [[TMP0]], i64 [[B:%.*]], i64 1
// CHECK-NEXT:    ret <2 x i64> [[TMP1]]
//
uint64x2_t test_vcreateq_u64(uint64_t a, uint64_t b)
{
    return vcreateq_u64(a, b);
}

// CHECK-LABEL: @test_vcreateq_u8(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = insertelement <2 x i64> undef, i64 [[A:%.*]], i64 0
// CHECK-NEXT:    [[TMP1:%.*]] = insertelement <2 x i64> [[TMP0]], i64 [[B:%.*]], i64 1
// CHECK-NEXT:    [[TMP2:%.*]] = bitcast <2 x i64> [[TMP1]] to <16 x i8>
// CHECK-NEXT:    ret <16 x i8> [[TMP2]]
//
uint8x16_t test_vcreateq_u8(uint64_t a, uint64_t b)
{
    return vcreateq_u8(a, b);
}

// CHECK-LABEL: @test_vuninitializedq_polymorphic_f16(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    ret <8 x half> undef
//
float16x8_t test_vuninitializedq_polymorphic_f16(float16x8_t (*funcptr)(void))
{
    return vuninitializedq(funcptr());
}

// CHECK-LABEL: @test_vuninitializedq_polymorphic_f32(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    ret <4 x float> undef
//
float32x4_t test_vuninitializedq_polymorphic_f32(float32x4_t (*funcptr)(void))
{
    return vuninitializedq(funcptr());
}

// CHECK-LABEL: @test_vuninitializedq_polymorphic_s8(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    ret <16 x i8> undef
//
int8x16_t test_vuninitializedq_polymorphic_s8(int8x16_t (*funcptr)(void))
{
    return vuninitializedq(funcptr());
}

// CHECK-LABEL: @test_vuninitializedq_polymorphic_s16(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    ret <8 x i16> undef
//
int16x8_t test_vuninitializedq_polymorphic_s16(int16x8_t (*funcptr)(void))
{
    return vuninitializedq(funcptr());
}

// CHECK-LABEL: @test_vuninitializedq_polymorphic_s32(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    ret <4 x i32> undef
//
int32x4_t test_vuninitializedq_polymorphic_s32(int32x4_t (*funcptr)(void))
{
    return vuninitializedq(funcptr());
}

// CHECK-LABEL: @test_vuninitializedq_polymorphic_s64(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    ret <2 x i64> undef
//
int64x2_t test_vuninitializedq_polymorphic_s64(int64x2_t (*funcptr)(void))
{
    return vuninitializedq(funcptr());
}

// CHECK-LABEL: @test_vuninitializedq_polymorphic_u8(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    ret <16 x i8> undef
//
uint8x16_t test_vuninitializedq_polymorphic_u8(uint8x16_t (*funcptr)(void))
{
    return vuninitializedq(funcptr());
}

// CHECK-LABEL: @test_vuninitializedq_polymorphic_u16(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    ret <8 x i16> undef
//
uint16x8_t test_vuninitializedq_polymorphic_u16(uint16x8_t (*funcptr)(void))
{
    return vuninitializedq(funcptr());
}

// CHECK-LABEL: @test_vuninitializedq_polymorphic_u32(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    ret <4 x i32> undef
//
uint32x4_t test_vuninitializedq_polymorphic_u32(uint32x4_t (*funcptr)(void))
{
    return vuninitializedq(funcptr());
}

// CHECK-LABEL: @test_vuninitializedq_polymorphic_u64(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    ret <2 x i64> undef
//
uint64x2_t test_vuninitializedq_polymorphic_u64(uint64x2_t (*funcptr)(void))
{
    return vuninitializedq(funcptr());
}

// CHECK-LABEL: @test_vuninitializedq_f16(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    ret <8 x half> undef
//
float16x8_t test_vuninitializedq_f16(void)
{
    return vuninitializedq_f16();
}

// CHECK-LABEL: @test_vuninitializedq_f32(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    ret <4 x float> undef
//
float32x4_t test_vuninitializedq_f32(void)
{
    return vuninitializedq_f32();
}

// CHECK-LABEL: @test_vuninitializedq_s16(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    ret <8 x i16> undef
//
int16x8_t test_vuninitializedq_s16(void)
{
    return vuninitializedq_s16();
}

// CHECK-LABEL: @test_vuninitializedq_s32(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    ret <4 x i32> undef
//
int32x4_t test_vuninitializedq_s32(void)
{
    return vuninitializedq_s32();
}

// CHECK-LABEL: @test_vuninitializedq_s64(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    ret <2 x i64> undef
//
int64x2_t test_vuninitializedq_s64(void)
{
    return vuninitializedq_s64();
}

// CHECK-LABEL: @test_vuninitializedq_s8(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    ret <16 x i8> undef
//
int8x16_t test_vuninitializedq_s8(void)
{
    return vuninitializedq_s8();
}

// CHECK-LABEL: @test_vuninitializedq_u16(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    ret <8 x i16> undef
//
uint16x8_t test_vuninitializedq_u16(void)
{
    return vuninitializedq_u16();
}

// CHECK-LABEL: @test_vuninitializedq_u32(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    ret <4 x i32> undef
//
uint32x4_t test_vuninitializedq_u32(void)
{
    return vuninitializedq_u32();
}

// CHECK-LABEL: @test_vuninitializedq_u64(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    ret <2 x i64> undef
//
uint64x2_t test_vuninitializedq_u64(void)
{
    return vuninitializedq_u64();
}

// CHECK-LABEL: @test_vuninitializedq_u8(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    ret <16 x i8> undef
//
uint8x16_t test_vuninitializedq_u8(void)
{
    return vuninitializedq_u8();
}

