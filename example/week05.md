# Week05. [clang/IR Pass] 함수 호출 명령 수정하기 (Part 2)

## **Requirement**
1. **[기본]** clang 컴파일러 프론트엔드에 옵션(ex. -freverse_func_order) 추가하기
2. **[기본]** func 함수 바디에 존재하는 함수 호출 명령 순서를 뒤집는 기능 추가하기
<br>

## **Example**
### *- 예제 소스코드*
``` C
// example.c
#include <stdio.h>
void func1(){
   printf("func1 called!\n");
}
int func2(){
   return 2;
}
int func3(int input){
   return 3;
}
void func(){
   func1();
   int a = func2();
   func3(a);
   printf("%d\n", a);
}
int main(){
   func();
   return 0;
}
```
### *- 수행 방법*
``` bash
# 기본, 예제 빌드 및 실행 시 결과 확인하기
$ clang -o example example.c
$ ./example
func1 called!
3

# 기본, clang 컴파일러에서 옵션(-freverse_func_order)을 사용하여 example.c 소스코드를 Human Readable LLVM IR 코드로 변환하기
$ clang -freverse_func_order example.c -emit-llvm -S -c -o example.mod.ll

# 기본, 수정된 IR 파일을 컴파일하여 실행해보기
$ clang -o example.mod example.mod.ll
$ ./example.mod
2
func1 called!
```
<br>

### *- Original LLVM IR*
```
; ModuleID = 'example.c'
source_filename = "example.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [15 x i8] c"func1 called!\0A\00", align 1
@.str.1 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @func1() #0 {
entry:
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str, i64 0, i64 0))
  ret void
}

declare dso_local i32 @printf(i8*, ...) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @func2() #0 {
entry:
  ret i32 2
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @func3(i32 %input) #0 {
entry:
  %input.addr = alloca i32, align 4
  store i32 %input, i32* %input.addr, align 4
  ret i32 3
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @func() #0 {
entry:
  %a = alloca i32, align 4
  call void @func1()
  %call = call i32 @func2()
  store i32 %call, i32* %a, align 4
  %0 = load i32, i32* %a, align 4
  %call1 = call i32 @func3(i32 %0)
  %1 = load i32, i32* %a, align 4
  %call2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i64 0, i64 0), i32 %1)
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  call void @func()
  ret i32 0
}

attributes #0 = { noinline nounwind optnone uwtable "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 12.0.0"}
```
<br>

### *- Modified LLVM IR(example.mod.ll)*
```

```
