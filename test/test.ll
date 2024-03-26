; ModuleID = 'test/test.c'
source_filename = "test/test.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [9 x i8] c"r0 = %d\0A\00", align 1
@.str.1 = private unnamed_addr constant [9 x i8] c"r1 = %d\0A\00", align 1
@.str.2 = private unnamed_addr constant [9 x i8] c"r2 = %d\0A\00", align 1
@.str.3 = private unnamed_addr constant [9 x i8] c"r3 = %d\0A\00", align 1
@.str.4 = private unnamed_addr constant [9 x i8] c"r4 = %d\0A\00", align 1
@.str.5 = private unnamed_addr constant [9 x i8] c"r5 = %d\0A\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @foo(i32 noundef %a, i32 noundef %b, i32 noundef %c) #0 {
entry:
  %a.addr = alloca i32, align 4
  %b.addr = alloca i32, align 4
  %c.addr = alloca i32, align 4
  %r0 = alloca i32, align 4
  %r1 = alloca i32, align 4
  %r2 = alloca i32, align 4
  %r3 = alloca i32, align 4
  %r4 = alloca i32, align 4
  %r5 = alloca i32, align 4
  %r6 = alloca i32, align 4
  %r7 = alloca i32, align 4
  %r8 = alloca i32, align 4
  store i32 %a, ptr %a.addr, align 4
  store i32 %b, ptr %b.addr, align 4
  store i32 %c, ptr %c.addr, align 4
  %0 = load i32, ptr %a.addr, align 4
  %add = add nsw i32 %0, 0
  store i32 %add, ptr %r0, align 4
  %1 = load i32, ptr %a.addr, align 4
  %add1 = add nsw i32 0, %1
  store i32 %add1, ptr %r1, align 4
  %2 = load i32, ptr %b.addr, align 4
  %mul = mul nsw i32 %2, 1
  store i32 %mul, ptr %r2, align 4
  %3 = load i32, ptr %b.addr, align 4
  %mul2 = mul nsw i32 1, %3
  store i32 %mul2, ptr %r3, align 4
  %4 = load i32, ptr %a.addr, align 4
  %mul3 = mul nsw i32 15, %4
  store i32 %mul3, ptr %r4, align 4
  %5 = load i32, ptr %a.addr, align 4
  %mul4 = mul nsw i32 %5, 15
  store i32 %mul4, ptr %r5, align 4
  %6 = load i32, ptr %a.addr, align 4
  %div = sdiv i32 %6, 8
  store i32 %div, ptr %r6, align 4
  %7 = load i32, ptr %b.addr, align 4
  %add5 = add nsw i32 %7, 1
  store i32 %add5, ptr %r7, align 4
  %8 = load i32, ptr %r7, align 4
  %sub = sub nsw i32 %8, 1
  store i32 %sub, ptr %r8, align 4
  %9 = load i32, ptr %r0, align 4
  %call = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %9)
  %10 = load i32, ptr %r1, align 4
  %call6 = call i32 (ptr, ...) @printf(ptr noundef @.str.1, i32 noundef %10)
  %11 = load i32, ptr %r2, align 4
  %call7 = call i32 (ptr, ...) @printf(ptr noundef @.str.2, i32 noundef %11)
  %12 = load i32, ptr %r3, align 4
  %call8 = call i32 (ptr, ...) @printf(ptr noundef @.str.3, i32 noundef %12)
  %13 = load i32, ptr %r4, align 4
  %call9 = call i32 (ptr, ...) @printf(ptr noundef @.str.4, i32 noundef %13)
  %14 = load i32, ptr %r5, align 4
  %call10 = call i32 (ptr, ...) @printf(ptr noundef @.str.5, i32 noundef %14)
  %15 = load i32, ptr %r6, align 4
  %call11 = call i32 (ptr, ...) @printf(ptr noundef @.str.5, i32 noundef %15)
  %16 = load i32, ptr %r8, align 4
  %call12 = call i32 (ptr, ...) @printf(ptr noundef @.str.5, i32 noundef %16)
  ret void
}

declare i32 @printf(ptr noundef, ...) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  store i32 0, ptr %retval, align 4
  call void @foo(i32 noundef 24, i32 noundef 5, i32 noundef 2)
  ret i32 0
}

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"clang version 17.0.6"}
