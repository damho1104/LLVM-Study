# Week02. [clang/IR Pass] 컴파일러 프론트엔드에 옵션 추가하고 소스코드에 정의된 함수 이름 출력하기

## **Requirement**
1. **[기본]** clang 컴파일러 프론트엔드에 옵션(ex. -fldh) 추가하기
2. **[기본]** 사용자 정의 LLVM IR Pass 에서는 소스코드에 정의된 함수 이름 출력하기
<br><br>

## **Example**
### *- 예제 소스코드*
``` C
// example.c
#include <stdio.h>
void func1()
{

}
void func2()
{
    
}
void func3()
{
    
}
int main()
{
        printf("Hello\n");
        return 0;
}
```
<br>

### *- 수행 방법*
``` bash
# 기본, clang 컴파일러에서 옵션을 사용하여 example.c 소스코드를 Human Readable LLVM IR 코드로 변환하기
$ clang -fldh example.c -emit-llvm -S -c -o example.mod.ll
func1
func2
func3
main

# 기본, 수정된 IR 파일을 컴파일하여 실행해보기
$ clang -o example example.mod.ll
$ ./example
Hello
```