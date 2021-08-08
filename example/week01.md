# Week01. [opt/IR Pass] LLVM IR Pass 하나 구축하기

## **Requirement**
1. **[기본]** opt 명령을 사용하는 사용자 정의 LLVM IR Pass 1개 구축하기
2. **[기본]** 사용자 정의 LLVM IR Pass 에서는 기존 printf 명령을 한번 더 수행하도록 하고 출력하는 기능 추가하기
3. **[심화]** 기존 printf 명령을 한번 더 수행하도록 하고 "파일명.mod.ll" 파일로 수정된 IR 코드 생성하기
4. **[심화]** 생성된 "파일명.mod.ll" 파일을 컴파일하여 수정된 내용 잘 반영되었는지 확인하기
<br><br>

## **Example**
### *- 예제 소스코드*
``` C
// example.c
#include <stdio.h>
int main()
{
    int a = 10;
    printf("%d\n", a);
}
```
<br>

### *- 수행 방법*
``` bash
# 기본, example.c 소스코드를 Human Readable LLVM IR 코드로 변환
$ clang -O0 example.c -emit-llvm -S -c -o example.ll

# 기본, opt 명령을 사용하여 LLVM IR Pass 수행하기
$ opt -load ~/build/llvm/12.0/lib/LLVMWeek01.so -cpPrintf example.ll

# 심화, 수정된 IR 파일이 생성되었는지 확인하기
$ ls -al
...
-rw-rw-r-- 1 damho1104 damho1104   73  7월 12 20:42 example.c
-rw-rw-r-- 1 damho1104 damho1104 1686  7월 12 20:42 example.ll
-rw-rw-r-- 1 damho1104 damho1104 1805  7월 13 00:44 example.mod.ll
...

# 심화, 수정된 IR 파일을 컴파일하여 실행해보기
$ clang -o example example.mod.ll
$ ./example
10
10
```