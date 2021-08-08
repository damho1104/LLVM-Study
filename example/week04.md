# Week04. [clang/IR Pass] 함수 호출 명령 수정하기 (Part 1)

## **Requirement**
1. **[기본]** clang 컴파일러 프론트엔드에 옵션(ex. -fwrap_func) 추가하기
2. **[기본]** 사용자 정의 LLVM IR Pass 에서는 소스코드에 존재하는 func 함수 호출이 __call_func 함수 호출로 변경되고 func 함수 호출은 __call_func 함수 바디에 있도록 하기
    * **[가정]** : printf 함수는 소스코드에서 이미 사용하였음
3. **[기본]** 옵션값에 따라 행동이 달라질 수 있도록 기능 추가하기
    * -fwrap_func 옵션에 값을 0을 주면 기본값, 2번 기능만 수행하기
    * -fwrap_func 옵션에 값을 1을 주면 2번 기능과 함께 __call_func 함수에는 printf 함수 호출 (call [함수명] function) 이 먼저 수행되도록 기능 추가하기
4. **[심화]** 사용자 정의 LLVM IR Pass 에서 func 함수 뿐만 아니라 타 함수도 가능하도록 하기
    * **Example**
        ``` C
        void func2(){ ... }
        int main(){
            ...
            func2();
        }

        =>

        void func2(){ ... }
        void __call_func2(){
            ...
            func2();
        }
        int main(){
            ...
            __call_func2();
        }
        ```
<br><br>

## **Example**
### *- 예제 소스코드*
``` C
// example.c
#include <stdio.h>

void func(){
}
int main(){
   printf("aaa\n");
   func();
   return 0;
}
```
### *- 수행 방법*
``` bash
# 기본, clang 컴파일러에서 옵션(-fwrap_func=0)을 사용하여 example.c 소스코드를 Human Readable LLVM IR 코드로 변환하기
$ clang -fwrap_func=0 example.c -emit-llvm -S -c -o example.mod.0.ll

# 기본, 수정된 IR 파일을 컴파일하여 실행해보기
$ clang -o example.mod.0 example.mod.0.ll
$ ./example.mod.0
aaa

# 기본, clang 컴파일러에서 옵션-fwrap_func=1을 사용하여 example.c 소스코드를 Human Readable LLVM IR 코드로 변환하기
$ clang -fwrap_func=1 example.c -emit-llvm -S -c -o example.mod.1.ll

# 기본, 수정된 IR 파일을 컴파일하여 실행해보기
$ clang -o example.mod.1 example.mod.1.ll
$ ./example.mod.1
call printf function
aaa
call func function
```
<br>

### *- Original LLVM IR*
```
; ModuleID = 'a.c'
source_filename = "a.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [5 x i8] c"aaa\0A\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @func() #0 {
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str, i64 0, i64 0))
  call void @func()
  ret i32 0
}

declare dso_local i32 @printf(i8*, ...) #1

attributes #0 = { noinline nounwind optnone uwtable "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 12.0.0"}
```
<br>

### *- Modified LLVM IR(example.mod.0.ll)*
```
; ModuleID = 'a.c'
source_filename = "a.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [5 x i8] c"aaa\0A\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @func() #0 {
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %2 = call i32 (i8*, ...) @__call_printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str, i64 0, i64 0))
  call void @__call_func()
  ret i32 0
}

declare dso_local i32 @printf(i8*, ...) #1

define internal i32 @__call_printf(i8* %0, ...) {
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str, i64 0, i64 0))
  ret i32 %2
}

define internal void @__call_func() {
  call void @func()
  ret void
}

attributes #0 = { noinline nounwind optnone uwtable "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 12.0.0"}
```
<br>

### *- Modified LLVM IR(example.mod.1.ll)*
```
; ModuleID = 'a.c'
source_filename = "a.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [5 x i8] c"aaa\0A\00", align 1
@.str.1 = private constant [22 x i8] c"call printf function\0A\00", align 1
@.str.2 = private constant [20 x i8] c"call func function\0A\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @func() #0 {
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %2 = call i32 (i8*, ...) @__call_printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str, i64 0, i64 0))
  call void @__call_func()
  ret i32 0
}

declare dso_local i32 @printf(i8*, ...) #1

define internal i32 @__call_printf(i8* %0, ...) {
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.1, i64 0, i64 0))
  %3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str, i64 0, i64 0))
  ret i32 %3
}

define internal void @__call_func() {
  %1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.2, i64 0, i64 0))
  call void @func()
  ret void
}

attributes #0 = { noinline nounwind optnone uwtable "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 12.0.0"}
```